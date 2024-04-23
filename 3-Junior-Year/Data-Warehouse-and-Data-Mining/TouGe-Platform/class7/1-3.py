# -*- coding: utf-8 -*-
import numpy as np
import pandas as pd

from Cluster import Nearest_Center
from Cluster import Estimate_Centers

def Cal_Accuracy(x1, x2):
    """计算精度
    参数:
        x1 - numpy数组
        x2 - numpy数组
    返回值：
        value - 浮点数，精度
    """
    #   请在此添加实现代码     #
    #********** Begin *********#
    #聚类数组对应元素相比较
    #返回精度值
    return np.sum(x1==x2)/len(x1)
    #********** End ***********#
# 随机种子对聚类的效果会有影响，为了便于测试，固定随机数种子
np.random.seed(5)
# 读入数据集
dataset = pd.read_csv('K-Means/iris.csv')
# 取得样本特征矩阵
X = dataset[['SepalLength', 'SepalWidth', 'PetalLength', 'PetalWidth']].values
#数据集表头含义：
#SepalLength:萼片长度
#SepalWidth:萼片宽度
#PetalLength:花瓣长度
#PetalWidth:花瓣宽度
#Species:种类
y = np.array(dataset['Species'])
# 读入数据
n_clusters, n_iteration = input().split(',')#输入
n_clusters = int(n_clusters)  # 聚类中心个数
n_iteration = int(n_iteration)  # 迭代次数
# 随机选择若干点作为聚类中心
point_index_lst = np.arange(len(y))
np.random.shuffle(point_index_lst)
cluster_centers = X[point_index_lst[:n_clusters]]
# 开始算法流程
y_estimated = np.zeros(len(y))
#   请在此添加实现代码     #
# ********** Begin *********#
    # 计算各个点最接近的聚类中心
    # 计算各个聚类中心
for _ in range(n_iteration):
    for i, point in enumerate(X):
        y_estimated[i] = Nearest_Center(point, cluster_centers)
    cluster_centers=Estimate_Centers(X, y_estimated, n_clusters)
# ********** End ***********#
print('%.3f' % Cal_Accuracy(y_estimated, y))