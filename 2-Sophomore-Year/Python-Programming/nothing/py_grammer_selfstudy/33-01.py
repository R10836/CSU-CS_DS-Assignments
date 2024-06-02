# -*- coding: utf-8 -*-
# File: 33-01.py
# Author: Ru Shawn
# Date: 2024/5/20
# Last Modified: 2024/5/20
# Description:


if __name__ == "__main__":
    n, m = map(int, input().split())
    d_int_list = []
    for i in range(1, n + 1):
        int_list = input().split()
        int_list.remove(int_list[0])
        d_int_list.append(int_list)
    # print(d_int_list)
    # [['1', '2', '3', '2', '1'], ['1'], ['2', '2', '2'], ['3', '2']]

    my_dict = {}
    for i in range(1, m + 1):
        my_dict[i] = [0, 0]
        for j in range(1, n + 1):
            flag = False
            for letter in d_int_list[j - 1]:
                if i == int(letter):
                    flag = True
                    my_dict[i][1] += 1
            if flag:
                my_dict[i][0] += 1
    # print(my_dict)
        print(f'{my_dict[i][0]} {my_dict[i][1]}')

    # 错误弯路：
    # for i in range(1, n+1):
    #     flag = 0
    #     for letter in d_int_list[i-1]:
    #         if i == int(letter):
    #             flag = 1
    #             my_dict[i][1] += 1
    #     if flag == 1:
    #         my_dict[i][0] += 1
    # print(my_dict)
