# 读取输入
N = int(input())
numbers = list(map(int, input().split()))

# 使用集合来存储所有数
num_set = set(numbers)
count = 0

# 遍历集合，查找相反数对
for num in numbers:
    if -num in num_set:
        count += 1
        num_set.remove(num)
        num_set.remove(-num)

print(count)
