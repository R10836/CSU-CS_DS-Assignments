while 1:
    try:
        num = int(input())

        str = '.' * 2 * num
        print('start' + str + 'end')
    except EOFError:
        break

# # -*- coding: utf-8 -*-
#
# x = eval(input())
#
# #请在下面补充代码，完成程序功能
# ############Begin############
#
# print("start" + "." * (20 * x) + "end")
#
# ############End##############