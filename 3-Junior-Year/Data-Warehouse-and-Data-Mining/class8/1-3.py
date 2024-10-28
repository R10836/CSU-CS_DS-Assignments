dataSet = [["青绿", "蜷缩", "浊响", "清晰", "凹陷", "硬滑", "是"],
           ["乌黑", "蜷缩", "沉闷", "清晰", "凹陷", "硬滑", "是"],
           ["乌黑", "蜷缩", "浊响", "清晰", "凹陷", "硬滑", "是"],
           ["青绿", "蜷缩", "沉闷", "清晰", "凹陷", "硬滑", "是"],
           ["浅白", "蜷缩", "浊响", "清晰", "凹陷", "硬滑", "是"],
           ["青绿", "稍蜷", "浊响", "清晰", "稍凹", "软粘", "是"],
           ["乌黑", "稍蜷", "浊响", "稍糊", "稍凹", "软粘", "是"],
           ["乌黑", "稍蜷", "浊响", "清晰", "稍凹", "硬滑", "是"],
           ["乌黑", "稍蜷", "沉闷", "稍糊", "稍凹", "硬滑", "否"],
           ["青绿", "硬挺", "清脆", "清晰", "平坦", "软粘", "否"],
           ["浅白", "硬挺", "清脆", "模糊", "平坦", "硬滑", "否"],
           ["浅白", "蜷缩", "浊响", "模糊", "平坦", "软粘", "否"],
           ["青绿", "稍蜷", "浊响", "稍糊", "凹陷", "硬滑", "否"],
           ["浅白", "稍蜷", "沉闷", "稍糊", "凹陷", "硬滑", "否"],
           ["乌黑", "稍蜷", "浊响", "清晰", "稍凹", "软粘", "否"],
           ["浅白", "蜷缩", "浊响", "模糊", "平坦", "硬滑", "否"],
           ["青绿", "蜷缩", "沉闷", "稍糊", "稍凹", "硬滑", "否"], ]

from math import log
import operator  # 此行加在文件顶部
from operator import itemgetter


# 计算信息熵
def calcShannonEnt(dataSet):
    numEntries = len(dataSet)  # 样本数
    labelCounts = {}
    for featVec in dataSet:  # 遍历每个样本
        currentLabel = featVec[-1]  # 当前样本的类别
        if currentLabel not in labelCounts.keys():  # 生成类别字典
            labelCounts[currentLabel] = 0
        labelCounts[currentLabel] += 1
    shannonEnt = 0.0
    for key in labelCounts:  # 计算信息熵
        prob = float(labelCounts[key]) / numEntries
        shannonEnt = shannonEnt - prob * log(prob, 2)
    return shannonEnt


# 划分数据集，axis:按第几个属性划分，value:要返回的子集对应的属性值
def splitDataSet(dataSet, axis, value):
    retDataSet = []
    featVec = []
    for featVec in dataSet:
        if featVec[axis] == value:
            reducedFeatVec = featVec[:axis]
            reducedFeatVec.extend(featVec[axis + 1:])
            retDataSet.append(reducedFeatVec)
    return retDataSet


# 选择最好的数据集划分方式
def chooseBestFeatureToSplit(dataSet):
    numFeatures = len(dataSet[0]) - 1  # 属性的个数
    baseEntropy = calcShannonEnt(dataSet)
    bestInfoGain = 0.0
    bestFeature = -1
    for i in range(numFeatures):  # 对每个属性技术信息增益
        featList = [example[i] for example in dataSet]
        uniqueVals = set(featList)  # 该属性的取值集合
        newEntropy = 0.0
        for value in uniqueVals:  # 对每一种取值计算信息增益
            subDataSet = splitDataSet(dataSet, i, value)
            prob = len(subDataSet) / float(len(dataSet))
            newEntropy += prob * calcShannonEnt(subDataSet)
        infoGain = baseEntropy - newEntropy
        if (infoGain > bestInfoGain):  # 选择信息增益最大的属性
            bestInfoGain = infoGain
            bestFeature = i
    return bestFeature


# 通过排序返回出现次数最多的类别
def majorityCnt(classList):
    classCount = {}
    for vote in classList:
        if vote not in classCount.keys(): classCount[vote] = 0
        classCount[vote] += 1
    sortedClassCount = sorted(classCount.iteritems(), key=operator.itemgetter(0), reverse=True)
    return sortedClassCount[0][0]


