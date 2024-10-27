import numpy as np
from scipy import stats

# 计算异众比率（只适用于分类数据）
def calculate_mode_discrepancy(data):
    unique_elements, counts = np.unique(data, return_counts=True)
    mode_index = np.argmax(counts)
    mode_count = counts[mode_index]
    total_count = len(data)
    mode_discrepancy = 1 - (mode_count / total_count)
    return mode_discrepancy

# 计算四分位差（只适用于顺序数据）
def calculate_interquartile_range(data):
    q3, q1 = np.percentile(data, [75 ,25])
    interquartile_range = q3 - q1
    return interquartile_range

# 计算方差和标准差（适用于数值型数据）
def calculate_variance_and_std(data):
    variance = np.var(data)
    std_deviation = np.std(data)
    return variance, std_deviation

# 计算标准分数（适用于数值型数据）
def calculate_z_scores(data):
    z_scores = stats.zscore(data)
    return z_scores

# 计算离散系数（适用于数值型数据）
def calculate_coefficient_of_variation(data):
    mean_value = np.mean(data)
    std_deviation = np.std(data)
    coefficient_of_variation = (std_deviation / mean_value) * 100
    return coefficient_of_variation

# 示例用法
# 分类数据
category_data = np.array(['A', 'B', 'B', 'C', 'A', 'B', 'B', 'B'])
mode_discrepancy = calculate_mode_discrepancy(category_data)
print("异众比率:", mode_discrepancy)

# 顺序数据
ordinal_data = np.array([10, 15, 20, 25, 30, 35, 40, 45])
interquartile_range = calculate_interquartile_range(ordinal_data)
print("四分位差:", interquartile_range)

# 数值型数据
numeric_data = np.array([15, 20, 25, 30, 35, 40, 45, 50])
variance, std_deviation = calculate_variance_and_std(numeric_data)
print("方差:", variance)
print("标准差:", std_deviation)

z_scores = calculate_z_scores(numeric_data)
print("标准分数:", z_scores)

coefficient_of_variation = calculate_coefficient_of_variation(numeric_data)
print("离散系数:", coefficient_of_variation)
