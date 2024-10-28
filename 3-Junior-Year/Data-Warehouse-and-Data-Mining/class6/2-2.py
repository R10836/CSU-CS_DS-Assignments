class treeNode:
    def __init__(self, nameValue, numOccur, parentNode):
        self.name = nameValue
        self.count = numOccur
        self.nodeLink = None
        self.parent = parentNode
        self.children = {}

    def inc(self, numOccur):
        self.count += numOccur

    def disp(self, ind=1):
        print('  ' * ind, self.name, ' ', self.count)
        for child in self.children.values():
            child.disp(ind + 1)


def updateHeader(nodeToTest, targetNode):
    while nodeToTest.nodeLink != None:
        nodeToTest = nodeToTest.nodeLink
    nodeToTest.nodeLink = targetNode


def updateFPtree(items, inTree, headerTable, count):
    if items[0] in inTree.children:
        # 判断items的第一个结点是否已作为子结点
        inTree.children[items[0]].inc(count)
    else:
        # 创建新的分支
        inTree.children[items[0]] = treeNode(items[0], count, inTree)
        # 更新相应频繁项集的链表，往后添加
        if headerTable[items[0]][1] == None:
            headerTable[items[0]][1] = inTree.children[items[0]]
        else:
            updateHeader(headerTable[items[0]][1], inTree.children[items[0]])
    # 递归
    if len(items) > 1:
        updateFPtree(items[1::], inTree.children[items[0]], headerTable, count)


def createFPtree(dataSet, minSup=1):
    headerTable = {}
    for trans in dataSet:
        for item in trans:
            headerTable[item] = headerTable.get(item, 0) + dataSet[trans]
    for k in list(headerTable):  # py2.7可写作for k in headerTable.keys() 此处为py3.x
        if headerTable[k] < minSup:
            del (headerTable[k])  # 删除不满足最小支持度的元素
    freqItemSet = set(headerTable.keys())  # 满足最小支持度的频繁项集
    if len(freqItemSet) == 0:
        return None, None
    for k in headerTable:
        headerTable[k] = [headerTable[k], None]  # element: [count, node]

    retTree = treeNode('Null Set', 1, None)
    # print (headerTable)
    for tranSet, count in dataSet.items():
        # dataSet：[element, count]
        localD = {}
        for item in tranSet:
            if item in freqItemSet:  # 过滤，只取该样本中满足最小支持度的频繁项
                localD[item] = headerTable[item][0]  # element : count
        if len(localD) > 0:
            # 根据全局频数从大到小对单样本排序
            orderedItem = [v[0] for v in sorted(localD.items(), key=lambda p: (p[1], p[0]), reverse=True)]
            # print (orderedItem)
            # 用过滤且排序后的样本更新树
            updateFPtree(orderedItem, retTree, headerTable, count)
    return retTree, headerTable


# 数据集
def loadSimpDat():
    simDat = [['beer', 'milk', 'chicken'], ['milk', 'bread'], ['milk', 'diaper'],
              ['beer', 'milk', 'bread'], ['beer', 'diaper'], ['milk', 'diaper'],
              ['beer', 'diaper'], ['beer', 'milk', 'diaper', 'chicken'], ['beer', 'milk', 'diaper']]
    return simDat


# 构造成 element : count 的形式
def createInitSet(dataSet):
    retDict = {}
    for trans in dataSet:
        key = frozenset(trans)
        if key in retDict:
            retDict[frozenset(trans)] += 1
        else:
            retDict[frozenset(trans)] = 1
    return retDict


# 递归回溯
def ascendFPtree(leafNode, prefixPath):
    if leafNode.parent != None:
        prefixPath.append(leafNode.name)
        ascendFPtree(leafNode.parent, prefixPath)


# 条件模式基
def findPrefixPath(basePat, myHeaderTab):
    treeNode = myHeaderTab[basePat][1]  # basePat在FP树中的第一个结点
    condPats = {}
    # 当treenode还存在
    # 声明变量前缀路径
    # 调用递归回溯函数
    # 前缀存在则为其在condPats的对应项计数，为当前treenode的计数值
    # treenode跳转为当前项在FP树的另一个节点
    # ********** Begin **********#

    while treeNode != None:
        prefixPath = []
        ascendFPtree(treeNode, prefixPath)
        if len(prefixPath) > 1:
            condPats[frozenset(prefixPath[1:])] = treeNode.count
        treeNode = treeNode.nodeLink

    # ********** End **********#
    return condPats


def mineFPtree(inTree, headerTable, minSup, preFix, freqItemList):  # 挖掘条件FP树
    # 最开始的频繁项集是headerTable中的各元素
    bigL = [v[0] for v in sorted(headerTable.items(), key=lambda p: str(p[1]))]  # 根据频繁项的总频次排序
    # print ('bigL:',bigL)
    for basePat in bigL:  # 对每个频繁项
        newFreqSet = preFix.copy()
        newFreqSet.add(basePat)
        listFreqSet = sorted(list(newFreqSet), key=lambda i: i[0])
        # print ('当前频繁项集：',newFreqSet)
        freqItemList.append(listFreqSet)
        # 获得当前频繁项集的条件模式基
        # 构造当前频繁项集的FP树
        # 当前项集的headtable还有项则递归挖掘条件FP树
        # ********** Begin **********#

        condPattBases = findPrefixPath(basePat, headerTable)
        myCondTree, myHead = createFPtree(condPattBases, minSup)
        if myHead != None:
            mineFPtree(myCondTree, myHead, minSup, newFreqSet, freqItemList)

        # ********** End **********#


simpDat = loadSimpDat()
initSet = createInitSet(simpDat)
retTree, headerTable = createFPtree(initSet, 3)
retTree.disp()
freqItems = []
# print ('headtable:',headerTable)
mineFPtree(retTree, headerTable, 3, set([]), freqItems)
print(freqItems)
