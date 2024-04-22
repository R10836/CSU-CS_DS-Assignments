from math import log


def calEnt(dataset):
    numEntries = len(dataset)
    labelCounts = {}
    # 给所有可能分类创建字典
    for featVec in dataset:
        currentlabel = featVec[-1]
        if currentlabel not in labelCounts.keys():
            labelCounts[currentlabel] = 0
        labelCounts[currentlabel] += 1
    ent = 0.0
    for key in labelCounts:
        p = float(labelCounts[key]) / numEntries
        # 以2为底求对数计算信息熵
        ent = ent - p * log(p, 2)
    return ent


def splitdataset(dataset, axis, value):
    retdataset = []  # 创建返回的数据集列表
    for featVec in dataset:  # 抽取符合划分特征的值
        if featVec[axis] == value:
            reducedfeatVec = featVec[:axis]  # 去掉axis特征
            reducedfeatVec.extend(featVec[axis + 1:])  # 将符合条件的特征添加到返回的数据集列表
            retdataset.append(reducedfeatVec)
    return retdataset


def C45_chooseBestFeatureToSplit(dataset):
    numFeatures = len(dataset[0]) - 1
    baseEnt = calEnt(dataset)
    bestInfoGain_ratio = 0.0
    bestFeature = -1
    for i in range(numFeatures):  # 遍历所有特征
        featList = [example[i] for example in dataset]
        uniqueVals = set(featList)  # 将特征列表创建成为set集合，元素不可重复。创建唯一的分类标签列表
        newEnt = 0.0
        IV = 0.0
        for value in uniqueVals:  # 计算每种划分方式的信息熵
            subdataset = splitdataset(dataset, i, value)
            p = len(subdataset) / float(len(dataset))
            newEnt += p * calEnt(subdataset)
            IV = IV - p * log(p, 2)
        infoGain = baseEnt - newEnt
        if (IV == 0):
            continue
        infoGain_ratio = infoGain / IV  # 此次feature的infoGain_ratio
        # ********** Begin **********#
        if infoGain_ratio > bestInfoGain_ratio:
            bestInfoGain_ratio = infoGain_ratio
            bestFeature = i
        # ********** End **********#
    return bestFeature