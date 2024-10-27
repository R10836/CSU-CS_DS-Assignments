import numpy as np
import pandas as pd
from sklearn.preprocessing import StandardScaler
from sklearn.cluster import KMeans  # 导入kmeans算法
import matplotlib.pyplot as plt
import csv
""" 
    L:会员入会时间距观测窗口结束的月数
    R:客户最后一次乘坐公司飞机距观测窗口结束的月数
    F:客户在观测窗口内乘坐公司飞机的次数
    M:客户在观测窗口内累计的飞行里程
    C:客户在观测窗口内乘坐舱位所对应的折扣系数的平均值
"""

datafile = r'C:\Users\33712\桌面\testPython\exp2/air_data.csv'  # 航空原始数据路径
cleanedfile = 'C:/Users/33712/桌面/testPython/exp2/data_cleaned.csv' # 数据清洗后保存的文件路径

# 读取数据
airline_data = pd.read_csv(datafile,encoding = 'utf-8')
print('原始数据的规格为：',airline_data.shape)

# 去除票价为空的记录
# loc：Selection by Label函数，即为按标签取数据
airline_notnull = airline_data.loc[airline_data['SUM_YR_1'].notnull() & airline_data['SUM_YR_2'].notnull(),:] # 数据中选择票价不为空的记录，并将结果存储在 airline_notnull 变量中。
print('删除缺失记录后数据的规格为：',airline_notnull.shape)

# 只保留票价非零的，或者平均折扣率不为0且总飞行公里数大于0的记录。
index1 = airline_notnull['SUM_YR_1'] != 0 # 创建一个布尔索引 index1，用于标识 SUM_YR_1 列中值不为零的记录。
index2 = airline_notnull['SUM_YR_2'] != 0
index3 = (airline_notnull['SEG_KM_SUM']> 0) & (airline_notnull['avg_discount'] != 0)
index4 = airline_notnull['AGE'] > 100  # 去除年龄大于100的记录
airline = airline_notnull[(index1 | index2) & index3 & ~index4] # 使用逻辑运算符和索引条件筛选出符合条件的记录，并将结果存储在 airline 变量中。
print('数据清洗后数据的规格为：',airline.shape)

airline.to_csv(cleanedfile)  # 将处理后的数据保存到指定路径 cleanedfile 中的 CSV 文件。
airline = pd.read_csv(cleanedfile, encoding = 'utf-8') # 使用 pandas 的 read_csv 函数重新读取清洗后的数据，并将结果存储在 airline 变量中。

# 选取需求属性
# 入会时间，观测窗口结束时间，最后一次乘机至观测窗口结束的时长，观测期间飞行次数，观测期间飞行里程数，平均折扣率
airline_selection = airline[['FFP_DATE','LOAD_TIME','LAST_TO_END',
                                     'FLIGHT_COUNT','SEG_KM_SUM','avg_discount']]
print('筛选的属性前10行为：\n',airline_selection.head(10))

# 构造属性L
# pandas.to_datetime（arg，errors =‘raise’，utc = None，format = None，unit = None ）自动识别时间格式
# astype 数据类型转换
L = pd.to_datetime(airline_selection['LOAD_TIME']) - pd.to_datetime(airline_selection['FFP_DATE'])
print('未处理的L的前5行是：\n',L.head(5))
# split：对字符串进行切片，观察之前数据发现，当前L的第一个字符串即为天数
L = L.astype('str').str.split().str[0]
print('取数据的L的前5行是：\n',L.head(5))
L = L.astype('int')/30
print('观测期间的月数（L）前5行是：\n',L.head(5))

# 合并属性
# pd.concat(obj,axis = 1),数据连接函数，obj可以是数组，列表或者数据框；
# axis = 0 表示按行连接（行增加连接），axis = 1 表示按列连接（列增加连接）
# iloc[:,:]前面的冒号取行数，后面的冒号取列数
airline_features = pd.concat([L,airline_selection.iloc[:,2:]],axis = 1)
airline_features.columns = ['L','R','F','M','C']
print('定义的LRFMC属性前10行为：\n',airline_features.head(10))

# 数据标准化：消除数据量级的影响
# StandardScaler():通过删除平均值并缩放到单位方差来标准化特征
# 通过 fit_transform() 对训练集进行归一化
data = StandardScaler().fit_transform(airline_features)
# 保存为二进制文件
np.savez('airline_scale.npz',data)
print('LRFMC五个属性经标准化后前10个值为：\n',data[:10,:])

# 读取标准化后的数据
airline_scale = np.load('airline_scale.npz')['arr_0']

