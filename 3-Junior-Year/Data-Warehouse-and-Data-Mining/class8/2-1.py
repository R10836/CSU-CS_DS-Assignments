from math import log

def calEnt(dataset):
    numEntries=len(dataset)
    labelCounts={}
    #给所有可能分类创建字典
    for featVec in dataset:
        currentlabel=featVec[-1]
        if currentlabel not in labelCounts.keys():
            labelCounts[currentlabel]=0
        labelCounts[currentlabel]+=1
    ent=0.0
    #********** Begin **********#
    #遍历标签
    for key in labelCounts:
        #计算
        p = float(labelCounts[key])/numEntries
        #以2为底求对数计算信息熵
        ent -= p*log(p, 2)
    #********** End **********#
    return ent