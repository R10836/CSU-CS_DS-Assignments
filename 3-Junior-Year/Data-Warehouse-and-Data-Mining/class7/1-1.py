import numpy as np


def Distance_Euclid(x, y):
    '''
    input:x(ndarray):��һ������������
          y(ndarray):�ڶ�������������
    output:distance(float):x��y�ľ���
    '''
    #********* Begin *********#
    return np.sqrt(np.sum((x - y) ** 2))

    # ********* End *********#


def Distance_Manhattan(x, y):
    '''
    input:x(ndarray):��һ������������
          y(ndarray):�ڶ�������������
    output:distance(float):x��y�ľ���
    '''
    #********* Begin *********#
    return np.sum(np.abs(x - y))

    # ********* End *********#


def Distance_Chebyshev(x, y):
    '''
    input:x(ndarray):��һ������������
          y(ndarray):�ڶ�������������
    output:distance(float):x��y�ľ���
    '''
    #********* Begin *********#
    return np.max(np.abs(x - y))
    #********** End *********#


def Distance_Minkowski(x, y, p):
    '''
    input:x(ndarray):��һ������������
          y(ndarray):�ڶ�������������
          p(int):����1ʱΪ�����پ��룬����2ʱΪŷ�Ͼ���
    output:distance(float):x��y�ľ���
    '''
    #********* Begin *********#
    return np.sum(np.abs(x - y) ** p) ** (1 / p)

    #********* End *********#
