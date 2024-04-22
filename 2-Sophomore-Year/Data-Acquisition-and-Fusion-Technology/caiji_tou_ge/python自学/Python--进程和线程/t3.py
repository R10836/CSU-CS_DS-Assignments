import threading

x = threading.local()


def init():
    x.value = 0


def action():
    init()
    for i in range(1000000):
        x.value += 1
        x.value -= 1


# 获取输入值
initial_value = int(input())

# 设置全局变量 x 的初始值
x.value = initial_value

# 创建线程
threads = []

for i in range(10):
    threads.append(threading.Thread(target=action))

# 启动线程
for i in range(10):
    threads[i].start()

# 等待线程结束
for i in range(10):
    threads[i].join()

# 输出最终的 x 值
print(x.value)
