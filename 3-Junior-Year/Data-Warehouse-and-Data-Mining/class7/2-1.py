"""
K��ֵ�����㷨
������ʼ�صĸ�������������������ص�������ϵ�����´ص�����Ϊ�����ľ�ֵ
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
        # ��ʼ������, ������ʼ��������
        self.N = data.shape[0]
        random_ind = np.random.choice(self.N, size=self.n_cluster)
        self.centers = [data[i] for i in random_ind]  # list�洢���ĵ���������
        for ind, p in enumerate(data):
            #     ���ڴ����ʵ�ִ���     #
            # ********** Begin *********#
            label = self.mark(p)
            self.cluster[label].append(ind)
            # ********** End ***********#
        return

    def _cal_dist(self, center, p):
        #   ���ڴ����ʵ�ִ���     #
        # ********** Begin *********#
        return np.sum((center - p) ** 2)
        # ����㵽�����ĵľ���ƽ��
        # ********** End ***********#

    def mark(self, p):
        dists = [self._cal_dist(center, p) for center in self.centers]
        # $$$$$for center in self.centers:
            #   ���ڴ����ʵ�ִ���     #
            # ********** Begin *********#
            # ���������㵽ÿ�������ĵľ��룬ѡȡ��С�Ĵ�
            # ********** End ***********#
        return dists.index(min(dists))

    def update_center(self, data):
        for label, inds in self.cluster.items():
            #   ���ڴ����ʵ�ִ���     #
            # ********** Begin *********#
            # ���´ص���������
            self.centers[label] = np.mean(data[inds], axis = 0)
            # ********** End ***********#
        return

    def divide(self, data):
        tmp_cluster = copy.deepcopy(self.cluster)  # ���������У��ֵ䳤�Ȳ��ܷ����ı䣬��deepcopy
        for label, inds in tmp_cluster.items():
            #   ���ڴ����ʵ�ִ���     #
            # ********** Begin *********#
            # ���¶���������
            # �����ǲ��䣬����
            for ind in inds:
                p = data[ind]
                new_label = self.mark(p)
                if new_label != label:
                    self.cluster[label].remove(ind)
                    self.cluster[new_label].append(ind)
            # ********** End ***********#
        return

    def cal_err(self, data):
        # ����MSE
        mse = 0
        for label, inds in self.cluster.items():
            #   ���ڴ����ʵ�ִ���     #
            # ********** Begin *********#
            mse += (np.sum((data[inds] - self.centers[label]) ** 2))
            # ********** End ***********#
        return mse / self.N

    def fit(self, data):
        self.init_param(data)
        step = 0
        while step < self.maxstep:
            #   ���ڴ����ʵ�ִ���     #
            # ********** Begin *********#
            self.update_center(data)
            self.divide(data)
            err = self.cal_err(data)
            if err < self.epsilon:
                break
            step += 1
            # ********** End ***********#
        return