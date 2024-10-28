import torch

# 构造标量
scalar = torch.tensor(3.14)
print("标量:", scalar)

# 构造向量
vector = torch.tensor([1, 2, 3])
print("向量:", vector)

# 构造矩阵
matrix = torch.tensor([[1, 2, 3], [4, 5, 6]])
print("矩阵:\n", matrix)

# 构造3维张量
tensor_3d = torch.tensor([[[1, 2], [3, 4]], [[5, 6], [7, 8]]])
print("3维张量:\n", tensor_3d)

# 切片张量
slice_tensor = tensor_3d[0, :, :]
print("切片后的张量:\n", slice_tensor)

# 检查是否有可用的GPU
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print("使用的设备:", device)

# 在GPU上创建张量
gpu_tensor = torch.tensor([1, 2, 3], device=device)
print("GPU上的张量:", gpu_tensor)

# 张量加法
tensor_a = torch.tensor([1, 2, 3])
tensor_b = torch.tensor([4, 5, 6])
tensor_add = tensor_a + tensor_b
print("张量加法结果:", tensor_add)

# 张量乘法
tensor_mul = tensor_a * tensor_b
print("张量乘法结果:", tensor_mul)

# 构造需要梯度的张量
x = torch.tensor(2.0, requires_grad=True)
y = x**2

# 反向传播计算梯度
y.backward()
print("张量x的梯度:", x.grad)
