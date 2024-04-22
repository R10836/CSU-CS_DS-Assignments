import math
from multiprocessing import cpu_count
from multiprocessing import Pool

# 判断数字是否为质数
#********** Begin *********#
def isPrime(n):
    if n < 2:
        return False
    for i in range(2, int(math.sqrt(n)) + 1):
        if n % i == 0:
            return False
    return True

#********** End *********#

# 计算给定区间含有多少个质数
#********** Begin *********#
def howMany(T):
    count = 0
    for num in T:
        if isPrime(num):
            count += 1
    return count

#********** End *********#

# 对整个数字空间N进行分段CPU_COUNT
#********** Begin *********#
def separateNum(N, CPU_COUNT):
    sepList = []
    step = N // CPU_COUNT
    for i in range(CPU_COUNT):
        start = i * step + 1
        end = (i + 1) * step if i != CPU_COUNT - 1 else N
        sepList.append(list(range(start, end + 1)))
    return sepList

#********** End *********#

if __name__ == '__main__':
    N = int(input())
    # 多进程
    CPU_COUNT = cpu_count()  ##CPU内核数 本机为8
    pool = Pool(CPU_COUNT)
    sepList = separateNum(N, CPU_COUNT)
    result = []
    for i in range(CPU_COUNT):
        result.append(pool.apply_async(howMany, (sepList[i], )))
    pool.close()
    pool.join()
    ans = 0
    list = [res.get() for res in result]
    print(sum(list), end = '')
