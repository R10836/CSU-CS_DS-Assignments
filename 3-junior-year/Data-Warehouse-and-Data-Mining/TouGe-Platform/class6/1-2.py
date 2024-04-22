#coding=utf-8
def load_data_set():
    """
    Load a sample data set (From Data Mining: Concepts and Techniques, 3th Edition)
    Returns:
        A data set: A list of transactions. Each transaction contains several items.
    """
    data_set = [['beer', 'milk', 'chicken'], ['milk', 'bread'], ['milk', 'diaper'],
            ['beer', 'milk', 'bread'], ['beer', 'diaper'], ['milk', 'diaper'],
            ['beer', 'diaper'], ['beer', 'milk', 'diaper', 'chicken'], ['beer', 'milk', 'diaper']]
    return data_set


def load_support_data():
    """
    Load a sample data set (From Data Mining: Concepts and Techniques, 3th Edition)
    Returns:
        A data set: A list of transactions. Each transaction contains several items.
    """
    support_data = {frozenset({'chicken'}): 0.2222222222222222, frozenset({'milk'}): 0.7777777777777778, frozenset({'beer'}): 0.6666666666666666, frozenset({'bread'}): 0.2222222222222222, frozenset({'diaper'}): 0.6666666666666666}
    return support_data


def load_C2():
    C2 = {frozenset({'diaper', 'chicken'}), frozenset({'chicken', 'bread'}), frozenset({'chicken', 'milk'}), frozenset({'diaper', 'bread'}), frozenset({'beer', 'bread'}), frozenset({'milk', 'bread'}), frozenset({'diaper', 'beer'}), frozenset({'diaper', 'milk'}), frozenset({'beer', 'milk'}), frozenset({'chicken', 'beer'})}
    return C2

def create_Ck(Lksub1, k):
    """
    通过Lk-1自己的连接操作,创建一个包含所有频繁出现的候选k个项集的集合Ck；
    Lksub1：Lk-1，一个包含所有频繁候选（k-1）个项目集的集合；
    k：频繁项目集的项目编号；
    返回：Ck；
    请补全代码。
    """
    Ck = set()
    len_Lksub1 = len(Lksub1)
    list_Lksub1 = list(Lksub1)
    for i in range(len_Lksub1):
        for j in range(i+1, len_Lksub1):
            l1 = list(list_Lksub1[i])
            l2 = list(list_Lksub1[j])
            l1.sort()
            l2.sort()
            # 判断前(k-2)项是否相同
            if l1[0:(k-2)] == l2[0:(k-2)]:
                # 合并两个集合，得到k项集
                Ck_item = frozenset(set(l1) | set(l2))
                # 判断是否满足Apriori属性
                if is_apriori(Ck_item, Lksub1):
                    Ck.add(Ck_item)
    return Ck

def generate_Lk_by_Ck(data_set, Ck, min_support, support_data):
    """
    Generate Lk by executing a delete policy from Ck.
    Args:
        data_set: A list of transactions. Each transaction contains several items.
        Ck: A set which contains all all frequent candidate k-itemsets.
        min_support: The minimum support.
        support_data: A dictionary. The key is frequent itemset and the value is support.
    Returns:
        Lk: A set which contains all all frequent k-itemsets.
    """
    Lk = set()
    item_count = {}
    for t in data_set:
        for item in Ck:
            if item.issubset(t):
                if item not in item_count:
                    item_count[item] = 1
                else:
                    item_count[item] += 1
    t_num = float(len(data_set))
    for item in item_count:
        # 计算支持度
        support = item_count[item] / t_num
        # 判断支持度是否大于等于最小支持度
        if support >= min_support:
            Lk.add(item)
            # 保存支持度计数
            support_data[item] = support
    return Lk

if __name__ == "__main__":
    data_set = load_data_set()
    C2 = load_C2()
    support_data = load_support_data()
    L2 = generate_Lk_by_Ck(data_set, C2, 0.2, support_data)
    temp1 = list()
    for freq_set in L2:
        temp = list(freq_set)
        temp.sort()
        temp1.append(temp)
    temp1.sort()
    for s in temp1:
        print(s, support_data[frozenset(s)])
