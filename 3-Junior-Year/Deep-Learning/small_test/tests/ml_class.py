import torch
import torch.nn as nn
import torch.optim as optim


# 定义网络结构
class SimpleNN(nn.Module):
    def __init__(self):
        super(SimpleNN, self).__init__()
        self.fc1 = nn.Linear(3, 4)  # 输入层到隐藏层
        self.fc2 = nn.Linear(4, 2)  # 隐藏层到输出层

    def forward(self, x):
        x = torch.sigmoid(self.fc1(x))
        x = torch.sigmoid(self.fc2(x))
        return x


# 创建模型实例
model = SimpleNN()

# 初始化权重和偏置（可选）
with torch.no_grad():
    # fc1 的权重矩阵形状应该是 (4, 3)
    model.fc1.weight = torch.nn.Parameter(torch.tensor([[0.1, 0.5, 0.9],
                                                        [0.2, 0.6, 1.0],
                                                        [0.3, 0.7, 1.1],
                                                        [0.4, 0.8, 1.2]], dtype=torch.float))
    model.fc1.bias = torch.nn.Parameter(torch.tensor([0.1, 0.2, 0.3, 0.4], dtype=torch.float))

    # fc2 的权重矩阵形状应该是 (2, 4)
    model.fc2.weight = torch.nn.Parameter(torch.tensor([[0.1, 0.3, 0.5, 0.7],
                                                        [0.2, 0.4, 0.6, 0.8]], dtype=torch.float))
    model.fc2.bias = torch.nn.Parameter(torch.tensor([0.1, 0.2], dtype=torch.float))

# 定义损失函数和优化器
criterion = nn.MSELoss()
optimizer = optim.SGD(model.parameters(), lr=0.01)

# 示例数据
X = torch.tensor([[0.1, 0.2, 0.3],
                  [0.4, 0.5, 0.6],
                  [0.7, 0.8, 0.9]], dtype=torch.float)
y_true = torch.tensor([[0.0, 1.0],
                       [1.0, 0.0],
                       [0.0, 1.0]], dtype=torch.float)

# 训练模型
epochs = 10
for epoch in range(epochs):
    # 前向传播
    y_pred = model(X)
    # 计算损失
    loss = criterion(y_pred, y_true)
    print(f'Epoch {epoch}, Loss: {loss.item()}')
    # 反向传播
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()
