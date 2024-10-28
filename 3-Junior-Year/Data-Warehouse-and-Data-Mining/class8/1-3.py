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
import operator  # ���м����ļ�����
from operator import itemgetter


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
            subDataSet = splitDataSet(dataSet, i, value)
            prob = len(subDataSet) / float(len(dataSet))
            newEntropy += prob * calcShannonEnt(subDataSet)
        infoGain = baseEntropy - newEntropy
        if (infoGain > bestInfoGain):  # ѡ����Ϣ������������
            bestInfoGain = infoGain
            bestFeature = i
    return bestFeature


# ͨ�����򷵻س��ִ����������
def majorityCnt(classList):
    classCount = {}
    for vote in classList:
        if vote not in classCount.keys(): classCount[vote] = 0
        classCount[vote] += 1
    sortedClassCount = sorted(classCount.iteritems(), key=operator.itemgetter(0), reverse=True)
    return sortedClassCount[0][0]


labels = ["ɫ��", "����", "����", "����", "�겿", "����"]


# �ݹ鹹��������
def createTree(dataSet, labels):
    classList = [example[-1] for example in dataSet]  # �������
    if classList.count(classList[0]) == len(classList):  # ���ֻ��һ����𣬷���
        return classList[0]
    if len(dataSet[0]) == 1:  # ����������������������ˣ����س��ִ����������
        return majorityCnt(classList)
    bestFeat = chooseBestFeatureToSplit(dataSet)  # ���Ż������Ե�����
    bestFeatLabel = labels[bestFeat]  # ���Ż������Եı�ǩ
    myTree = {bestFeatLabel: {}}
    del (labels[bestFeat])  # �Ѿ�ѡ����������ٲ������
    featValues = [example[bestFeat] for example in dataSet]
    uniqueValue = set(featValues)  # ���������п���ȡֵ��Ҳ���ǽڵ�ķ�֧
    # ********* Begin *******#
    for value in uniqueValue:
        subDataSet = splitDataSet(dataSet, bestFeat, value)
        myTree[bestFeatLabel][value] = createTree(subDataSet, labels[:])

    # ********* End *********#
    return myTree


Trees = createTree(dataSet, labels)


def classify(inputTree, featLabels, testVec):
    firstStr = list(inputTree.keys())[0]  # �õ���keyֵ
    secondDict = inputTree[firstStr]  # ��key��value--->��һ����֧
    featIndex = featLabels.index(firstStr)  # ȷ�����ڵ��Ǳ�ǩ�����е���һ����������
    key = testVec[featIndex]  # ȷ��һ������������������һ����֧�д������б�
    valueOfFeat = secondDict[key]
    if isinstance(valueOfFeat, dict):  # �ж�ʵ������ �� type�������� �����������һ��
        classLabel = classify(valueOfFeat, featLabels, testVec)
    else:
        classLabel = valueOfFeat
    return classLabel


def retrieveTree(i):
    data = Trees
    listOfTrees = [data]
    return listOfTrees[i]


def createDataSet():
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
    labels = ['ɫ��', '����', '����', '����', '�겿', '����']
    # [�Ƿ���Ը���ˮ��,�Ƿ��н���]
    return dataSet, labels


if __name__ == '__main__':
    data, label = createDataSet()
    myTree = retrieveTree(0)
    result = classify(myTree, label, ['ǳ��', '����', '����', '�Ժ�', '����', 'Ӳ��'])
    if result == 'yes':
        print("�ù�")
    else:
        print("���Ǻù�")

