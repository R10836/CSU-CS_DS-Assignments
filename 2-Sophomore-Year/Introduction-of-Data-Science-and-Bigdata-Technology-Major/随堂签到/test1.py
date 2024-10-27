import statistics

data = [2, 7, 5, 8, 8, 10, 9, 4, 7, 2, 1, 8, 6, 5, 10, 7, 7, 9, 9, 6]

# 1. 众数
mode = statistics.mode(data)

# 2. 中位数
median = statistics.median(data)

# 3. 均值
mean = statistics.mean(data)

# 4. 几何平均数
geometric_mean = statistics.geometric_mean(data)

# 5. 四分位数
quartiles = statistics.quantiles(data, n=4)

# 6. 调和平均数
harmonic_mean = statistics.harmonic_mean(data)

# 7. 异众比率
mode_count = data.count(mode)
max_frequency = max(data.count(x) for x in data if x != mode)
amplitude_mode = mode_count / max_frequency

# 8. 四分位差
quartile_range = quartiles[2] - quartiles[0]

# 9. 极差
range_value = max(data) - min(data)

# 10. 平均差
mean_deviation = sum(abs(x - mean) for x in data) / len(data)

# 11. 方差和标准差
variance = statistics.variance(data)
standard_deviation = statistics.stdev(data)

# 12. 标准分数
z_scores = [(x - mean) / standard_deviation for x in data]

# 13. 离散分数
coefficient_of_variation = (standard_deviation / mean) * 100

# 输出结果，精确到两位小数
print("众数:", format(mode, ".2f"))
print("中位数:", format(median, ".2f"))
print("均值:", format(mean, ".2f"))
print("几何平均数:", format(geometric_mean, ".2f"))
print("四分位数:", [format(q, ".2f") for q in quartiles])
print("调和平均数:", format(harmonic_mean, ".2f"))
print("异众比率:", format(amplitude_mode, ".2f"))
print("四分位差:", format(quartile_range, ".2f"))
print("极差:", format(range_value, ".2f"))
print("平均差:", format(mean_deviation, ".2f"))
print("方差:", format(variance, ".2f"))
print("标准差:", format(standard_deviation, ".2f"))
print("标准分数:", [format(z, ".2f") for z in z_scores])
print("离散分数:", format(coefficient_of_variation, ".2f"))
