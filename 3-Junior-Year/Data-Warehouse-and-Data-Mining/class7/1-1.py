import numpy as np


def Distance_Euclid(x, y):
    '''
    input:x(ndarray):第一个样本的坐标
          y(ndarray):第二个样本的坐标
    output:distance(float):x到y的距离
    '''
    #********* Begin *********#
    return np.sqrt(np.sum((x - y) ** 2))

    # ********* End *********#


def Distance_Manhattan(x, y):
    '''
    input:x(ndarray):第一个样本的坐标
          y(ndarray):第二个样本的坐标
    output:distance(float):x到y的距离
    '''
    #********* Begin *********#
    return np.sum(np.abs(x - y))

    # ********* End *********#


def Distance_Chebyshev(x, y):
    '''
    input:x(ndarray):第一个样本的坐标
          y(ndarray):第二个样本的坐标
    output:distance(float):x到y的距离
    '''
    #********* Begin *********#
    return np.max(np.abs(x - y))
    #********** End *********#


def Distance_Minkowski(x, y, p):
    '''
    input:x(ndarray):第一个样本的坐标
          y(ndarray):第二个样本的坐标
          p(int):等于1时为曼哈顿距离，等于2时为欧氏距离
    output:distance(float):x到y的距离
    '''
    #********* Begin *********#
    return np.sum(np.abs(x - y) ** p) ** (1 / p)

    #********* End *********#
