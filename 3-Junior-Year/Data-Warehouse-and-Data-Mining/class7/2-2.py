import numpy as np

from sklearn.datasets import make_blobs
from K_Means import KMEANS

class Spectrum:
    def __init__(self, n_cluster, epsilon=1e-3, maxstep=1000, method='unnormalized', criterion='gaussian', gamma=2.0,
                 dis_epsilon=70, k=5):
        self.n_cluster = n_cluster
        self.epsilon = epsilon
        self.maxstep = maxstep
        self.method = method  # �������ṩ�淶���Լ��ǹ淶�����׾����㷨
        self.criterion = criterion  # �����Ծ���Ĺ�������
        self.gamma = gamma  # ��˹�����е�sigma����
        self.dis_epsilon = dis_epsilon  # epsilon-���ڷ����Ĳ���
        self.k = k  # k���ڷ����Ĳ���
        self.W = None  # ͼ�������Ծ���
        self.L = None  # ͼ��������˹����
        self.L_norm = None  # �淶�����������˹����
        self.D = None  # ͼ�ĶȾ���
        self.cluster = None
        self.N = None

    # ��ʼ������
    def init_param(self, data):
        self.N = data.shape[0]
        dis_mat = self.cal_dis_mat(data)
        self.cal_weight_mat(dis_mat)
        self.D = np.diag(self.W.sum(axis=1))
        self.L = self.D - self.W
        return

    # �������ƽ���ľ���
    def cal_dis_mat(self, data):
        dis_mat = np.zeros((self.N, self.N))
        for i in range(self.N):
            for j in range(i + 1, self.N):
                #   ���ڴ����ʵ�ִ���     #
                # ********** Begin *********#
                dis_mat[i][j] = np.sum((data[i] - data[j])**2)
                dis_mat[j][i] = dis_mat[i][j]

                # ********** End ***********#
        return dis_mat

    # ���������Ծ���
    def cal_weight_mat(self, dis_mat):
        if self.criterion == 'gaussian':  # �ʺ��ڽ�С������
            if self.gamma is None:
                raise ValueError('gamma is not set')
            self.W = np.exp(-self.gamma * dis_mat)
        elif self.criterion == 'k_nearest':  # �ʺ��ڽϴ�������
            if self.k is None or self.gamma is None:
                raise ValueError('k or gamma is not set')
            self.W = np.zeros((self.N, self.N))
            for i in range(self.N):
                inds = np.argpartition(dis_mat[i], self.k + 1)[:self.k + 1]  # ���ڰ�����������+1
                tmp_w = np.exp(-self.gamma * dis_mat[i][inds])
                self.W[i][inds] = tmp_w
        elif self.criterion == 'eps_nearest':  # �ʺ��ڽϴ�������
            if self.dis_epsilon is None:
                raise ValueError('epsilon is not set')
            self.W = np.zeros((self.N, self.N))
            for i in range(self.N):
                inds = np.where(dis_mat[i] < self.dis_epsilon)
                self.W[i][inds] = 1.0 / len(inds)
        else:
            raise ValueError('the criterion is not supported')
        return

    # ѵ��������
    def fit(self, data):
        self.init_param(data)
        if self.method == 'unnormalized':
            #   ���ڴ����ʵ�ִ���     #
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
        # ����MSE �������
        #   ���ڴ����ʵ�ִ���     #
        # ********** Begin *********#
        for label, inds in cluster.items():
            mse += np.sum(np.sum((data[inds]-np.mean(data[inds],axis=0))**2,axis=1))
        return mse/len(data)

        # ********** End ***********#
    if cal_err(data, cluster) < 1000 and cal_err(data, cluster) > 10:
        print("True");