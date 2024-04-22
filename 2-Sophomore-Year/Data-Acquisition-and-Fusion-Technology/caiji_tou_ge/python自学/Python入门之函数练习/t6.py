def main():
    x = 1
    while x < 1001:
        # **********Program**********
        # 建立一个空列表，再用for循环，老师上课讲过
        lists = [i for i in range(1, x) if x % i == 0]

        # **********  End  **********
        if x == sum(lists):
            print("【完数为：】%d" % x)
            print("【它的真因子为：】%s" % lists)
        x += 1


if __name__ == '__main__':
    main()
