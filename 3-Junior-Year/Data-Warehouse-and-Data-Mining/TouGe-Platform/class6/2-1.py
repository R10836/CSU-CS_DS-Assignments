def loadSimpDat():  # 加载数据集
    simpDat = [['beer', 'milk', 'chicken'], ['milk', 'bread'], ['milk', 'diaper'],
               ['beer', 'milk', 'bread'], ['beer', 'diaper'], ['milk', 'diaper'],
               ['beer', 'diaper'], ['beer', 'milk', 'diaper', 'chicken'], ['beer', 'milk', 'diaper']]
    return simpDat


def createInitSet(dataSet):  # 处理数据集，化为 （记录，计数）的形式
    retDict = {}
    for trans in dataSet:
        fset = frozenset(trans)
        retDict.setdefault(fset, 0)
        retDict[fset] += 1
    return retDict


class treeNode:  # 构造树节点
    def __init__(self, nameValue, numOccur, parentNode):
        self.name = nameValue
        self.count = numOccur
        self.nodeLink = None
        self.parent = parentNode
        self.children = {}

    def inc(self, numOccur):
        self.count += numOccur

    def disp(self, ind=1):
        print('   ' * ind, self.name, ' ', self.count)
        for child in self.children.values():
            child.disp(ind + 1)


def createTree(dataSet, minSup=1):
    headerTable = {}
    # 此一次遍历数据集， 记录每个数据项的支持度,存在headerTable中
    for trans in dataSet:
        for item in trans:
            headerTable[item] = headerTable.get(item, 0) + 1

    # 根据最小支持度过滤
    lessThanMinsup = list(filter(lambda k: headerTable[k] < minSup, headerTable.keys()))
    for k in lessThanMinsup: del (headerTable[k])

    freqItemSet = set(headerTable.keys())
    # 如果所有数据都不满足最小支持度，返回None, None
    if len(freqItemSet) == 0:
        return None, None

    for k in headerTable:
        headerTable[k] = [headerTable[k], None]
    # 初始化FP树，即创建根节点null
    retTree = treeNode('φ', 1, None)
    # print (headerTable)
    # 第二次遍历数据集，构建fp-tree
    for tranSet, count in dataSet.items():
        # 根据最小支持度处理一条训练样本，key:样本中的一个样例，value:该样例的的全局支持度
        localD = {}
        # 遍历这条数据中的每个元素
        # 过滤每条记录中支持度小于最小支持度的元素
        # 把headerTable中记录的该元素的出现次数赋值给localD中的对应元素
        # ********** Begin **********#
        for item in tranSet:
            if item in freqItemSet:
                localD[item] = headerTable[item][0]

                # ********** End **********#

        if len(localD) > 0:
            # 根据全局频繁项对每个事务中的数据进行排序,等价于 order by p[1] desc, p[0] desc
            orderedItems = [v[0] for v in sorted(localD.items(), key=lambda p: (p[1], p[0]), reverse=True)]
            # print (orderedItems)
            updateTree(orderedItems, retTree, headerTable, count)
    return retTree, headerTable


# 根据items中的项往FP树中插入节点
def updateTree(items, inTree, headerTable, count):
    # 判断items的第一项是否已作为根节点null的子结点,是的话增加计数
    # ********** Begin **********#
    if items[0] in inTree.children:
        inTree.children[items[0]].inc(count)
    else:
        inTree.children[items[0]] = treeNode(items[0], count, inTree)

        # ********** End **********#
        # 不是子结点则创建新分支，并将headerTable的指针更新（更新代码已给出）
        # ********** Begin **********#

        # ********** End **********#
        if headerTable[items[0]][1] == None:  # update header table
            headerTable[items[0]][1] = inTree.children[items[0]]
        else:
            updateHeader(headerTable[items[0]][1], inTree.children[items[0]])

    if len(items) > 1:  # call updateTree() with remaining ordered items
        updateTree(items[1:], inTree.children[items[0]], headerTable, count)


def updateHeader(nodeToTest, targetNode):  # this version does not use recursion
    while (nodeToTest.nodeLink != None):  # Do not use recursion to traverse a linked list!
        nodeToTest = nodeToTest.nodeLink
    nodeToTest.nodeLink = targetNode


simpDat = loadSimpDat()
dictDat = createInitSet(simpDat)
myFPTree, myheader = createTree(dictDat, 3)
myFPTree.disp()