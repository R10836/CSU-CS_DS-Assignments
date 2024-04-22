def fun(i):
    # **********Program**********
    bai = i // 100  # /：普通的除法运算符。它执行除法并返回一个浮点数结果，即使被除数和除数都是整数。
    shi = (i - bai * 100) // 10  # //：整数除法运算符。它执行除法并返回结果的整数部分，舍弃小数部分。
    ge = i - bai * 100 - shi * 10
    if (bai ** 3 + shi ** 3 + ge ** 3) == i:
        return True
    else:
        return False

    # **********  End  **********


def main():
    a = int(input("【请输入一个三位数，并按回车确认:】"))
    flag = fun(a);
    if flag:
        print("%d是【水仙花数】" % a);
    else:
        print("%d不是【水仙花数】" % a);


if __name__ == '__main__':
    main()
