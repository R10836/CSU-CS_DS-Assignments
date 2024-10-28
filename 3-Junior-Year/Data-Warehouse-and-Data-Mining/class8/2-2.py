from math import log


def calEnt(dataset):
    numEntries = len(dataset)
    labelCounts = {}
    # �����п��ܷ��ഴ���ֵ�
    for featVec in dataset:
        currentlabel = featVec[-1]
        if currentlabel not in labelCounts.keys():
            labelCounts[currentlabel] = 0
        labelCounts[currentlabel] += 1
    ent = 0.0
    for key in labelCounts:
        p = float(labelCounts[key]) / numEntries
        # ��2Ϊ�������������Ϣ��
        ent = ent - p * log(p, 2)
    return ent


def splitdataset(dataset, axis, value):
    retdataset = []  # �������ص����ݼ��б�
    for featVec in dataset:  # ��ȡ���ϻ���������ֵ
        if featVec[axis] == value:
            reducedfeatVec = featVec[:axis]  # ȥ��axis����
            reducedfeatVec.extend(featVec[axis + 1:])  # ������������������ӵ����ص����ݼ��б�
            retdataset.append(reducedfeatVec)
    return retdataset


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
        if (IV == 0):
            continue
        infoGain_ratio = infoGain / IV  # �˴�feature��infoGain_ratio
        # ********** Begin **********#
        if infoGain_ratio > bestInfoGain_ratio:
            bestInfoGain_ratio = infoGain_ratio
            bestFeature = i
        # ********** End **********#
    return bestFeature