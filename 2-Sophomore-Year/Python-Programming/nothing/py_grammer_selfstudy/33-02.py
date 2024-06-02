# -*- coding: utf-8 -*-
# File: 33-02.py
# Author: Ru Shawn
# Date: 2024/5/20
# Last Modified: 2024/5/20
# Description: 

# 超时了
# if __name__ == "__main__":
#     n, m = map(int, input().split())
#     paper1_set = set(input().split())
#     paper2_set = set(input().split())
#     # print(n, m, paper1_list, paper2_list)
#
#     set1 = set()
#     for item in paper1_set:
#         set1.add(item.lower())
#     # print(set1)
#
#     set2 = set()
#     for item in paper2_set:
#         set2.add(item.lower())
#     # print(set2)
#
#     nn = 0
#     uu = len(set1) + len(set2)
#
#     for item in set1:
#         for jtem in set2:
#             if item == jtem:
#                 uu -= 1
#                 nn += 1
#
#     print(nn)
#     print(uu)

if __name__ == "__main__":
    n, m = map(int, input().split())
    paper1_set = set(input().split())
    paper2_set = set(input().split())
    # print(n, m, paper1_list, paper2_list)

    set1 = set()
    for item in paper1_set:
        set1.add(item.lower())
    # print(set1)

    set2 = set()
    for item in paper2_set:
        set2.add(item.lower())
    # print(set2)

    intersection_set = set1 & set2
    union_set = set1 | set2
    print(len(intersection_set))
    print(len(union_set))