labels = ["色泽", "根蒂", "敲声", "纹理", "脐部", "触感"]


# 递归构建决策树
def createTree(dataSet, labels):
    classList = [example[-1] for example in dataSet]  # 类别向量
    if classList.count(classList[0]) == len(classList):  # 如果只有一个类别，返回
        return classList[0]
    if len(dataSet[0]) == 1:  # 如果所有特征都被遍历完了，返回出现次数最多的类别
        return majorityCnt(classList)
    bestFeat = chooseBestFeatureToSplit(dataSet)  # 最优划分属性的索引
    bestFeatLabel = labels[bestFeat]  # 最优划分属性的标签
    myTree = {bestFeatLabel: {}}
    del (labels[bestFeat])  # 已经选择的特征不再参与分类
    featValues = [example[bestFeat] for example in dataSet]
    uniqueValue = set(featValues)  # 该属性所有可能取值，也就是节点的分支
    # ********* Begin *******#
    for value in uniqueValue:
        subDataSet = splitDataSet(dataSet, bestFeat, value)
        myTree[bestFeatLabel][value] = createTree(subDataSet, labels[:])

    # ********* End *********#
    return myTree


Trees = createTree(dataSet, labels)


def classify(inputTree, featLabels, testVec):
    firstStr = list(inputTree.keys())[0]  # 得到首key值
    secondDict = inputTree[firstStr]  # 首key的value--->下一个分支
    featIndex = featLabels.index(firstStr)  # 确定根节点是标签向量中的哪一个（索引）
    key = testVec[featIndex]  # 确定一个条件后的类别或进入下一个分支有待继续判别
    valueOfFeat = secondDict[key]
    if isinstance(valueOfFeat, dict):  # 判断实例函数 和 type函数类似 但是这个更好一点
        classLabel = classify(valueOfFeat, featLabels, testVec)
    else:
        classLabel = valueOfFeat
    return classLabel


def retrieveTree(i):
    data = Trees
    listOfTrees = [data]
    return listOfTrees[i]


def createDataSet():
    dataSet = [["青绿", "蜷缩", "浊响", "清晰", "凹陷", "硬滑", "是"],
               ["乌黑", "蜷缩", "沉闷", "清晰", "凹陷", "硬滑", "是"],
               ["乌黑", "蜷缩", "浊响", "清晰", "凹陷", "硬滑", "是"],
               ["青绿", "蜷缩", "沉闷", "清晰", "凹陷", "硬滑", "是"],
               ["浅白", "蜷缩", "浊响", "清晰", "凹陷", "硬滑", "是"],
               ["青绿", "稍蜷", "浊响", "清晰", "稍凹", "软粘", "是"],
               ["乌黑", "稍蜷", "浊响", "稍糊", "稍凹", "软粘", "是"],
               ["乌黑", "稍蜷", "浊响", "清晰", "稍凹", "硬滑", "是"],
               ["乌黑", "稍蜷", "沉闷", "稍糊", "稍凹", "硬滑", "否"],
               ["青绿", "硬挺", "清脆", "清晰", "平坦", "软粘", "否"],
               ["浅白", "硬挺", "清脆", "模糊", "平坦", "硬滑", "否"],
               ["浅白", "蜷缩", "浊响", "模糊", "平坦", "软粘", "否"],
               ["青绿", "稍蜷", "浊响", "稍糊", "凹陷", "硬滑", "否"],
               ["浅白", "稍蜷", "沉闷", "稍糊", "凹陷", "硬滑", "否"],
               ["乌黑", "稍蜷", "浊响", "清晰", "稍凹", "软粘", "否"],
               ["浅白", "蜷缩", "浊响", "模糊", "平坦", "硬滑", "否"],
               ["青绿", "蜷缩", "沉闷", "稍糊", "稍凹", "硬滑", "否"], ]
    labels = ['色泽', '根蒂', '敲声', '纹理', '脐部', '触感']
    # [是否可以浮出水面,是否有脚蹼]
    return dataSet, labels


if __name__ == '__main__':
    data, label = createDataSet()
    myTree = retrieveTree(0)
    result = classify(myTree, label, ['浅白', '蜷缩', '浊响', '稍糊', '凹陷', '硬滑'])
    if result == 'yes':
        print("好瓜")
    else:
        print("不是好瓜")

