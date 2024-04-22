import time
import decimal

def factorial(n):
    result = 1
    for i in range(1, n + 1):
        result *= decimal.Decimal(i)
    return result

def factorial_sum(n):
    result = decimal.Decimal(0)
    for i in range(1, n + 1):
        result += factorial(i)
    return result

while True:
    try:
        n = int(input("请输入一个正整数 n (输入负数退出): "))

        if n < 0:
            print("程序退出。")
            break

        decimal.getcontext().prec = 200  # 设置精度，根据需要调整
        start_time = time.time()
        result = factorial_sum(n)
        end_time = time.time()
        print(f"n={n}, 结果={result}, 运行时间={end_time - start_time}秒")
    except ValueError:
        print("请输入有效的正整数。")
