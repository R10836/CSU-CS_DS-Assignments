from multiprocessing import Pool
from multiprocessing import cpu_count

N = int(input())
a = list(map(int, input().split()))


def howMany(T):
    ans = 0
    for i in range(T[0] - 1, T[1]):
        ans = max(ans, a[i])
    return ans


# 对整个数字空间N进行分段CPU_COUNT
def seprateNum(N, CPU_COUNT):
    list = [[i * (N // CPU_COUNT) + 1, (i + 1) * (N // CPU_COUNT)] for i in range(0, CPU_COUNT)]
    list[0][0] = 1
    if list[CPU_COUNT - 1][1] < N:
        list[CPU_COUNT - 1][1] = N
    return list


# 多进程
if __name__ == '__main__':
    # 获取CPU核心数
    CPU_COUNT = cpu_count()

    # 将整个数字空间N进行分段
    segments = seprateNum(N, CPU_COUNT)

    # 使用进程池
    with Pool(CPU_COUNT) as pool:
        # 将分段任务提交到进程池
        results = pool.map(howMany, segments)

    # 输出最终的最大值
    max_value = max(results)
    print(max_value)
