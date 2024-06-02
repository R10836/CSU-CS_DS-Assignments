# -*- coding: utf-8 -*-
# File: 01-2.py
# Author: Ru Shawn
# Date: 2024/5/17
# Last Modified: 2024/5/17
# Description: 

if __name__ == "__main__":
    N, M = map(int, input().split())

    window_list = []
    for i in range(N):
        x1, y1, x2, y2 = map(int, input().split())
        window = (x1, y1, x2, y2, i+1)
        window_list.append(window)

    for j in range(M):
        x, y = map(int, input().split())

        for i in range(len(window_list)-1, -1, -1):  # 惯例：倒序遍历列表
            xx1 = window_list[i][0]
            xx2 = window_list[i][2]
            yy1 = window_list[i][1]
            yy2 = window_list[i][3]
            ii = window_list[i][4]
            # print(xx1, yy1, xx2, yy2, ii)

            if xx1 <= x <= xx2 and yy1 <= y <= yy2:
                print(ii)
                window_list.append(window_list.pop(i))
                break

            if i == 0:
                print("IGNORED")