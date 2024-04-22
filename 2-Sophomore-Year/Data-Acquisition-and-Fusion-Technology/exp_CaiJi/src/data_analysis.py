#!/usr/bin/env python3
# coding: utf-8

"""
大数据采集与融合技术实验
数据分析和数据可视化
大数据2103 茹湘原 8204193010
"""

import warnings

# 三大库
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

warnings.simplefilter('ignore')
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
    correlation_matrix(data_frame)
    histogram_of_number_of_houses(data_frame)
    average_price_histogram(data_frame)
    plot_pie_chart(data_frame, 'year')
    regressive_analysis(data_frame)
    regressive_analysis_2(data_frame)
    analyze_correlation(data_frame)
    analyze_correlation_area(data_frame)
    analyze_correlation_price(data_frame)
