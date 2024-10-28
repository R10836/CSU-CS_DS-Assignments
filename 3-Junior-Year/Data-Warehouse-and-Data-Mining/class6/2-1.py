def loadSimpDat():  # �������ݼ�
    simpDat = [['beer', 'milk', 'chicken'], ['milk', 'bread'], ['milk', 'diaper'],
               ['beer', 'milk', 'bread'], ['beer', 'diaper'], ['milk', 'diaper'],
               ['beer', 'diaper'], ['beer', 'milk', 'diaper', 'chicken'], ['beer', 'milk', 'diaper']]
    return simpDat


def createInitSet(dataSet):  # �������ݼ�����Ϊ ����¼������������ʽ
    retDict = {}
    for trans in dataSet:
        fset = frozenset(trans)
        retDict.setdefault(fset, 0)
        retDict[fset] += 1
    return retDict


class treeNode:  # �������ڵ�
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
    # ��һ�α������ݼ��� ��¼ÿ���������֧�ֶ�,����headerTable��
    for trans in dataSet:
        for item in trans:
            headerTable[item] = headerTable.get(item, 0) + 1

    # ������С֧�ֶȹ���
    lessThanMinsup = list(filter(lambda k: headerTable[k] < minSup, headerTable.keys()))
    for k in lessThanMinsup: del (headerTable[k])

    freqItemSet = set(headerTable.keys())
    # ����������ݶ���������С֧�ֶȣ�����None, None
    if len(freqItemSet) == 0:
        return None, None

    for k in headerTable:
        headerTable[k] = [headerTable[k], None]
    # ��ʼ��FP�������������ڵ�null
    retTree = treeNode('��', 1, None)
    # print (headerTable)
    # �ڶ��α������ݼ�������fp-tree
    for tranSet, count in dataSet.items():
        # ������С֧�ֶȴ���һ��ѵ��������key:�����е�һ��������value:�������ĵ�ȫ��֧�ֶ�
        localD = {}
        # �������������е�ÿ��Ԫ��
        # ����ÿ����¼��֧�ֶ�С����С֧�ֶȵ�Ԫ��
        # ��headerTable�м�¼�ĸ�Ԫ�صĳ��ִ�����ֵ��localD�еĶ�ӦԪ��
        # ********** Begin **********#
        for item in tranSet:
            if item in freqItemSet:
                localD[item] = headerTable[item][0]

                # ********** End **********#

        if len(localD) > 0:
            # ����ȫ��Ƶ�����ÿ�������е����ݽ�������,�ȼ��� order by p[1] desc, p[0] desc
            orderedItems = [v[0] for v in sorted(localD.items(), key=lambda p: (p[1], p[0]), reverse=True)]
            # print (orderedItems)
            updateTree(orderedItems, retTree, headerTable, count)
    return retTree, headerTable


# ����items�е�����FP���в���ڵ�
def updateTree(items, inTree, headerTable, count):
    # �ж�items�ĵ�һ���Ƿ�����Ϊ���ڵ�null���ӽ��,�ǵĻ����Ӽ���
    # ********** Begin **********#
    if items[0] in inTree.children:
        inTree.children[items[0]].inc(count)
    else:
        inTree.children[items[0]] = treeNode(items[0], count, inTree)

        # ********** End **********#
        # �����ӽ���򴴽��·�֧������headerTable��ָ����£����´����Ѹ�����
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