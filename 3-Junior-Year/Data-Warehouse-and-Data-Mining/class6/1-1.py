def load_Lksub1():
    Lksub1 = [frozenset(['l2', 'l3']),
              frozenset(['l1', 'l3']), frozenset(['l2', 'l1']), frozenset(['l2', 'l5'])]
    return Lksub1


def load_Ck_item1():
    Ck_item = frozenset(['l1', 'l2', 'l3'])
    return Ck_item


def load_Ck_item2():
    Ck_item = frozenset(['l1', 'l2', 'l5'])
    return Ck_item


def is_apriori(Ck_item, Lksub1):
    """
    判断频繁的候选k项目集是否满足Apriori属性；
    Ck_item：Ck中的一个频繁候选k-itemset，其中包含所有频繁候选k项集；
    Lksub1：Lk-1，一个包含所有频繁候选（k-1）个项目集的集合；
    满足Apriori属性返回True；
    不满足Apriori属性返回False。
    """
    # 判断Ck_item中的每个(k-1)项子集是否在Lksub1中
    for item in Ck_item:
        # 从Ck_item中移除一个项，得到(k-1)项子集
        subset = Ck_item - frozenset([item])
        # 如果子集不在Lksub1中，则不满足Apriori属性，返回False
        if subset not in Lksub1:
            return False
    # 所有子集都在Lksub1中，满足Apriori属性，返回True
    return True


if __name__ == "__main__":
    Ck_item1 = load_Ck_item1()
    Ck_item2 = load_Ck_item2()
    Lksub1 = load_Lksub1()

    if is_apriori(Ck_item1, Lksub1):
        print("true")
    else:
        print("false")

    if is_apriori(Ck_item2, Lksub1):
        print("true")
    else:
        print("false")
