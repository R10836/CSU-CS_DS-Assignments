# -*- coding: utf-8 -*-
import numpy as np

from Distance import Distance_Minkowski


def Nearest_Center(x, centers):
    """计算各个聚类中心与输入样本最近的
    参数:
        x - numpy数组
        centers - numpy二维数组
    返回值：
        cindex - 整数，类中心的索引值，比如3代表分配x到第3个聚类中
    """
    cindex = -1
    #   请在此添加实现代码     #
    # ********** Begin *********#
    # 计算点到各个中心的距离
    min_dist = float('inf')
    for item, center in enumerate(centers):
        dist = np.linalg.norm(x - center)
        if dist < min_dist:
            min_dist = dist
            cindex = item
    return cindex

    # 找出最小距离的类

    # ********** End ***********#


def Estimate_Centers(X, y_estimated, n_clusters):
    """重新计算各聚类中心
    参数:
        X - numpy二维数组，代表数据集的样本特征矩阵
        y_estimated - numpy数组，估计的各个样本的聚类中心索引
        n_clusters - 整数，设定的聚类个数
    返回值：
        centers - numpy二维数组，各个样本的聚类中心
    """
    centers = np.zeros((n_clusters, X.shape[1]))
    # 请在此添加实现代码
    # ********** Begin *********#
    for i in range(n_clusters):
        cluster_points = X[y_estimated == i]
        if len(cluster_points) > 0:
            centers[i] = np.mean(cluster_points, axis=0)
    return centers

    # ********** End ***********#
