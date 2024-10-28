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
        # �ж�items�ĵ�һ������Ƿ�����Ϊ�ӽ��
        inTree.children[items[0]].inc(count)
    else:
        # �����µķ�֧
        inTree.children[items[0]] = treeNode(items[0], count, inTree)
        # ������ӦƵ����������������
        if headerTable[items[0]][1] == None:
            headerTable[items[0]][1] = inTree.children[items[0]]
        else:
            updateHeader(headerTable[items[0]][1], inTree.children[items[0]])
    # �ݹ�
    if len(items) > 1:
        updateFPtree(items[1::], inTree.children[items[0]], headerTable, count)


def createFPtree(dataSet, minSup=1):
    headerTable = {}
    for trans in dataSet:
        for item in trans:
            headerTable[item] = headerTable.get(item, 0) + dataSet[trans]
    for k in list(headerTable):  # py2.7��д��for k in headerTable.keys() �˴�Ϊpy3.x
        if headerTable[k] < minSup:
            del (headerTable[k])  # ɾ����������С֧�ֶȵ�Ԫ��
    freqItemSet = set(headerTable.keys())  # ������С֧�ֶȵ�Ƶ���
    if len(freqItemSet) == 0:
        return None, None
    for k in headerTable:
        headerTable[k] = [headerTable[k], None]  # element: [count, node]

    retTree = treeNode('Null Set', 1, None)
    # print (headerTable)
    for tranSet, count in dataSet.items():
        # dataSet��[element, count]
        localD = {}
        for item in tranSet:
            if item in freqItemSet:  # ���ˣ�ֻȡ��������������С֧�ֶȵ�Ƶ����
                localD[item] = headerTable[item][0]  # element : count
        if len(localD) > 0:
            # ����ȫ��Ƶ���Ӵ�С�Ե���������
            orderedItem = [v[0] for v in sorted(localD.items(), key=lambda p: (p[1], p[0]), reverse=True)]
            # print (orderedItem)
            # �ù���������������������
            updateFPtree(orderedItem, retTree, headerTable, count)
    return retTree, headerTable


# ���ݼ�
def loadSimpDat():
    simDat = [['beer', 'milk', 'chicken'], ['milk', 'bread'], ['milk', 'diaper'],
              ['beer', 'milk', 'bread'], ['beer', 'diaper'], ['milk', 'diaper'],
              ['beer', 'diaper'], ['beer', 'milk', 'diaper', 'chicken'], ['beer', 'milk', 'diaper']]
    return simDat


# ����� element : count ����ʽ
def createInitSet(dataSet):
    retDict = {}
    for trans in dataSet:
        key = frozenset(trans)
        if key in retDict:
            retDict[frozenset(trans)] += 1
        else:
            retDict[frozenset(trans)] = 1
    return retDict


# �ݹ����
def ascendFPtree(leafNode, prefixPath):
    if leafNode.parent != None:
        prefixPath.append(leafNode.name)
        ascendFPtree(leafNode.parent, prefixPath)


# ����ģʽ��
def findPrefixPath(basePat, myHeaderTab):
    treeNode = myHeaderTab[basePat][1]  # basePat��FP���еĵ�һ�����
    condPats = {}
    # ��treenode������
    # ��������ǰ׺·��
    # ���õݹ���ݺ���
    # ǰ׺������Ϊ����condPats�Ķ�Ӧ�������Ϊ��ǰtreenode�ļ���ֵ
    # treenode��תΪ��ǰ����FP������һ���ڵ�
    # ********** Begin **********#

    while treeNode != None:
        prefixPath = []
        ascendFPtree(treeNode, prefixPath)
        if len(prefixPath) > 1:
            condPats[frozenset(prefixPath[1:])] = treeNode.count
        treeNode = treeNode.nodeLink

    # ********** End **********#
    return condPats


def mineFPtree(inTree, headerTable, minSup, preFix, freqItemList):  # �ھ�����FP��
    # �ʼ��Ƶ�����headerTable�еĸ�Ԫ��
    bigL = [v[0] for v in sorted(headerTable.items(), key=lambda p: str(p[1]))]  # ����Ƶ�������Ƶ������
    # print ('bigL:',bigL)
    for basePat in bigL:  # ��ÿ��Ƶ����
        newFreqSet = preFix.copy()
        newFreqSet.add(basePat)
        listFreqSet = sorted(list(newFreqSet), key=lambda i: i[0])
        # print ('��ǰƵ�����',newFreqSet)
        freqItemList.append(listFreqSet)
        # ��õ�ǰƵ���������ģʽ��
        # ���쵱ǰƵ�����FP��
        # ��ǰ���headtable��������ݹ��ھ�����FP��
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
