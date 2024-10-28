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


def create_C1(data_set):
    """
    Create frequent candidate 1-itemset C1 by scaning data set.
    Args:
        data_set: A list of transactions. Each transaction contains several items.
    Returns:
        C1: A set which contains all frequent candidate 1-itemsets
    """
    C1 = set()
    for t in data_set:
        for item in t:
            item_set = frozenset([item])
            C1.add(item_set)
    return C1


def is_apriori(Ck_item, Lksub1):
    """
    Judge whether a frequent candidate k-itemset satisfy Apriori property.
    Args:
        Ck_item: a frequent candidate k-itemset in Ck which contains all frequent
                 candidate k-itemsets.
        Lksub1: Lk-1, a set which contains all frequent candidate (k-1)-itemsets.
    Returns:
        True: satisfying Apriori property.
        False: Not satisfying Apriori property.
    """
    for item in Ck_item:
        sub_Ck = Ck_item - frozenset([item])
        if sub_Ck not in Lksub1:
            return False
    return True


def create_Ck(Lksub1, k):
    """
    Create Ck, a set which contains all all frequent candidate k-itemsets
    by Lk-1's own connection operation.
    Args:
        Lksub1: Lk-1, a set which contains all frequent candidate (k-1)-itemsets.
        k: the item number of a frequent itemset.
    Return:
        Ck: a set which contains all all frequent candidate k-itemsets.
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
            #若前k-2项相同，则合并
            if l1[0:(k-2)] == l2[0:(k-2)]:
                Ck_item = frozenset(set(l1) | set(l2))
                # pruning
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
        if (item_count[item] / t_num) >= min_support:
            Lk.add(item)
            support_data[item] = item_count[item] / t_num
    return Lk


def generate_L(data_set, k, min_support):
    """
    Generate all frequent itemsets.
    Args:
        data_set: A list of transactions. Each transaction contains several items.
        k: Maximum number of items for all frequent itemsets.
        min_support: The minimum support.
    Returns:
        L: The list of Lk.
        support_data: A dictionary. The key is frequent itemset and the value is support.
    """
    support_data = {}
    C1 = create_C1(data_set)
    L1 = generate_Lk_by_Ck(data_set, C1, min_support, support_data)
    Lksub1 = L1.copy()
    L = []
    L.append(Lksub1)
    for i in range(2, k+1):
        Ck = create_Ck(Lksub1, i)
        Lk = generate_Lk_by_Ck(data_set, Ck, min_support, support_data)
        if len(Lk) == 0:
            break
        Lksub1 = Lk.copy()
        L.append(Lksub1)
    return L, support_data


def generate_big_rules(L, support_data, min_conf):
    """
    Generate big rules from frequent itemsets.
    Args:
        L: The list of Lk.
        support_data: A dictionary. The key is frequent itemset and the value is support.
        min_conf: Minimal confidence.
    Returns:
        big_rule_list: A list which contains all big rules. Each big rule is represented
                       as a 3-tuple .
    """
    big_rule_list = []
    sub_set_list = []
    for i in range(0, len(L)):
        for freq_set in L[i]:
            for sub_set in sub_set_list:
                if sub_set.issubset(freq_set):
                    conf = support_data[freq_set] / support_data[freq_set - sub_set]
                    big_rule = (freq_set - sub_set, sub_set, conf)
                    if conf >= min_conf and big_rule not in big_rule_list:
                        big_rule_list.append(big_rule)
            sub_set_list.append(freq_set)
    return big_rule_list


if __name__ == "__main__":
    """
    Test
    """
    data_set = load_data_set()
    L, support_data = generate_L(data_set, k=3, min_support=0.2)
    big_rules_list = generate_big_rules(L, support_data, min_conf=0.7)
for Lk in L:
    print("=" * 50)
    print("frequent " + str(len(list(Lk)[0])) + "-itemsets\t\tsupport")
    print("=" * 50)
    temp1 = list()
    for freq_set in Lk:
        temp = list(freq_set)
        temp.sort()
        temp1.append(temp)
    temp1.sort()
    for s in temp1:
        print(s, support_data[frozenset(s)])

print("Big Rules")
temp1 = list()
for item in big_rules_list:
    temp = list(item[0])
    temp.sort()
    if temp not in temp1:
        temp1.append(temp)
temp1.sort()
for t in temp1:
    count = 0
    tempset = set()
    for item in big_rules_list:
        if item[0] == frozenset(t):
            count += 1
            tempset.add(item)
    if count == 1:
        for item in big_rules_list:
            if item[0] == frozenset(t):
                list0 = list(item[0])
                list0.sort()
                print(list0, "=>", list(item[1]), "conf: ", item[2])
    else:
        temp2 = list()
        for item in tempset:
            temp = list(item[1])
            temp.sort()
            if temp not in temp2:
                temp2.append(temp)
        temp2.sort()
        for a in temp2:
            for item in tempset:
                if item[1] == frozenset(a):
                    list0 = list(item[0])
                    list0.sort()
                    print(list0, "=>", a, "conf: ", item[2])

