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
            # ********* Begin *******#

            subDataSet = splitDataSet(dataSet, i, value)
            prob = len(subDataSet) / float(len(dataSet))
            newEntropy += prob * calcShannonEnt(subDataSet)

            # ********* End *********#
        infoGain = baseEntropy - newEntropy
        if (infoGain > bestInfoGain):  # 选择信息增益最大的属性
            bestInfoGain = infoGain
            bestFeature = i
    return bestFeature


print(chooseBestFeatureToSplit(dataSet))