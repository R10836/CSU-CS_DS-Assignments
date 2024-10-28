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
    �ж�Ƶ���ĺ�ѡk��Ŀ���Ƿ�����Apriori���ԣ�
    Ck_item��Ck�е�һ��Ƶ����ѡk-itemset�����а�������Ƶ����ѡk���
    Lksub1��Lk-1��һ����������Ƶ����ѡ��k-1������Ŀ���ļ��ϣ�
    ����Apriori���Է���True��
    ������Apriori���Է���False��
    """
    # �ж�Ck_item�е�ÿ��(k-1)���Ӽ��Ƿ���Lksub1��
    for item in Ck_item:
        # ��Ck_item���Ƴ�һ����õ�(k-1)���Ӽ�
        subset = Ck_item - frozenset([item])
        # ����Ӽ�����Lksub1�У�������Apriori���ԣ�����False
        if subset not in Lksub1:
            return False
    # �����Ӽ�����Lksub1�У�����Apriori���ԣ�����True
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
