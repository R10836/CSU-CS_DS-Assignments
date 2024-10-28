import numpy as np

from sklearn.datasets import make_blobs
from K_Means import KMEANS

class Spectrum:
    def __init__(self, n_cluster, epsilon=1e-3, maxstep=1000, method='unnormalized', criterion='gaussian', gamma=2.0,
                 dis_epsilon=70, k=5):
        self.n_cluster = n_cluster
        self.epsilon = epsilon
        self.maxstep = maxstep
        self.method = method  # 本程序提供规范化以及非规范化的谱聚类算法
        self.criterion = criterion  # 相似性矩阵的构建方法
        self.gamma = gamma  # 高斯方法中的sigma参数
        self.dis_epsilon = dis_epsilon  # epsilon-近邻方法的参数
        self.k = k  # k近邻方法的参数
        self.W = None  # 图的相似性矩阵
        self.L = None  # 图的拉普拉斯矩阵
        self.L_norm = None  # 规范化后的拉普拉斯矩阵
        self.D = None  # 图的度矩阵
        self.cluster = None
        self.N = None

    # 初始化参数
    def init_param(self, data):
        self.N = data.shape[0]
        dis_mat = self.cal_dis_mat(data)
        self.cal_weight_mat(dis_mat)
        self.D = np.diag(self.W.sum(axis=1))
        self.L = self.D - self.W
        return

    # 计算距离平方的矩阵
    def cal_dis_mat(self, data):
        dis_mat = np.zeros((self.N, self.N))
        for i in range(self.N):
            for j in range(i + 1, self.N):
                #   请在此添加实现代码     #
                # ********** Begin *********#
                dis_mat[i][j] = np.sum((data[i] - data[j])**2)
                dis_mat[j][i] = dis_mat[i][j]

                # ********** End ***********#
        return dis_mat

    # 计算相似性矩阵
    def cal_weight_mat(self, dis_mat):
        if self.criterion == 'gaussian':  # 适合于较小样本集
            if self.gamma is None:
                raise ValueError('gamma is not set')
            self.W = np.exp(-self.gamma * dis_mat)
        elif self.criterion == 'k_nearest':  # 适合于较大样本集
            if self.k is None or self.gamma is None:
                raise ValueError('k or gamma is not set')
            self.W = np.zeros((self.N, self.N))
            for i in range(self.N):
                inds = np.argpartition(dis_mat[i], self.k + 1)[:self.k + 1]  # 由于包括自身，所以+1
                tmp_w = np.exp(-self.gamma * dis_mat[i][inds])
                self.W[i][inds] = tmp_w
        elif self.criterion == 'eps_nearest':  # 适合于较大样本集
            if self.dis_epsilon is None:
                raise ValueError('epsilon is not set')
            self.W = np.zeros((self.N, self.N))
            for i in range(self.N):
                inds = np.where(dis_mat[i] < self.dis_epsilon)
                self.W[i][inds] = 1.0 / len(inds)
        else:
            raise ValueError('the criterion is not supported')
        return

    # 训练主函数
    def fit(self, data):
        self.init_param(data)
        if self.method == 'unnormalized':
            #   请在此添加实现代码     #
            # ********** Begin *********#
            D_inv_sqrt = np.diag(1/np.sqrt(np.diag(self.D)))
            L_norm = np.eye(self.N) - np.dot(np.dot(D_inv_sqrt, self.W), D_inv_sqrt)
            eigvals, eigvecs = np.linalg.eigh(L_norm)

            indices = np.argsort(eigvals)[:self.n_cluster]
            Vectors = eigvecs[:,indices]
            # ********** End ***********#
        else:
            raise ValueError('the method is not supported')
        km = KMEANS(self.n_cluster, self.epsilon, self.maxstep)
        km.fit(Vectors)
        self.cluster = km.cluster
        return

if __name__ == '__main__':
    data, label = make_blobs(centers=3, n_features=10, cluster_std=1.2, n_samples=500, random_state=1)
    sp = Spectrum(n_cluster=3, method='unnormalized', criterion='gaussian', gamma=0.1)
    sp.fit(data)
    cluster = sp.cluster
    def cal_err(data, cluster):
        mse = 0
        # 计算MSE 均方误差
        #   请在此添加实现代码     #
        # ********** Begin *********#
        for label, inds in cluster.items():
            mse += np.sum(np.sum((data[inds]-np.mean(data[inds],axis=0))**2,axis=1))
        return mse/len(data)

        # ********** End ***********#
    if cal_err(data, cluster) < 1000 and cal_err(data, cluster) > 10:
        print("True");