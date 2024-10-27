![image-20231206182315760](https://raw.githubusercontent.com/LukiRyan/TyporaImageBox/main/img/202312061823820.png)

==正式的实验报告在doc文件夹==

# 大数据采集与融合技术 实验报告

|   **学院**   | **计算机学院** |
| :----------: | :------------: |
| **专业班级** |                |
|              |                |
|              |                |
|              |                |

# 目录

[TOC]

------



# 正文

==正式的实验报告在doc文件夹==

## 一、实验内容

​	熟悉实践大数据实战的整体流程，包括python 数据爬取、数据清洗加数据预处理、python可视化图形展示、得出结论，指导预测，从实际的项目需求入手，完成整个大数据的流程处理，真正体会到大数据在实际生活中的应用。

​	项目需求是找出某市各个区的房屋出租数量与出租均价之间的关系。本次使用的数据爬取工具为python。



## 二、实验目的

（1）掌握python 数据爬取的相关技术

（2）掌握数据清洗和数据预处理的相关技术

（3）掌握python可视化图形展示的相关方法

（4）理解和掌握大数据的流程处理



## 三、实验过程

### 一、实验准备

#### 1、网站选取

项目的数据来源于贝壳网长沙市的房价信息，长沙市租房网页（https://cs.ke.com/）如下图：

![image-20231206183000401](https://raw.githubusercontent.com/LukiRyan/TyporaImageBox/main/img/202312061830716.png)

（网站全局样式）

![image-20231206183057305](https://raw.githubusercontent.com/LukiRyan/TyporaImageBox/main/img/202312061830480.png)

（使用谷歌浏览器开发者工具查看网页结构）

选取网站url:

```python
# 原始url
original_url = 'https://cs.ke.com/ershoufang/{}/'
```





#### 2、找到其用户代理信息

![image-20231206183657472](https://raw.githubusercontent.com/LukiRyan/TyporaImageBox/main/img/202312061836656.png)

（找到其请求标头）

```
# 用户代理
user_agent = ('Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/119.0.0.0 '
              'Safari/537.36')
```



#### 3、 规定相应的城区，建立相应的字典

观察贝壳网的url的命名特点，，是按照区名的拼音命名其子域名的，直接建立字典就行。

![image-20231206184909405](https://raw.githubusercontent.com/LukiRyan/TyporaImageBox/main/img/202312061849513.png)

（观察贝壳网的url的命名特点）

```python
# 规定相应的城区，建立相应的字典
districts = {'yuhua': '雨花', 'yuelu': '岳麓', 'tianxin': '天心', 'kaifu': '开福', 'furong': '芙蓉', 'wangcheng': '望城',
             'ningxiang': '宁乡', 'liuyang': '浏阳', 'changshaxian': '长沙县'}
```



#### 4、将网页保存到本地，方便看html源码

![image-20231206221314160](https://raw.githubusercontent.com/LukiRyan/TyporaImageBox/main/img/202312062213327.png)

（网页另存为）

我存为了[这个文件](./static/static_page.html)。

观察网页元素，我觉得有价值的数据属性有区县、标题、小区、楼层、建成年、室、厅、面积、价格、每平米价格。

故我设置列名为：

```python
# 规定相应的列
column = ['district', 'title', 'community', 'floor', 'year', 'bedroom', 'living_room', 'area', 'price', 'unit_price']
```



### 二、数据采集 和 数据存储

#### 1、导入相应库

```python
import re

import pandas as pd
import requests
from pyquery import PyQuery as pq
```



#### 2、发送HTTP请求，返回响应对象

​	使用request对网页进行爬取，由于刚开始做实验时失败了很多次，所以我考虑了许多健壮性方面的问题。通过多次尝试和异常处理来应对网络或其他可能的问题，确保在可能情况下获取到有效的页面内容。

```python
trying_time = 5


# 获取页面内容
def fetch_page(url, headers, trying_time):
    """
    尝试多次获取页面内容，直到成功或达到最大尝试次数。

    :param url: 目标URL
    :param headers: 请求头信息
    :param trying_time: 最大尝试次数
    :return: 成功获取到的响应对象或None
    """
    for second in range(1, trying_time + 1):
        try:
            response = requests.get(url, headers=headers, timeout=(5, 10))
            if response.status_code == 200:
                return response  # 成功获取到页面，返回响应对象
        except requests.RequestException as e:
            print(f'Request failed {second} time: {e}')

    print('Failed to fetch the page after multiple attempts.')
    return None

```



#### 3、获取每一页的信息，并将DataFrame数据储存在CSV文件中

分析html源码，提取出有用的数据

![image-20231206235726955](https://raw.githubusercontent.com/LukiRyan/TyporaImageBox/main/img/202312062357054.png)



​	人工找出位置后，分析语句特点，用正则提取出数据，获取每一页的信息。最后将数据写入[CSV文件](./data/prices.csv)中。

```python
# 获取每一页的信息
def get_one_page(district, page):
    # 构造请求的 URL 和请求头
    url = original_url.format(district) + 'pg{}/'.format(page)
    headers = {"User-Agent": user_agent}

    # 获取页面内容
    res = fetch_page(url, headers, time)
    if res is None:
        return None
    doc = pq(res.text)  # 使用 PyQuery 解析页面

    # 获取房屋信息所在的<ul>标签
    ul = doc('.sellListContent')  # 房价信息都在<ul class="sellListContent" log-mod="list">中，首先获取ul内容

    # 获取每个房屋信息的<div>标签
    divs = ul.children('.clear .info.clear').items()

    # 通过字典的形式创建DataFrame
    df = pd.DataFrame(columns=column)

    # 遍历每个房屋信息的<div>标签
    for div in divs:
        # 提取房屋信息
        title = div.children('.title a').text()  # 标题信息
        place = div.children('.address .flood .positionInfo a').text()  # 地址信息
        msg = div.children('.address .houseInfo').text()  # 其他信息

        # 提取楼层信息
        try:
            # 楼层在“低中高”中的一个
            floor = re.findall('[低|中|高]楼层', msg)[0]
        except IndexError:
            floor = None
        try:
            total_floor = re.findall(r'\d+', re.findall(r'共\d+层', msg)[0])[0]
        except IndexError:
            total_floor = None

        # 提取年份、房间个数和面积信息
        try:
            build_year = re.findall(r'\d+年', msg)[0].split('年')[0]
        except IndexError:
            build_year = None
        try:
            model = re.findall(r'\d室\d厅', msg)[0]
            room = int(re.findall(r'\d', model)[0])  # 室
            hall = int(re.findall(r'\d', model)[1])  # 厅
        except IndexError:
            room = None
            hall = None
        try:
            area = float(re.findall(r'\d+\.*\d*平米', msg)[0].split('平米')[0])  # 面积
        except IndexError:
            area = None

        # 提取房屋朝向、价格和单价信息
        direction = msg.split("| ")[-1]
        price = div.children('.address .priceInfo .totalPrice span').text()  # 价格
        yuan_per_meter = int(
            div.children('.address .priceInfo .unitPrice span').text().split('元/平')[0].replace(',', ''))

        # 将提取的信息存入DataFrame
        df.loc[len(df)] = {'district': districts[district], 'title': title,
                           'place': place, 'floor': floor, 'total_floor': total_floor, 'build_year': build_year,
                           'room': room, 'hall': hall, 'area': area, 'direction': direction, 'price': price,
                           'mean_price': yuan_per_meter}

    # 将DataFrame数据追加到CSV文件
    df.to_csv('house_data.csv', mode='a', index=False, columns=column, encoding="utf-8", header=None)

```



#### 4、获取最后一页的页码

![image-20231206190257849](https://raw.githubusercontent.com/LukiRyan/TyporaImageBox/main/img/202312061902973.png)

（用户浏览器工具找到有关尾页的html文本）



​	这样，就可以从页面的 HTML 文本中找到类名为 `'page-box'` 的元素，然后使用正则表达式提取出其中的数字，最终得到最后的页码。

```python
# 获得末页的页码
def get_end_page(district):
    """
    获取指定行政区的二手房信息的尾页页码。

    :param district: 行政区名称
    :return: 尾页的页码，如果获取失败则返回 None
    """
    # 构造请求的 URL 和请求头
    url = original_url.format(district)
    headers = {"User-Agent": user_agent}

    # 获取页面内容
    res = fetch_page(url, headers, time)
    if res is None:
        return None
    doc = pq(res.text)  # 使用 PyQuery 解析页面

    # 提取页面中的页码信息
    html = doc('.page-box').html()
    end_page = int(re.findall(r'\d+', html)[0])  # 正则筛选出数字
    
    return end_page

```



#### 5、主逻辑

```python
 # 表头先写入CSV文件
df = pd.DataFrame(columns=column)
df.to_csv('../data/prices.csv', mode='a', index=False,
          columns=column, encoding="utf-8")

# 按区遍历爬取
for area in districts.keys():
    end_page = get_end_page(area)  # 获取每个区的最后一页的页码
    for p in range(1, end_page + 1):
        print('The page being crawled: {}'.format(p))
        get_one_page(area, p)

```



#### 6、[运行](./src/my_spider.py)结果

​	print是为了逐个观察是否爬成功了。

![image-20231206232927560](https://raw.githubusercontent.com/LukiRyan/TyporaImageBox/main/img/202312062329647.png)

（运行结果）



### 三、数据可视化 和 数据分析

#### 1、导入相应库

```python
import warnings

# 三大库
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

```



#### 2、直接从csv读取读取数据

```python
def load_data():
    """
    从 '../data/prices.csv' 加载数据集

    :return:DataFrame:
            Pandas DataFrame containing the loaded dataset.
    """
    data = pd.read_csv('../data/prices.csv')
    # 测试
    # data.info()
    # data.head()
    return data

```



![image-20231207201713124](https://raw.githubusercontent.com/LukiRyan/TyporaImageBox/main/img/202312072017333.png)

（测试结果如图）



分析发现year为浮点型，不太合适，遂改为整数型：

```python
    if 'year' in data.columns:
        data['year'] = pd.to_numeric(data['year'], errors='coerce').astype('Int64')  # 将"year"列中的数值转换为整数型
```



#### 3、相关系数可视化



先看一下数据之间的相关性，以便于寻找分析的方向：

```python
def correlation_matrix(data):
    """
    对数据集中的数值型列进行相关性分析，绘制相关性矩阵的热力图

    :param data: DataFrame
           包含加载的数据集的 Pandas DataFrame。
    :return: None
    """
    # 选择数值型列
    numeric_columns = data.select_dtypes(include=['number']).columns

    # 计算相关性矩阵
    data_corr = data[numeric_columns].corr()

    # 创建图形和子图，设置画布大小
    fig, ax = plt.subplots(figsize=(12, 12))

    # 创建热力图，使用 imshow 函数
    cax = ax.imshow(data_corr, cmap='viridis', interpolation='nearest')

    # 显示颜色条
    cbar = fig.colorbar(cax)

    # 设置坐标轴标签
    ticks = np.arange(0, len(data_corr.columns), 1)
    ax.set_xticks(ticks)
    ax.set_yticks(ticks)
    ax.set_xticklabels(data_corr.columns, rotation=45, ha='right')
    ax.set_yticklabels(data_corr.columns)

    # 显示相关性系数值
    for i in range(len(data_corr.columns)):
        for j in range(len(data_corr.columns)):
            text = ax.text(j, i, f'{data_corr.iloc[i, j]:.2f}', ha='center', va='center', color='w')

    # 设置标题
    ax.set_title('数值型列相关性矩阵热力图')

    # 保存到项目中
    plt.savefig('../images/correlation_matrix_heatmap.png', bbox_inches='tight')
    print('correlation_matrix_heatmap.png is saved.')
    # plt.show()

```

![correlation_matrix_heatmap](https://raw.githubusercontent.com/LukiRyan/TyporaImageBox/main/img/202312090932628.png)

（correlation_matrix_heatmap.png）



​	观查该图，发现一些问题：比如发现房子面积与单价关系不大，但是单价却受总价的影响较大，房总价几乎和面积是线性相关的但又不完全是线性相关的。存在的问题是由于没有对区县进行量化，所以没有反映地区与房价的关系，以下是补充：



#### 4、每个地区的房屋售卖个数柱状图

```python
def histogram_of_number_of_houses(data):
    """
    生成各地区房屋数量的柱状图。

    :param data: 包含房屋数据的 DataFrame
    :return: None
    """
    fig, ax1 = plt.subplots(figsize=(12, 9))

    # 在数据集 data 中新增一列 'count'
    data['count'] = 1

    # 统计各区的数据集的个数
    df_tmp = data.groupby('district').sum()['count']

    # 创建柱状图
    rect1 = ax1.bar(df_tmp.index, df_tmp.values, width=0.5, color='burlywood', label='房屋数量', align='center')

    # 设置坐标轴标签和标题
    ax1.set(xlabel='地区', ylabel='挂网售卖数量', title='数据集中各地区房屋售卖数量统计')

    # 在柱子上添加标签
    ax1.bar_label(rect1, label_type='edge', fontsize=10, color='black')

    # 添加网格线
    ax1.grid(axis='y', linestyle='--', alpha=0.7)

    # 添加图例
    ax1.legend(loc='upper right')

    # 保存图表到文件
    plt.savefig('../images/histogram_of_number_of_houses.png')
    print('histogram_of_number_of_houses.png is saved.')
    # plt.show()

```

![histogram_of_number_of_houses](https://raw.githubusercontent.com/LukiRyan/TyporaImageBox/main/img/202312090925408.png)

(histogram_of_number_of_houses.png)



#### 5、不同地区房屋均价

```python
def average_price_histogram(data):
    """
    生成房屋平均均价的柱状图。

    :param data: 包含房屋数据的 DataFrame
    :return: None
    """
    fig, ax1 = plt.subplots(figsize=(12, 9))

    # 选择 'district' 和 'unit_price' 列
    data = data[['district', 'unit_price']]

    # 按 'district' 列分组，计算均价
    df_tmp = data.groupby('district').mean()['unit_price']

    # 创建柱状图
    rect1 = ax1.bar(df_tmp.index, df_tmp.values, width=0.5, color='red', label='平均均价', align='center')

    # 设置坐标轴标签和标题
    ax1.set(xlabel='地区', ylabel='均价', title='不同地区平均均价')

    # 在柱子上添加标签
    ax1.bar_label(rect1, label_type='edge', fontsize=10, color='black')

    # 添加网格线
    ax1.grid(axis='y', linestyle='--', alpha=0.7)

    # 添加图例
    ax1.legend(loc='upper right')

    # 保存图表到文件
    plt.savefig('../images/histogram_of_average_house_prices.png')
    print('histogram_of_average_house_prices.png is saved.')
    # plt.show()

```

![histogram_of_average_house_prices](https://raw.githubusercontent.com/LukiRyan/TyporaImageBox/main/img/202312090925752.png)

（histogram_of_average_house_prices.png）



#### 6、不同年份建成的房产的饼图



```python
def plot_pie_chart(data, column_name, default_value=0):
    """
    生成不同年份建成的房产的饼图

    :param data: 输入的DataFrame
    :param column_name: 需要分析的列名
    :param default_value: 用于替换null值的默认值
    """
    # 根据指定列的值计算频数，包含null值
    column_counts = data[column_name].value_counts(dropna=False)

    # 计算总数
    total_count = column_counts.sum()

    # 计算占比小于2%的数据总和
    small_percentage_count = column_counts[column_counts / total_count < 0.02].sum()

    # 将占比小于2%的数值合并为"其他年份"
    column_counts = column_counts[column_counts / total_count >= 0.02]
    column_counts['其他年份'] = small_percentage_count

    # 将null值显示为"未知年份"
    column_counts.index = column_counts.index.fillna('未知年份')

    # 创建图表
    fig, ax = plt.subplots(figsize=(9, 9))

    # 绘制饼图
    ax.pie(column_counts, labels=column_counts.index, autopct='%1.1f%%', startangle=90,  textprops={'fontsize': 16})

    ax.axis('equal')  # 使饼图比例相等

    # 设置图标题
    ax.set_title(f'按{column_name}的分布情况', fontsize=20)

    # 保存图表到文件
    plt.savefig(f'../images/distribution_of_{column_name}.png')
    print(f'Distribution of {column_name} is saved.')
    # plt.show()

```



![distribution_of_year](https://raw.githubusercontent.com/LukiRyan/TyporaImageBox/main/img/202312171549205.png)

（distribution_of_year.png）



#### 7、各个数据与出租均价之间的关系



```python
def regressive_analysis(data):
    """
    各个数据与出租均价之间的关系

    参数:
    - data (pd.DataFrame): 输入数据框架，包含 'district' 和 'unit_price' 列。
    """
    # 1. 统计 'district' 列中每个元素的出现次数
    data['district_count'] = data['district'].map(data['district'].value_counts())

    # 2. 计算按 'district' 分类的 'unit_price' 列的统计信息
    unit_price_stats = data.groupby('district').agg({'unit_price': ['count', 'mean']})
    unit_price_stats.columns = ['unit_price_count', 'unit_price_mean']

    # 3. 计算 'district_count' 和 'unit_price' 之间的相关系数
    corr_r = data['district_count'].corr(data['unit_price'])
    print("District Count 和 Unit Price 之间的相关系数:", corr_r)

    # 4. 绘制 'district_count' 和 'unit_price' 之间的散点图和回归线
    plt.figure(figsize=(12, 9), dpi=240)
    plt.scatter(data['district_count'], data['unit_price'], s=2, label=f"相关系数: {corr_r:.3f}")

    # 计算并绘制回归线
    slope, intercept = np.polyfit(data['district_count'], data['unit_price'], 1)
    plt.plot(data['district_count'], slope * data['district_count'] + intercept, color='red', alpha=0.5)

    # 设置标签和标题
    plt.xlabel('区县房产数量')
    plt.ylabel('单价')
    plt.title('房屋数量与均价之间的相关系数和回归线')

    # 保存图表到文件
    plt.savefig(f'../images/regressive_analysis.png')
    print(f'regressive_analysis is saved.')

    # 打印区域计数和单价统计信息
    print("\n区域计数:")
    print(data[['district', 'district_count']].drop_duplicates())

    print("\n单价统计信息:")
    print(unit_price_stats)

```



计算出相关系数：

![image-20231217212608339](https://raw.githubusercontent.com/LukiRyan/TyporaImageBox/main/img/202312172126432.png)

（运行结果）



```
District Count 和 Unit Price 之间的相关系数: 0.02437521280144697
regressive_analysis is saved.

区域计数:
      district  district_count
0           雨花            3000
3000        岳麓            3000
6000        天心            3000
9000        开福            3000
12000       芙蓉            3000
15000       望城            3000
18000       宁乡               7
18007       浏阳               3
18010      长沙县            3000

单价统计信息:
          unit_price_count  unit_price_mean
district                                   
天心                    3000     10655.783000
宁乡                       7      6209.142857
岳麓                    3000     14860.173000
开福                    3000     11847.280333
望城                    3000      8930.666000
浏阳                       3      6595.333333
芙蓉                    3000     10072.254333
长沙县                   3000      8143.139000
雨花                    3000     11441.976000
```



生成**高清**的回归线、散点图：

![regressive_analysis](https://raw.githubusercontent.com/LukiRyan/TyporaImageBox/main/img/202312172121551.png)

（regressive_analysis.png）



​	发现由于网页卖方上线为3000，所以数据分布无法体现实际情况，这个数据分析的不到有效结论，各个数据与出租均价之间的关系不大。



#### 8、研究各地GDP和房价间的关系

在网上简单找到2022年的数据，如图：

![img](https://raw.githubusercontent.com/LukiRyan/TyporaImageBox/main/img/202312172133042.jpeg)

（长沙各区县2022年GDP）

得：

```python
dgp = [2478.00, 1562.12, 1302.16, 1180.00, 1327.16, 1053.13, 1227.06, 1722.50, 2114.42]
```



稍微修改：

```python
def regressive_analysis_2(data):
    """
        GDP与出租均价之间的关系

        参数:
        - data (pd.DataFrame): 输入数据框架
    """
    # 1. 统计 'district' 列中每个元素的出现次数
    data['count'] = data['district'].map(data['district'].value_counts())

    # 2. 修改 'district_count' 列的值为给定列表 dgp
    dgp = [2478.00, 1562.12, 1302.16, 1180.00, 1327.16, 1053.13, 1227.06, 1722.50, 2114.42]
    data['district_gdp'] = np.tile(dgp, len(data) // len(dgp) + 1)[:len(data)]

    # 3. 计算按 'district' 分类的 'unit_price' 列的平均值
    unit_price_avg = data.groupby('district')['unit_price'].mean()

    # 4. 计算 'dgp' 和 'unit_price' 之间的相关系数
    corr_r = data['district_gdp'].corr(data['unit_price'])
    print("DGP 和 Unit Price 之间的相关系数:", corr_r)

    # 5. 绘制 'dgp' 和 'unit_price' 之间的散点图和回归线
    plt.figure(figsize=(12, 9), dpi=100)  # 设置图表大小和分辨率
    plt.scatter(data['district_gdp'], data['unit_price'], alpha=0.5, s=2, label=f"相关系数: {corr_r:.3f}")

    # 计算并绘制回归线
    slope, intercept = np.polyfit(data['district_gdp'], data['unit_price'], 1)
    plt.plot(data['district_gdp'], slope * data['district_gdp'] + intercept, color='red', alpha=0.5)

    # 设置标签和标题
    plt.xlabel('DGP')
    plt.ylabel('Unit Price')
    plt.title('DGP 和 Unit Price 之间的相关系数和回归线')

    # 显示图例和图表
    plt.legend()
    plt.show()

    # 打印区域计数和单价统计信息
    print("\n区域计数:")
    print(data[['district', 'count']].drop_duplicates())

    print("\n单价平均值:")
    print(unit_price_avg)

```





发现长沙各地方GDP与每平方房价也没啥关系。

![regressive_analysis_GDP](https://raw.githubusercontent.com/LukiRyan/TyporaImageBox/main/img/202312172217373.png)

（regressive_analysis_GDP.png）



#### 9、建成年份对于每平米房价的影响



```python
def analyze_correlation(data):
    """
    分析数据框架中 'year' 和 'unit_price' 两列之间的相关性，并绘制回归线和散点图。

    参数:
    - data (pd.DataFrame): 输入数据框架，包含 'year' 和 'unit_price' 列。

    返回:
    None (显示绘图并打印统计信息)。
    """

    # 删除包含缺失值的行
    data_cleaned = data.dropna(subset=['year', 'unit_price'])

    # 计算 'year' 和 'unit_price' 之间的相关系数
    corr_r = data_cleaned['year'].corr(data_cleaned['unit_price'])
    print("Year 和 Unit Price 之间的相关系数:", corr_r)

    # 绘制散点图和回归线
    plt.figure(figsize=(12, 9), dpi=240)  # 设置图表大小和分辨率
    plt.scatter(data_cleaned['year'], data_cleaned['unit_price'], s=1, label=f"相关系数: {corr_r:.3f}")

    # 计算并绘制回归线
    slope, intercept = np.polyfit(data_cleaned['year'], data_cleaned['unit_price'], 1)
    plt.plot(data_cleaned['year'], slope * data_cleaned['year'] + intercept, color='red', alpha=0.5, label='回归线')

    # 设置图表标题和标签
    plt.xlabel('Year')
    plt.ylabel('Unit Price')
    plt.title('Year 和 Unit Price 之间的相关系数和回归线')

    # 保存图表到文件
    plt.savefig(f'../images/relationship_between_year_and_unit.png')
    print(f'relationship_between_year_and_unit is saved.')

```



得到：

```python
Year 和 Unit Price 之间的相关系数: 0.20001410314110368
```



生成：

![relationship_between_year_and_unit](https://raw.githubusercontent.com/LukiRyan/TyporaImageBox/main/img/202312172229289.png)

（relationship_between_year_and_unit.png）



​	由图可知，建成年份对于每平米房价有一定的影响，但90年代以前建成的房子较少，样本不足，有一定的局限性。



#### 10、建筑面积对于每平米房价的影响



```python
def analyze_correlation_area(data):
    """
    绘制建筑面积与每平米房价的散点图和回归线，并计算相关系数。

    :param data: 包含 'area' 和 'unit_price' 列的数据框
    :return: 无返回值，将图表保存为图片文件
    """
    # 删除包含缺失值的行
    data = data.dropna(subset=['area', 'unit_price'])

    # 提取 'area' 和 'unit_price' 列
    area, unit_price = data['area'], data['unit_price']

    # 计算相关系数
    correlation = np.corrcoef(area, unit_price)[0, 1]
    print(f'相关系数: {correlation}')

    # 设置图表大小和分辨率
    plt.figure(figsize=(12, 9), dpi=240)

    # 绘制散点图和回归线
    plt.scatter(area, unit_price, s=1, label='数据点')
    plt.plot(np.unique(area), np.poly1d(np.polyfit(area, unit_price, 1))(np.unique(area)), color='red', label='回归线')

    # 添加标题和标签
    plt.title('建筑面积与每平米房价的相关系数和回归线')
    plt.xlabel('建筑面积')
    plt.ylabel('平米价格')

    # 保存图表到文件
    plt.savefig('../images/relationship_between_area_and_unit.png')
    print('relationship_between_area_and_unit.png is saved.')

```



得到：

```python
相关系数: 0.3104513566780693
```



图像：

![relationship_between_area_and_unit](https://raw.githubusercontent.com/LukiRyan/TyporaImageBox/main/img/202312181725298.png)

（relationship_between_area_and_unit.png）



#### 11、总房价对于每平米房价的影响



```python
def analyze_correlation_price(data):
    """
    绘制总价格与每平米房价的散点图和回归线，并计算相关系数。

    :param data: 包含 'price' 和 'unit_price' 列的数据框
    :return: 无返回值，将图表保存为图片文件
    """
    # 删除包含缺失值的行
    data = data.dropna(subset=['price', 'unit_price'])

    # 提取 'price' 和 'unit_price' 列
    price, unit_price = data['price'], data['unit_price']

    # 计算相关系数
    correlation2 = np.corrcoef(price, unit_price)[0, 1]
    print(f'相关系数: {correlation2}')

    # 设置图表大小和分辨率
    plt.figure(figsize=(12, 9), dpi=240)

    # 绘制散点图和回归线
    plt.scatter(price, unit_price, s=0.5, label='数据点')
    plt.plot(np.unique(price), np.poly1d(np.polyfit(price, unit_price, 1))(np.unique(price)), color='red', label='回归线')

    # 添加标题和标签
    plt.title('总价格与每平米房价的相关系数和回归线')
    plt.xlabel('总价格')
    plt.ylabel('平米价格')

    # 保存图表到文件
    plt.savefig('../images/p9_relationship_between_price_and_unit.png')
    print('p9_relationship_between_price_and_unit.png is saved.')

```



得到：

```python
相关系数: 0.8335513031546169
```

可知，关联性比较强，接近线性。



图像：

![p9_relationship_between_price_and_unit](https://raw.githubusercontent.com/LukiRyan/TyporaImageBox/main/img/202312181740404.png)



​	同理，还可以进行许多的数据分析。



### 四、数据分析初步报告



由前面的数据分析综合，得出：



* 贝壳网上，长沙市岳麓区房价最高，均价为14860.2元/平米。然后分别是开福、雨花、天心、芙蓉、望城、长沙县、浏阳、宁乡。其中，开福和雨花房价不相上下，为11500元/平米左右。天心和芙蓉房价不相上下，为10700元/平米左右。望城和长沙县房价不相上下，为8500元/平米左右。宁乡房价最低，均价为6209.14元/平米。
* 由于贝壳网的限制，一个区县最多有3000条房产信息，岳麓、开福、雨花、天心、芙蓉、望城、长沙县均将3000条数据拉满。而宁乡和浏阳相对偏远，数据较少，不利于数据分析，故此数据分析具有一定的局限性。
* 贝壳网上，由于非强制商家填写建筑年份，故贝壳网售卖的长沙市房产建成年份中，有45.3%为未知。而建成年份占比最多的是2014年，为5.9%。其余占比大于2.0%的年份按占比大小排名为：2013、2016、2015、2017、2018、2012、2010、2011、2008。由此可见二手房的建成年份普遍集中在2013——2018年间，与中国房地产业的黄金时代也较为吻合。
* 长沙市的二手房价格并不随区县的生产总值的影响，无论是较发达的芙蓉、雨花区，还是较为落后的宁乡、望城，房价之间相差不受当地生产总值的制约，反而生产总值居中的岳麓区房价最高，说明房价还受其他的很多的因素影响。
* 建成年份、建筑面积、房产总价均对房价有不同程度的影响，建成年份越晚，房价越高；建筑面积越大，每平米房价越高；总价格越贵，每平米房价也越贵。其中，房产总价均对每平米房价的影响最大，相关系数约为0.83；建筑面积均对每平米房价的影响次之，相关系数约为0.31；房产总价均对每平米房价的影响较小，相关系数约为0.20。






## 四、总结与思考

### 1、关于数据采集和数据存储部分

我学到了：

 * **网络爬虫基础：** 了解了如何使用 Python 的 `requests` 库发送 HTTP 请求，以及如何解析 HTML 页面，使用 `PyQuery` 这样的库来提取页面信息。
 * **异常处理：** 学到了如何处理网络请求中可能出现的异常，提高了代码的鲁棒性，确保在网络不稳定或异常情况下也能正常运行。
 * **正则表达式应用：** 通过使用正则表达式，学会了从文本中提取特定信息的技巧。在爬虫中，这是一项非常重要的技能，因为网页内容的结构可能会有很多变化。
 * **数据处理和存储：** 使用了 `pandas` 库进行数据处理，包括创建 DataFrame、追加数据到 CSV 文件等。这是一个在数据分析和科学领域非常常用的工具。
 * **函数模块化：** 通过将不同功能划分为不同的函数，学会了如何使代码更有组织，可读性更强。这是编程中良好的实践。
 * **学科交叉：** 爬虫涉及到网络通信、数据分析等多个领域，通过这个项目，学到了如何将多个学科的知识结合起来解决实际问题。
 * **项目实践：** 通过实际的项目经验，了解了在爬虫项目中可能遇到的问题，比如页面结构变更、反爬虫机制等，学会了如何应对这些挑战。



### 2、关于数据可视化和数据分析部分

我学到了：

 * **数据分析流程：** 了解了数据分析的基本流程，包括加载数据、数据清洗、数据可视化等步骤。这对于理解如何处理和分析实际数据是很重要的。
 * **Pandas 库应用：** 学到了如何使用 Pandas 库来加载、处理和分析数据。例如，通过 `pd.read_csv` 加载 CSV 文件，使用 DataFrame 进行数据处理和统计。
 * **Matplotlib 库应用：** 通过代码中的图表绘制，学到了如何使用 Matplotlib 库进行数据可视化，包括绘制热力图、柱状图、饼图、散点图等。
* **统计分析方法：** 了解了一些统计分析方法，如相关性分析、回归分析等，这对于理解数据之间的关系和趋势是非常有帮助的。
 * **异常处理：** 在代码中看到了对警告信息的简单处理，了解了如何处理可能出现的异常情况，增强了代码的鲁棒性。
 * **函数模块化：** 通过将不同功能划分为不同的函数，提高了代码的可读性和维护性，学到了良好的编程实践。
 * **文件操作：** 学到了如何读取和保存文件，这在实际项目中非常常见。
 * **撰写数据分析报告：** 学到了如何使用通俗的语言简单的写一份数据分析报告



------



# 源代码

## my_spider.py

```python
#!/usr/bin/env python3
# coding: utf-8

"""
大数据采集与融合技术实验
数据采集和数据存储
"""


import re

import pandas as pd
import requests
from pyquery import PyQuery as pq


# 获取页面内容
def fetch_page(url, headers, trying_time):
    """
    尝试多次获取页面内容，直到成功或达到最大尝试次数。

    :param url: 目标URL
    :param headers: 请求头信息
    :param trying_time: 最大尝试次数
    :return: 成功获取到的响应对象或None
    """
    for second in range(1, trying_time + 1):
        try:
            response = requests.get(url, headers=headers, timeout=(3, 7))
            if response.status_code == 200:
                return response
        except requests.RequestException as e:
            print(f'Request failed {second} time: {e}')

    print('Failed to fetch the page after multiple attempts.')
    return None


# 获取每一页的信息
def get_one_page(district, page):
    """
    获取指定区域和页码的房屋信息并存储到CSV文件中。

    :param district: 区域信息
    :param page: 页码
    :return: None
    """
    # 构造请求的 URL 和请求头
    url = original_url.format(district) + 'pg{}/'.format(page)
    headers = {"User-Agent": user_agent}

    # 获取页面内容
    res = fetch_page(url, headers, time)
    if res is None:
        return None
    doc = pq(res.text)  # 使用 PyQuery 解析页面

    # 获取房屋信息所在的<ul>标签
    ul = doc('.sellListContent')

    # 获取每个房屋信息的<div>标签
    divs = ul.children('.clear .info.clear').items()

    # 通过字典的形式创建DataFrame
    df = pd.DataFrame(columns=column)

    # 遍历每个房屋信息的<div>标签
    for div in divs:
        # 基础信息
        title = div.children('.title a').text()  # 标题信息
        community = div.children('.address .flood .positionInfo a').text()  # 小区信息
        msg = div.children('.address .houseInfo').text()  # 其他信息

        # 楼层
        try:
            floor = re.findall('[低|中|高]楼层', msg)[0]
        except IndexError:
            floor = None

        # 建成年份
        try:
            year = re.findall(r'\d+年', msg)[0].split('年')[0]
        except IndexError:
            year = None

        # 几室几厅
        try:
            model = re.findall(r'\d室\d厅', msg)[0]
            bedroom = int(re.findall(r'\d', model)[0])  # 室
            living_room = int(re.findall(r'\d', model)[1])  # 厅
        except IndexError:
            bedroom = None
            living_room = None

        # 面积
        try:
            area = float(re.findall(r'\d+\.*\d*平米', msg)[0].split('平米')[0])  # 面积
        except IndexError:
            area = None

        # 总价、单价
        price = div.children('.address .priceInfo .totalPrice span').text()  # 价格
        yuan_per_meter = int(
            div.children('.address .priceInfo .unitPrice span').text().split('元/平')[0].replace(',', ''))

        # 将提取的信息存入DataFrame
        df.loc[len(df)] = {'district': districts[district], 'title': title,
                           'community': community, 'floor': floor, 'year': year,
                           'bedroom': bedroom, 'living_room': living_room, 'area': area, 'price': price,
                           'unit_price': yuan_per_meter}

    # 将DataFrame数据追加到CSV文件
    df.to_csv('../data/prices.csv', mode='a', index=False, columns=column, encoding="utf-8", header=None)


# 获得末页的页码
def get_end_page(district):
    """
    获取指定行政区的二手房信息的尾页页码。

    :param district: 行政区名称
    :return: 尾页的页码，如果获取失败则返回 None
    """
    # 构造请求的 URL 和请求头
    url = original_url.format(district)
    headers = {"User-Agent": user_agent}

    # 获取页面内容
    res = fetch_page(url, headers, time)
    if res is None:
        return None
    doc = pq(res.text)  # 使用 PyQuery 解析页面

    # 提取页面中的页码信息
    html = doc('.page-box').html()
    end_page = int(re.findall(r'\d+', html)[0])  # 正则筛选出数字
    return end_page


# 原始url
original_url = 'https://cs.ke.com/ershoufang/{}/'

# 用户代理
user_agent = ('Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/119.0.0.0 '
              'Safari/537.36')

# 规定相应的城区，建立相应的字典
districts = {'yuhua': '雨花', 'yuelu': '岳麓', 'tianxin': '天心', 'kaifu': '开福', 'furong': '芙蓉', 'wangcheng': '望城',
             'ningxiang': '宁乡', 'liuyang': '浏阳', 'changshaxian': '长沙县'}

# 规定相应的列
column = ['district', 'title', 'community', 'floor', 'year', 'bedroom', 'living_room', 'area', 'price', 'unit_price']

# 重复请求的次数
time = 5


# 表头先写入CSV文件
df = pd.DataFrame(columns=column)
df.to_csv('../data/prices.csv', mode='a', index=False,
          columns=column, encoding="utf-8")

# 按区遍历爬取
for area in districts.keys():
    end_page = get_end_page(area)  # 获取每个区的最后一页的页码
    for p in range(1, end_page + 1):
        print('The page being crawled: {}'.format(p))
        get_one_page(area, p)

```



## data_analysis.py

```python
#!/usr/bin/env python3
# coding: utf-8

"""
大数据采集与融合技术实验
数据分析和数据可视化
"""

import warnings

# 三大库
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

warnings.simplefilter('ignore')
# 解决不能显示中文的问题
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False


def load_data():
    """
    从 '../data/prices.csv' 加载数据集

    :return:DataFrame:
            Pandas DataFrame containing the loaded dataset.
    """
    data = pd.read_csv('../data/prices.csv')
    # 测试
    # data.info()
    # data.head()
    # if 'year' in data.columns:  # p4
    #     data['year'] = pd.to_numeric(data['year'], errors='coerce').astype('Int64')  # 将"year"列中的数值转换为整数型
    return data


def correlation_matrix(data):
    """
    对数据集中的数值型列进行相关性分析，绘制相关性矩阵的热力图

    :param data: DataFrame
           包含加载的数据集的 Pandas DataFrame。
    :return: None
    """
    # 选择数值型列
    numeric_columns = data.select_dtypes(include=['number']).columns

    # 计算相关性矩阵
    data_corr = data[numeric_columns].corr()

    # 创建图形和子图，设置画布大小
    fig, ax = plt.subplots(figsize=(9, 9))

    # 创建热力图，使用 imshow 函数
    cax = ax.imshow(data_corr, cmap='viridis', interpolation='nearest')

    # 显示颜色条
    cbar = fig.colorbar(cax)

    # 设置坐标轴标签
    ticks = np.arange(0, len(data_corr.columns), 1)
    ax.set_xticks(ticks)
    ax.set_yticks(ticks)
    ax.set_xticklabels(data_corr.columns, rotation=45, ha='right')
    ax.set_yticklabels(data_corr.columns)

    # 显示相关性系数值
    for i in range(len(data_corr.columns)):
        for j in range(len(data_corr.columns)):
            text = ax.text(j, i, f'{data_corr.iloc[i, j]:.2f}', ha='center', va='center', color='w')

    # 设置标题
    ax.set_title('数值型列相关性矩阵热力图')

    # 保存到项目中
    plt.savefig('../images/p1_correlation_matrix_heatmap.png', bbox_inches='tight')
    print('p1_correlation_matrix_heatmap.png is saved.')
    # plt.show()


def histogram_of_number_of_houses(data):
    """
    生成各地区房屋数量的柱状图。

    :param data: 包含房屋数据的 DataFrame
    :return: None
    """
    fig, ax1 = plt.subplots(figsize=(12, 9))

    # 在数据集 data 中新增一列 'count'
    data['count'] = 1

    # 统计各区的数据集的个数
    df_tmp = data.groupby('district').sum()['count']

    # 创建柱状图
    rect1 = ax1.bar(df_tmp.index, df_tmp.values, width=0.5, color='burlywood', label='房屋数量', align='center')

    # 设置坐标轴标签和标题
    ax1.set(xlabel='地区', ylabel='挂网售卖数量', title='数据集中各地区房屋售卖数量统计')

    # 在柱子上添加标签
    ax1.bar_label(rect1, label_type='edge', fontsize=10, color='black')

    # 添加网格线
    ax1.grid(axis='y', linestyle='--', alpha=0.7)

    # 添加图例
    ax1.legend(loc='upper right')

    # 保存图表到文件
    plt.savefig('../images/p2_histogram_of_number_of_houses.png')
    print('p2_histogram_of_number_of_houses.png is saved.')
    # plt.show()


def average_price_histogram(data):
    """
    生成房屋平均均价的柱状图。

    :param data: 包含房屋数据的 DataFrame
    :return: None
    """
    fig, ax1 = plt.subplots(figsize=(12, 9))

    # 选择 'district' 和 'unit_price' 列
    data = data[['district', 'unit_price']]

    # 按 'district' 列分组，计算均价
    df_tmp = data.groupby('district').mean()['unit_price']

    # 创建柱状图
    rect1 = ax1.bar(df_tmp.index, df_tmp.values, width=0.5, color='red', label='平均均价', align='center')

    # 设置坐标轴标签和标题
    ax1.set(xlabel='地区', ylabel='均价', title='不同地区平均均价')

    # 在柱子上添加标签
    ax1.bar_label(rect1, label_type='edge', fontsize=10, color='black')

    # 添加网格线
    ax1.grid(axis='y', linestyle='--', alpha=0.7)

    # 添加图例
    ax1.legend(loc='upper right')

    # 保存图表到文件
    plt.savefig('../images/p3_histogram_of_average_house_prices.png')
    print('p3_histogram_of_average_house_prices.png is saved.')
    # plt.show()


def plot_pie_chart(data, column_name, default_value=0):
    """
    生成不同年份建成的房产的饼图

    :param data: 输入的DataFrame
    :param column_name: 需要分析的列名
    :param default_value: 用于替换null值的默认值
    """
    # 根据指定列的值计算频数，包含null值
    column_counts = data[column_name].value_counts(dropna=False)

    # 计算总数
    total_count = column_counts.sum()

    # 计算占比小于2%的数据总和
    small_percentage_count = column_counts[column_counts / total_count < 0.02].sum()

    # 将占比小于2%的数值合并为"其他年份"
    column_counts = column_counts[column_counts / total_count >= 0.02]
    column_counts['其他年份'] = small_percentage_count

    # 将null值显示为"未知年份"
    column_counts.index = column_counts.index.fillna('未知年份')

    # 创建图表
    fig, ax = plt.subplots(figsize=(9, 9))

    # 绘制饼图
    ax.pie(column_counts, labels=column_counts.index, autopct='%1.1f%%', startangle=90, textprops={'fontsize': 16})

    ax.axis('equal')  # 使饼图比例相等

    # 设置图标题
    ax.set_title(f'按{column_name}的分布情况', fontsize=20)

    # 保存图表到文件
    plt.savefig(f'../images/p4_distribution_of_{column_name}.png')
    print(f'p4_Distribution of {column_name} is saved.')
    # plt.show()


def regressive_analysis(data):
    """
    各个数据与出租均价之间的关系

    参数:
    - data (pd.DataFrame): 输入数据框架，包含 'district' 和 'unit_price' 列。
    """
    # 1. 统计 'district' 列中每个元素的出现次数
    data['district_count'] = data['district'].map(data['district'].value_counts())

    # 2. 计算按 'district' 分类的 'unit_price' 列的统计信息
    unit_price_stats = data.groupby('district').agg({'unit_price': ['count', 'mean']})
    unit_price_stats.columns = ['unit_price_count', 'unit_price_mean']

    # 3. 计算 'district_count' 和 'unit_price' 之间的相关系数
    corr_r = data['district_count'].corr(data['unit_price'])
    print("District Count 和 Unit Price 之间的相关系数:", corr_r)

    # 4. 绘制 'district_count' 和 'unit_price' 之间的散点图和回归线
    plt.figure(figsize=(12, 9), dpi=240)
    plt.scatter(data['district_count'], data['unit_price'], s=2, label=f"相关系数: {corr_r:.3f}")

    # 计算并绘制回归线
    slope, intercept = np.polyfit(data['district_count'], data['unit_price'], 1)
    plt.plot(data['district_count'], slope * data['district_count'] + intercept, color='red', alpha=0.5)

    # 设置标签和标题
    plt.xlabel('区县房产数量')
    plt.ylabel('单价')
    plt.title('房屋数量与均价之间的相关系数和回归线')

    # 保存图表到文件
    plt.savefig(f'../images/p5_regressive_analysis.png')
    print(f'p5_regressive_analysis is saved.')

    # 打印区域计数和单价统计信息
    print("\n区域计数:")
    print(data[['district', 'district_count']].drop_duplicates())

    print("\n单价统计信息:")
    print(unit_price_stats)


def regressive_analysis_2(data):
    """
        GDP与出租均价之间的关系

        参数:
        - data (pd.DataFrame): 输入数据框架
    """
    # 1. 统计 'district' 列中每个元素的出现次数
    data['count'] = data['district'].map(data['district'].value_counts())

    # 2. 修改 'district_count' 列的值为给定列表 dgp
    dgp = [2478.00, 1562.12, 1302.16, 1180.00, 1327.16, 1053.13, 1227.06, 1722.50, 2114.42]
    data['district_gdp'] = np.tile(dgp, len(data) // len(dgp) + 1)[:len(data)]

    # 3. 计算按 'district' 分类的 'unit_price' 列的平均值
    unit_price_avg = data.groupby('district')['unit_price'].mean()

    # 4. 计算 'dgp' 和 'unit_price' 之间的相关系数
    corr_r = data['district_gdp'].corr(data['unit_price'])
    print("DGP 和 Unit Price 之间的相关系数:", corr_r)

    # 5. 绘制 'dgp' 和 'unit_price' 之间的散点图和回归线
    plt.figure(figsize=(12, 9), dpi=100)  # 设置图表大小和分辨率
    plt.scatter(data['district_gdp'], data['unit_price'], alpha=0.5, s=2, label=f"相关系数: {corr_r:.3f}")

    # 计算并绘制回归线
    slope, intercept = np.polyfit(data['district_gdp'], data['unit_price'], 1)
    plt.plot(data['district_gdp'], slope * data['district_gdp'] + intercept, color='red', alpha=0.5)

    # 设置标签和标题
    plt.xlabel('DGP')
    plt.ylabel('Unit Price')
    plt.title('DGP 和 Unit Price 之间的相关系数和回归线')

    # 保存图表到文件
    plt.savefig(f'../images/p6_regressive_analysis_GDP.png')
    print(f'p6_regressive_analysis_GDP is saved.')

    # 打印区域计数和单价统计信息
    print("\n区域计数:")
    print(data[['district', 'count']].drop_duplicates())

    print("\n单价平均值:")
    print(unit_price_avg)


def analyze_correlation(data):
    """
    分析数据框架中 'year' 和 'unit_price' 两列之间的相关性，并绘制回归线和散点图。

    参数:
    - data (pd.DataFrame): 输入数据框架，包含 'year' 和 'unit_price' 列。

    返回:
    None (显示绘图并打印统计信息)。
    """

    # 删除包含缺失值的行
    data_cleaned = data.dropna(subset=['year', 'unit_price'])

    # 计算 'year' 和 'unit_price' 之间的相关系数
    corr_r = data_cleaned['year'].corr(data_cleaned['unit_price'])
    print("Year 和 Unit Price 之间的相关系数:", corr_r)

    # 绘制散点图和回归线
    plt.figure(figsize=(12, 9), dpi=240)  # 设置图表大小和分辨率
    plt.scatter(data_cleaned['year'], data_cleaned['unit_price'], s=1, label=f"相关系数: {corr_r:.3f}")

    # 计算并绘制回归线
    slope, intercept = np.polyfit(data_cleaned['year'], data_cleaned['unit_price'], 1)
    plt.plot(data_cleaned['year'], slope * data_cleaned['year'] + intercept, color='red', alpha=0.5, label='回归线')

    # 设置图表标题和标签
    plt.xlabel('Year')
    plt.ylabel('Unit Price')
    plt.title('Year 和 Unit Price 之间的相关系数和回归线')

    # 保存图表到文件
    plt.savefig(f'../images/p7_relationship_between_year_and_unit.png')
    print(f'p7_relationship_between_year_and_unit is saved.')


def analyze_correlation_area(data):
    """
    绘制建筑面积与每平米房价的散点图和回归线，并计算相关系数。

    :param data: 包含 'area' 和 'unit_price' 列的数据框
    :return: 无返回值，将图表保存为图片文件
    """
    # 删除包含缺失值的行
    data = data.dropna(subset=['area', 'unit_price'])

    # 提取 'area' 和 'unit_price' 列
    area, unit_price = data['area'], data['unit_price']

    # 计算相关系数
    correlation = np.corrcoef(area, unit_price)[0, 1]
    print(f'相关系数: {correlation}')

    # 设置图表大小和分辨率
    plt.figure(figsize=(12, 9), dpi=240)

    # 绘制散点图和回归线
    plt.scatter(area, unit_price, s=1, label='数据点')
    plt.plot(np.unique(area), np.poly1d(np.polyfit(area, unit_price, 1))(np.unique(area)), color='red', label='回归线')

    # 添加标题和标签
    plt.title('建筑面积与每平米房价的相关系数和回归线')
    plt.xlabel('建筑面积')
    plt.ylabel('平米价格')

    # 保存图表到文件
    plt.savefig('../images/p8_relationship_between_area_and_unit.png')
    print('p8_relationship_between_area_and_unit.png is saved.')


def analyze_correlation_price(data):
    """
    绘制总价格与每平米房价的散点图和回归线，并计算相关系数。

    :param data: 包含 'price' 和 'unit_price' 列的数据框
    :return: 无返回值，将图表保存为图片文件
    """
    # 删除包含缺失值的行
    data = data.dropna(subset=['price', 'unit_price'])

    # 提取 'price' 和 'unit_price' 列
    price, unit_price = data['price'], data['unit_price']

    # 计算相关系数
    correlation2 = np.corrcoef(price, unit_price)[0, 1]
    print(f'相关系数: {correlation2}')

    # 设置图表大小和分辨率
    plt.figure(figsize=(12, 9), dpi=240)

    # 绘制散点图和回归线
    plt.scatter(price, unit_price, s=0.5, label='数据点')
    plt.plot(np.unique(price), np.poly1d(np.polyfit(price, unit_price, 1))(np.unique(price)), color='red', label='回归线')

    # 添加标题和标签
    plt.title('总价格与每平米房价的相关系数和回归线')
    plt.xlabel('总价格')
    plt.ylabel('平米价格')

    # 保存图表到文件
    plt.savefig('../images/p9_relationship_between_price_and_unit.png')
    print('p9_relationship_between_price_and_unit.png is saved.')


if __name__ == '__main__':
    data_frame = load_data()
    # TODO
    # correlation_matrix(data_frame)
    # histogram_of_number_of_houses(data_frame)
    # average_price_histogram(data_frame)
    # plot_pie_chart(data_frame, 'year')
    # regressive_analysis(data_frame)
    # regressive_analysis_2(data_frame)
    # analyze_correlation(data_frame)
    # analyze_correlation_area(data_frame)
    # analyze_correlation_price(data_frame)

```



------

==正式的实验报告在doc文件夹==
