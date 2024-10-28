from math import log

def calEnt(dataset):
    numEntries=len(dataset)
    labelCounts={}
    #�����п��ܷ��ഴ���ֵ�
    for featVec in dataset:
        currentlabel=featVec[-1]
        if currentlabel not in labelCounts.keys():
            labelCounts[currentlabel]=0
        labelCounts[currentlabel]+=1
    ent=0.0
    #********** Begin **********#
    #������ǩ
    for key in labelCounts:
        #����
        p = float(labelCounts[key])/numEntries
        #��2Ϊ�������������Ϣ��
        ent -= p*log(p, 2)
    #********** End **********#
    return ent