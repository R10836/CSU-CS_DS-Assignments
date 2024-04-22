import numpy as np

# 计算众数
def calculate_mode(data):
    unique_elements, counts = np.unique(data, return_counts=True)
    mode_index = np.argmax(counts)
    mode = unique_elements[mode_index]
    mode_count = counts[mode_index]
    return mode, mode_count

# 计算中位数
def calculate_median(data):
    median = np.median(data)
    return median

# 计算均值和几何平均数
def calculate_means(data):
    mean = np.mean(data)
    geometric_mean = np.exp(np.mean(np.log(data)))
    return mean, geometric_mean

# 处理一维数组的情况
def calculate_statistics_1d(data):
    mode, mode_count = calculate_mode(data)
    median = calculate_median(data)
    mean, geometric_mean = calculate_means(data)
    return {
        "众数": mode,
        "众数出现次数": mode_count,
        "中位数": median,
        "均值": mean,
        "几何平均数": geometric_mean
    }

# 处理二维数组的情况
def calculate_statistics_2d(data):
    flattened_data = data.flatten()  # 将二维数组展平为一维数组
    return calculate_statistics_1d(flattened_data)

# 示例用法
# 一维数组
array_1d = np.array([1, 2, 2, 3, 4, 4, 4, 5])
result_1d = calculate_statistics_1d(array_1d)
print("一维数组的集中趋势测度:")
print(result_1d)

# 二维数组
array_2d = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
result_2d = calculate_statistics_2d(array_2d)
print("二维数组的集中趋势测度:")
print(result_2d)
