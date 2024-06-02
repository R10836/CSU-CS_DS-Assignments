# -*- coding: utf-8 -*-
# File: 32-01.py
# Author: Ru Shawn
# Date: 2024/5/21
# Last Modified: 2024/5/21
# Description: 

if __name__ == "__main__":
    n, m = map(int, input().split())
    loc_list = []
    for i in range(1, n):
        loc = []
        loc = input().split()
        loc_list.append(loc)
    print(loc_list)
