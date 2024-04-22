# 定义组别、频数
groups = [[2, 3], [7, 8], [12, 13], [17, 18]]
frequencies = [4, 6, 10, 5]

# 将数据按照频数展开
data = []
for i in range(len(groups)):
    lower_bound, upper_bound = groups[i]
    for j in range(frequencies[i]):
        data.append((lower_bound + upper_bound) / 2)  # 使用组中值表示频数

# 计算平均差
mean_deviation = sum(abs(x - sum(data) / len(data)) for x in data) / len(data)

# 计算方差
mean = sum(data) / len(data)
variance = sum((x - mean) ** 2 for x in data) / len(data)

print("平均差:", round(mean_deviation, 2))
print("方差:", round(variance, 2))
