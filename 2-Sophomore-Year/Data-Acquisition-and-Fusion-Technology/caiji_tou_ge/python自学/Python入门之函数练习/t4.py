def fun(s):
    # **********Program**********
    if s[0] == s[-1] and s[1] == s[-2]: # 将if语句补充完整
        return True
    else:
        return False
    # **********  End  **********


def main():
    s = input("【请输入一个5位字符:】")
    if len(s) != 5:
        s = input("【输入错误，请重新输入:】")
    else:
        if fun(s):
            print("%s是【回文数】" % s)
        else:
            print("%s不是【回文数】" % s)


if __name__ == '__main__':
    main()
