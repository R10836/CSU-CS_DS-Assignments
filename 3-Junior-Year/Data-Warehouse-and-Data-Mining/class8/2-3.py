from math import log
import operator


# ������Ϣ��
def calEnt(dataset):
    numEntries = len(dataset)
    labelCounts = {}
    # �����п��ܷ��ഴ���ֵ�
    for featVec in dataset:
        currentlabel = featVec[-1]
        if currentlabel not in labelCounts.keys():
            labelCounts[currentlabel] = 0
        labelCounts[currentlabel] += 1
    Ent = 0.0
    for key in labelCounts:
        p = float(labelCounts[key]) / numEntries
        Ent = Ent - p * log(p, 2)  # ��2Ϊ�������
    return Ent


# �������ݼ�
def splitdataset(dataset, axis, value):
    retdataset = []  # �������ص����ݼ��б�
    for featVec in dataset:  # ��ȡ���ϻ���������ֵ
        if featVec[axis] == value:
            reducedfeatVec = featVec[:axis]  # ȥ��axis����
            reducedfeatVec.extend(featVec[axis + 1:])  # ������������������ӵ����ص����ݼ��б�
            retdataset.append(reducedfeatVec)
    return retdataset


'''
ѡ����õ����ݼ����ַ�ʽ
C4.5�㷨��ʹ�á������ʡ���ѡ�񻮷�����
'''


def C45_chooseBestFeatureToSplit(dataset):
    numFeatures = len(dataset[0]) - 1
    baseEnt = calEnt(dataset)
    bestInfoGain_ratio = 0.0
    bestFeature = -1
    for i in range(numFeatures):  # ������������
        featList = [example[i] for example in dataset]
        uniqueVals = set(featList)  # �������б�����Ϊset���ϣ�Ԫ�ز����ظ�������Ψһ�ķ����ǩ�б�
        newEnt = 0.0
        IV = 0.0
        for value in uniqueVals:  # ����ÿ�ֻ��ַ�ʽ����Ϣ��
            subdataset = splitdataset(dataset, i, value)
            p = len(subdataset) / float(len(dataset))
            newEnt += p * calEnt(subdataset)
            IV = IV - p * log(p, 2)
        infoGain = baseEnt - newEnt
        if (IV == 0):  # fix the overflow bug
            continue
        infoGain_ratio = infoGain / IV  # ���feature��infoGain_ratio
        if (infoGain_ratio > bestInfoGain_ratio):  # ѡ������gain ratio
            bestInfoGain_ratio = infoGain_ratio
            bestFeature = i  # ѡ������gain ratio��Ӧ��feature
    return bestFeature


def C45_createTree(dataset, labels):
    classList = [example[-1] for example in dataset]
    if classList.count(classList[0]) == len(classList):
        # �����ȫ��ͬ��ֹͣ����
        return classList[0]
    if len(dataset[0]) == 1:
        # ��������������ʱ���س��ִ�������
        return majorityCnt(classList)
    bestFeat = C45_chooseBestFeatureToSplit(dataset)
    bestFeatLabel = labels[bestFeat]

    C45Tree = {bestFeatLabel: {}}
    del (labels[bestFeat])
    # �õ��б�����ڵ����е�����ֵ
    featValues = [example[bestFeat] for example in dataset]
    uniqueVals = set(featValues)
    for value in uniqueVals:
        subLabels = labels[:]
        # ********** Begin **********#

        C45Tree[bestFeatLabel][value] = C45_createTree(splitdataset(dataset, bestFeat, value), subLabels)  # �ݹ鴴��������

        # ********** End **********#
    return C45Tree


def classify(inputTree, featLabels, testVec):
    """
    ���룺�������������ǩ����������
    ��������߽��
    �������ܾ�����
    """
    firstStr = list(inputTree.keys())[0]
    secondDict = inputTree[firstStr]
    featIndex = featLabels.index(firstStr)
    classLabel = '0'
    for key in secondDict.keys():
        if testVec[featIndex] == key:
            if type(secondDict[key]).__name__ == 'dict':
                # ********** Begin **********#

                classLabel = classify(secondDict[key], featLabels, testVec) if isinstance(secondDict[key], dict) else \
                secondDict[key]  # �ݹ����

            # ********** End **********#
            else:
                classLabel = secondDict[key]
    return classLabel
