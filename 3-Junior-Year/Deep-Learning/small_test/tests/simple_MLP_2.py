import torch
import torch.nn as nn
import torch.optim as optim


# 定义神经网络
class MyModule(nn.Module):
    def __init__(self, input_size, hidden_size, output_size, n_layers):
        super(MyModule, self).__init__()
        layers = []

        # 输入层
        layers.append(nn.Linear(input_size, hidden_size))
        layers.append(nn.Sigmoid())

        # 隐藏层
        for _ in range(n_layers - 2):
            layers.append(nn.Linear(hidden_size, hidden_size))
            layers.append(nn.Sigmoid())

        # 输出层
        layers.append(nn.Linear(hidden_size, output_size))

        self.network = nn.Sequential(*layers)

    def forward(self, x):
        return self.network(x)


# 初始化神经网络
def initialize_weights(m):
    if isinstance(m, nn.Linear):
        torch.nn.init.uniform_(m.weight)
        torch.nn.init.zeros_(m.bias)


# 定义输入参数
input_size = 10  # a个节点
hidden_size = 20  # b个节点
output_size = 1  # c个节点
n_layers = 3  # n层

# 初始化网络
model = MyModule(input_size, hidden_size, output_size, n_layers)
model.apply(initialize_weights)

# 定义损失函数和优化器
criterion = nn.MSELoss()
optimizer = optim.SGD(model.parameters(), lr=0.01)

# 自定义输入和标签
inputs = torch.randn(5, input_size)  # 5个样本，a个特征
targets = torch.randn(5, output_size)  # 5个样本，c个输出

# 训练步骤
for epoch in range(1000):
    # 前向传播
    outputs = model(inputs)
    loss = criterion(outputs, targets)

    # 反向传播和优化
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

    if (epoch + 1) % 100 == 0:
        print(f'Epoch [{epoch + 1}/1000], Loss: {loss.item():.4f}')