k = 2  # 确定聚类中心数
# 构建模型，随机种子设为123
kmeans_model = KMeans(n_clusters=k, random_state=123)
fit_kmeans = kmeans_model.fit(airline_scale)  # 模型训练

# 查看聚类结果
kmeans_cc = kmeans_model.cluster_centers_  # 聚类中心
print('各类聚类中心为：\n',kmeans_cc)
kmeans_labels = kmeans_model.labels_  # 样本的类别标签
print('各样本的类别标签为：\n',kmeans_labels)
r1 = pd.Series(kmeans_model.labels_).value_counts()  # 统计不同类别样本的数目
print('最终每个类别的数目为：\n',r1)

# 输出聚类分群的结果
cluster_center = pd.DataFrame(kmeans_model.cluster_centers_,
             columns = ['ZL','ZR','ZF','ZM','ZC'])   # 将聚类中心放在数据框中
cluster_center.index = pd.DataFrame(kmeans_model.labels_ ).\
                  drop_duplicates().iloc[:,0]  # 将样本类别作为数据框索引
print(cluster_center)

# 客户分群雷达图
labels = ['ZL','ZR','ZF','ZM','ZC']
legen = ['客户群' + str(i + 1) for i in cluster_center.index]  # 客户群命名，作为雷达图的图例
lstype = ['-','--',(0, (3, 5, 1, 5, 1, 5)),':','-.']
kinds = list(cluster_center.iloc[:, 0])

# 由于雷达图要保证数据闭合，因此再添加L列，并转换为 np.ndarray
cluster_center = pd.concat([cluster_center, cluster_center[['ZL']]], axis=1)
centers = np.array(cluster_center.iloc[:, 0:])

# 分割圆周长，并让其闭合
n = len(labels)
angle = np.linspace(0, 2 * np.pi, n, endpoint=False)
angle = np.concatenate((angle, [angle[0]]))

# 绘图
fig = plt.figure(figsize = (8,8))
ax = fig.add_subplot(111, polar=True)  # 以极坐标的形式绘制图形
plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号

# 画线
for i in range(len(kinds)):
    ax.plot(angle, centers[i], linestyle=lstype[i], linewidth=2, label=kinds[i])

# 添加属性标签
ang = angle * 180 / np.pi
ax.set_thetagrids(ang[:-1], labels)
#ax.set_thetagrids(angle * 180 / np.pi, labels)
plt.title('客户特征分析雷达图')
plt.legend(legen)
fig.patch.set_facecolor('#FFFFE0')
plt.gcf().canvas.set_window_title('ryan python实验2')
plt.show()
plt.close

with open('C:/Users/33712/桌面/testPython/exp2/data_cleaned.csv','r',encoding='utf-8')as fp:
    reader=csv.reader(fp)
    t=0
    for rows in enumerate(reader):
        if kmeans_labels[t]==0:
            row =rows
            # print(row)
            filename=row[1]
            path=r'C:/Users/Dell/Desktop/python/一般客户.csv'
            with open (path,'a',newline='',encoding='utf-8')as fp:
                    writer=csv.writer(fp)
                    writer.writerow(row)
            fp.close()
            t=t+1
        elif kmeans_labels[t]==1:
            row =rows
            # print(row)
            filename=row[1]
            path=r'C:/Users/Dell/Desktop/python/低价值客户.csv'
            with open (path,'a',newline='',encoding='utf-8')as fp:
                    writer=csv.writer(fp)
                    writer.writerow(row)
            fp.close()
            t=t+1
        elif kmeans_labels[t]==2:
            row =rows
            # print(row)
            filename=row[1]
            path=r'C:/Users/Dell/Desktop/python/重要挽留客户.csv'
            with open (path,'a',newline='',encoding='utf-8')as fp:
                    writer=csv.writer(fp)
                    writer.writerow(row)
            fp.close()
            t=t+1
        elif kmeans_labels[t]==3:
            row =rows
            # print(row)
            filename=row[1]
            path=r'C:/Users/Dell/Desktop/python/重要保持客户.csv'
            with open (path,'a',newline='',encoding='utf-8')as fp:
                    writer=csv.writer(fp)
                    writer.writerow(row)
            fp.close()
            t=t+1
        elif kmeans_labels[t]==4:
            row =rows
            # print(row)
            filename=row[1]
            path=r'C:/Users/Dell/Desktop/python/重要发展客户.csv'
            with open (path,'a',newline='',encoding='utf-8')as fp:
                    writer=csv.writer(fp)
                    writer.writerow(row)
            fp.close()
            t=t+1