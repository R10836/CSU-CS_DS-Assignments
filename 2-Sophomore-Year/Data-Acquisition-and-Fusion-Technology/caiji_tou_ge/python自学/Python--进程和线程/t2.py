import threading
import math

ans = 0
lock = threading.Lock()


# 判断数字是否为质数
# ********** Begin *********#
def isPrime(n):
    if n < 2:
        return False
    for i in range(2, int(math.sqrt(n)) + 1):
        if n % i == 0:
            return False
    return True


# ********** End *********#

# 计算给定区间含有多少个质数
# ********** Begin *********#
def howMany(T):
    global ans
    local_count = 0
    for num in T:
        if isPrime(num):
            local_count += 1
    with lock:
        ans += local_count


# ********** End *********#

# 对整个数字空间N进行分段CPU_COUNT
# ********** Begin *********#
def separateNum(N, threadNum):
    sepList = []
    step = N // threadNum
    for i in range(threadNum):
        start = i * step + 1
        end = (i + 1) * step if i != threadNum - 1 else N
        sepList.append(list(range(start, end + 1)))
    return sepList


# ********** End *********#

if __name__ == '__main__':
    N = int(input())
    threadNum = 32
    t = []
    sepList = separateNum(N, threadNum)
    for i in range(threadNum):
        t.append(threading.Thread(target=howMany, args=(sepList[i],)))
        t[i].start()
    for i in range(threadNum):
        t[i].join()
    print(N - 1 - ans, end='')
