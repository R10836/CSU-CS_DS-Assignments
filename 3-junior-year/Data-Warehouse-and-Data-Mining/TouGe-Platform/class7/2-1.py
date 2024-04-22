"""
K均值聚类算法
给定初始簇的个数，迭代更改样本与簇的隶属关系，更新簇的中心为样本的均值
"""
import numpy as np
import copy

from collections import defaultdict
from sklearn.datasets import make_blobs


class KMEANS:
    def __init__(self, n_cluster, epsilon=1e-3, maxstep=2000):
        self.n_cluster = n_cluster
        self.epsilon = epsilon
        self.maxstep = maxstep
        self.N = None
        self.centers = None
        self.cluster = defaultdict(list)

    def init_param(self, data):
        # 初始化参数, 包括初始化簇中心
        self.N = data.shape[0]
        random_ind = np.random.choice(self.N, size=self.n_cluster)
        self.centers = [data[i] for i in random_ind]  # list存储中心点坐标数组
        for ind, p in enumerate(data):
            #     请在此添加实现代码     #
            # ********** Begin *********#
            label = self.mark(p)
            self.cluster[label].append(ind)
            # ********** End ***********#
        return

    def _cal_dist(self, center, p):
        #   请在此添加实现代码     #
        # ********** Begin *********#
        return np.sum((center - p) ** 2)
        # 计算点到簇中心的距离平方
        # ********** End ***********#

    def mark(self, p):
        dists = [self._cal_dist(center, p) for center in self.centers]
        # $$$$$for center in self.centers:
            #   请在此添加实现代码     #
            # ********** Begin *********#
            # 计算样本点到每个簇中心的距离，选取最小的簇
            # ********** End ***********#
        return dists.index(min(dists))

    def update_center(self, data):
        for label, inds in self.cluster.items():
            #   请在此添加实现代码     #
            # ********** Begin *********#
            # 更新簇的中心坐标
            self.centers[label] = np.mean(data[inds], axis = 0)
            # ********** End ***********#
        return

    def divide(self, data):
        tmp_cluster = copy.deepcopy(self.cluster)  # 迭代过程中，字典长度不能发生改变，故deepcopy
        for label, inds in tmp_cluster.items():
            #   请在此添加实现代码     #
            # ********** Begin *********#
            # 重新对样本聚类
            # 若类标记不变，跳过
            for ind in inds:
                p = data[ind]
                new_label = self.mark(p)
                if new_label != label:
                    self.cluster[label].remove(ind)
                    self.cluster[new_label].append(ind)
            # ********** End ***********#
        return

    def cal_err(self, data):
        # 计算MSE
        mse = 0
        for label, inds in self.cluster.items():
            #   请在此添加实现代码     #
            # ********** Begin *********#
            mse += (np.sum((data[inds] - self.centers[label]) ** 2))
            # ********** End ***********#
        return mse / self.N

    def fit(self, data):
        self.init_param(data)
        step = 0
        while step < self.maxstep:
            #   请在此添加实现代码     #
            # ********** Begin *********#
            self.update_center(data)
            self.divide(data)
            err = self.cal_err(data)
            if err < self.epsilon:
                break
            step += 1
            # ********** End ***********#
        return