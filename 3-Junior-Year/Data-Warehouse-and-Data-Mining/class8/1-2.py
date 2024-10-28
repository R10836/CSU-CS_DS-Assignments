dataSet = [["����", "����", "����", "����", "����", "Ӳ��", "��"],
           ["�ں�", "����", "����", "����", "����", "Ӳ��", "��"],
           ["�ں�", "����", "����", "����", "����", "Ӳ��", "��"],
           ["����", "����", "����", "����", "����", "Ӳ��", "��"],
           ["ǳ��", "����", "����", "����", "����", "Ӳ��", "��"],
           ["����", "����", "����", "����", "�԰�", "��ճ", "��"],
           ["�ں�", "����", "����", "�Ժ�", "�԰�", "��ճ", "��"],
           ["�ں�", "����", "����", "����", "�԰�", "Ӳ��", "��"],
           ["�ں�", "����", "����", "�Ժ�", "�԰�", "Ӳ��", "��"],
           ["����", "Ӳͦ", "���", "����", "ƽ̹", "��ճ", "��"],
           ["ǳ��", "Ӳͦ", "���", "ģ��", "ƽ̹", "Ӳ��", "��"],
           ["ǳ��", "����", "����", "ģ��", "ƽ̹", "��ճ", "��"],
           ["����", "����", "����", "�Ժ�", "����", "Ӳ��", "��"],
           ["ǳ��", "����", "����", "�Ժ�", "����", "Ӳ��", "��"],
           ["�ں�", "����", "����", "����", "�԰�", "��ճ", "��"],
           ["ǳ��", "����", "����", "ģ��", "ƽ̹", "Ӳ��", "��"],
           ["����", "����", "����", "�Ժ�", "�԰�", "Ӳ��", "��"], ]

from math import log


# ������Ϣ��
def calcShannonEnt(dataSet):
    numEntries = len(dataSet)  # ������
    labelCounts = {}
    for featVec in dataSet:  # ����ÿ������
        currentLabel = featVec[-1]  # ��ǰ���������
        if currentLabel not in labelCounts.keys():  # ��������ֵ�
            labelCounts[currentLabel] = 0
        labelCounts[currentLabel] += 1
    shannonEnt = 0.0
    for key in labelCounts:  # ������Ϣ��
        prob = float(labelCounts[key]) / numEntries
        shannonEnt = shannonEnt - prob * log(prob, 2)
    return shannonEnt


# �������ݼ���axis:���ڼ������Ի��֣�value:Ҫ���ص��Ӽ���Ӧ������ֵ
def splitDataSet(dataSet, axis, value):
    retDataSet = []
    featVec = []
    for featVec in dataSet:
        if featVec[axis] == value:
            reducedFeatVec = featVec[:axis]
            reducedFeatVec.extend(featVec[axis + 1:])
            retDataSet.append(reducedFeatVec)
    return retDataSet


# ѡ����õ����ݼ����ַ�ʽ
def chooseBestFeatureToSplit(dataSet):
    numFeatures = len(dataSet[0]) - 1  # ���Եĸ���
    baseEntropy = calcShannonEnt(dataSet)
    bestInfoGain = 0.0
    bestFeature = -1

    for i in range(numFeatures):  # ��ÿ�����Լ�����Ϣ����
        featList = [example[i] for example in dataSet]
        uniqueVals = set(featList)  # �����Ե�ȡֵ����
        newEntropy = 0.0
        for value in uniqueVals:  # ��ÿһ��ȡֵ������Ϣ����
            # ********* Begin *******#

            subDataSet = splitDataSet(dataSet, i, value)
            prob = len(subDataSet) / float(len(dataSet))
            newEntropy += prob * calcShannonEnt(subDataSet)

            # ********* End *********#
        infoGain = baseEntropy - newEntropy
        if (infoGain > bestInfoGain):  # ѡ����Ϣ������������
            bestInfoGain = infoGain
            bestFeature = i
    return bestFeature


print(chooseBestFeatureToSplit(dataSet))