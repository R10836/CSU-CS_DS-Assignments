# -*- coding: utf-8 -*-
# File: 01-3.py
# Author: Ru Shawn
# Date: 2024/5/19
# Last Modified: 2024/5/19
# Description: 30%

if __name__ == "__main__":
    # 1、输入
    format_str = input()
    N = int(input())
    command_list = []
    for i in range(N):
        command = input()
        command_list.append(command)
    # print(format_str)
    # print(N)
    # print(command_list)

    # 2、分析格式字符串
    none_num_list = []
    with_num_list = []
    for i in range(len(format_str)-1):
        if format_str[i+1] == ":":
            with_num_list.append(format_str[i])
        elif format_str[i+1] != ":" and format_str[i] != ":":
            none_num_list.append(format_str[i])
    if format_str[-1] != ":":
        none_num_list.append(format_str[-1])
    # print(none_num_list)
    # print(with_num_list)

    # 3、处理命令行
    for i in range(N):
        print(f'Case {i+1}: ', end='')

        now_command = command_list[i]
        word_list = command_list[i].split(' ')
        # print(word_list, end='')
        if len(word_list) <= 1:  # 处理只有命令行工具的名字的情况
            print()
            continue

        # 处理命令行正文
        output_list = []
        for j in range(1, len(word_list)):
            if word_list[j][0] == '-':
                if word_list[j][1] in none_num_list:
                    if (word_list[j], None) not in output_list:  # 删除重复
                        output_list.append((word_list[j], None))
                elif word_list[j][1] in with_num_list:
                    if j == len(word_list)-1:
                        print()
                        break
                    num = int(word_list[j + 1])
                    output_list.append((word_list[j], num))
                    for item in output_list:  # 删除重复
                        if type(item) == tuple and item[0] == word_list[j]:
                            if int(item[1]) < num:
                                output_list.remove(item)
                    word_list[j+1] = '@'  # 占坑拉屎大法
                else:
                    break
            elif word_list[j][0] == '@':
                continue
            else:
                break
        # print(output_list, end='')
        # Case 1: [('-a', None), ('-l', None)]
        # Case 2:
        # Case 3: [('-x', None), ('-w', 15)]
        # Case 4: [('-a', None), ('-b', None)]

        # 排序
        for j in range(0, len(output_list)-1):
            for k in range(1, len(output_list)):
                if output_list[j][0][1] > output_list[k][0][1]:
                    temp = output_list[j]
                    output_list[j] = output_list[k]
                    output_list[k] = temp

        # 输出
        for item in output_list:
            if item[1] is None:
                print(f"{item[0]}", end='')
            else:
                print(f"{item[0]} {item[1]}", end='')
            if item != output_list[-1]:
                print(' ', end='')

        if i != N-1:
            print()
