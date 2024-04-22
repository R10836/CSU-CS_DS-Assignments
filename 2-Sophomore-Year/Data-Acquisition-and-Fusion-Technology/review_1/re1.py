# import test_tool
from test_tool import *

a = 3
b = 3.02
c = 'asd'
str = 'abcdefghijklmnopqrstuvwxyz'
# c1 = '435'
# cc = '1233\n21'
# ccc = '1233\\n21'
# type_a = type(a)
# type_b = type(b)
# type_c = type(c)
str1 = 'qweD'
str2 = 'qe'
# print(a**a, b, c, cc, ccc, type_a, type_b, type_c, float(a), int(b), int(c1), str(b))

# 这两种表述相等
print(str1 + 'ppp%fppp%d%s' % (b*100, a, c) + str2)
# print(str1 + f"ppp{b*100}ppp{a}{c}" + str2)



# 获取用户输入的数字
# number = int(input("请输入一个数字: "))

# 判断数字的正负性并输出结果
# if number > 0:
#     print("输入的数字是正数")
# elif number < 0:
#     print("输入的数字是负数")
# else:
#     print("输入的数字是零")


# qwe = 12
# print(f'{qwe}' + 'one')
#
# def fuck():
#     global qwe
#     qwe = 777
#     print(f'{qwe}' + 'two')
# fuck()
#
# print(f'{qwe}' + 'three')

# # 定义一个包含整数的列表
# numbers = [1, 2.02022, 'dddw2s2dwq3ddd', True, [111, 2.22222, 'qaz']]
#
# # 打印整个列表
# print(numbers)
# for i in numbers:
#     print(f'{i}' + '的类型是：' f'{type(i)}')
#
# # 打印列表中的特定元素
# print("第一个元素:", numbers[0])
# print("最后一个元素:", numbers[-1])
#
# cut_str = str[0:22:3]
# print(cut_str)

# def get_user_info():
#     name = "John"
#     age = 25
#     email = "john@example.com"
#     return name, age, email
#
# # 调用函数并获取返回值
# user_allinfo = get_user_info()
# user_name, user_age, user_email = get_user_info()
#
# # 打印返回值
# print(user_allinfo)
# print(user_name, user_age * 12, user_email)

# def info(*args):
#     print(args)
#     return "Function executed successfully."
#
# print(info('tom'))
# print(info('tom', 18, 3.23))
#
# try:
#     f = open('fuck.txt', 'r')
#     print('this is try.')
# except:
#     f = open('fuck.txt', 'w')
#     print('this is except.')

# print(test_tool.ttttt)
# print(ttttt)
# print(test_tool.tool1(b, a))

