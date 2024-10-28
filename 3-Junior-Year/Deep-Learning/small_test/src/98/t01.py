# -*- coding: utf-8 -*-
# File: t01.py
# Author: Ru Shawn
# Date: 2024/8/9

"""
好的！这是一个简单的练习题目：

### 题目
你需要构建一个简单的全连接神经网络（即多层感知器，MLP），用于对MNIST手写数字数据集进行分类。具体要求如下：

1. **数据集**：
   - 使用MNIST数据集（可通过`torchvision.datasets`加载）。
   - 将图像数据标准化到[0, 1]范围。

2. **模型结构**：
   - 输入层：28x28个节点（MNIST图片的像素点展开为一维向量）。
   - 隐藏层1：128个节点，激活函数使用ReLU。
   - 隐藏层2：64个节点，激活函数使用ReLU。
   - 输出层：10个节点（对应0-9的数字分类），激活函数使用softmax。

3. **训练**：
   - 使用交叉熵损失函数（`CrossEntropyLoss`）。
   - 优化器使用SGD，学习率为0.01。
   - 训练模型5个epoch。

4. **评估**：
   - 在测试集上评估模型的准确率。

### 提示
- 你需要考虑如何将数据加载到模型中，如何定义和训练模型，以及如何计算测试集上的准确率。

写好代码后，告诉我，我会帮你检查并给出反馈。
"""

import torch
from torch import nn
from torch.utils.data import DataLoader
from torchvision import transforms, datasets


class MyMLP(nn.Module):
    def __init__(self):
        super(MyMLP, self).__init__()
        # 定义模型层次结构
        self.fc1 = nn.Linear(28 * 28, 128)  # 输入层到隐藏层1
        self.fc2 = nn.Linear(128, 64)  # 隐藏层1到隐藏层2
        self.fc3 = nn.Linear(64, 10)  # 隐藏层2到输出层

    def forward(self, x):
        # 前向传播过程
        x = x.view(-1, 28 * 28)  # 将28x28的图像展开成一维向量
        x = nn.functional.relu(self.fc1(x))  # 隐藏层1 + ReLU
        x = nn.functional.relu(self.fc2(x))  # 隐藏层2 + ReLU
        x = nn.functional.log_softmax(self.fc3(x), dim=1)  # 输出层 + Softmax
        return x


if __name__ == "__main__":

    transform = transforms.Compose([transforms.ToTensor(), transforms.Normalize((0.5,), (0.5,))])
    train_dataset = datasets.MNIST(root='../data', train=True, transform=transform, download=True)
    test_dataset = datasets.MNIST(root='../data', train=False, transform=transform, download=True)

    train_loader = DataLoader(dataset=train_dataset, batch_size=64, shuffle=True)
    test_loader = DataLoader(dataset=test_dataset, batch_size=1000, shuffle=False)

    model = MyMLP()
    criterion = nn.CrossEntropyLoss()
    optimizer = torch.optim.SGD(model.parameters(), lr=0.01)

    for epoch in range(5):
        model.train()
        for batch_idx, (data, target) in enumerate(train_loader):
            optimizer.zero_grad()
            output = model(data)
            loss = criterion(output, target)
            loss.backward()
            optimizer.step()
        print(f'Epoch {epoch + 1}, Loss: {loss.item()}')

    model.eval()
    correct = 0
    total = 0
    with torch.no_grad():
        for data, target in test_loader:
            output = model(data)
            _, predicted = torch.max(output.data, 1)
            total += target.size(0)
            correct += (predicted == target).sum().item()
    print(f'Test Accuracy: {100 * correct / total}%')

    # torch.save(model.state_dict(), 'model.pth')

"""
Q1：为什么self.fc1还能加个括号传参数？
self.fc1 之所以能加括号并传入参数，是因为 self.fc1 是一个 层 (layer) 对象，而在 PyTorch 中，层对象本质上是一个可调用的对象（即一个函数或方法），可以直接使用括号传入参数来执行前向传播计算。
self.fc1 是 nn.Linear 的实例，具体来说，self.fc1(x) 背后执行了以下操作：
计算线性变换 y = xW^T + b，其中 W 是权重矩阵，b 是偏置项，x 是输入数据。
返回结果 y，这个结果会传递到下一层或者激活函数中。

Q2：为什么是F.relu而不是torch.relu
在PyTorch中，F.relu 和 torch.relu 都可以用来应用ReLU激活函数，torch.relu 更适合在一些简单的操作中直接对张量应用，但在神经网络模型定义中，用 F.relu 更为常见。
所以，使用 F.relu 是为了保持代码风格的统一和清晰度。在绝大多数情况下，二者的功能是相同的，选择哪个更多的是个人风格问题。

Q3：F.relu(self.fc1(x))
这一步首先计算 self.fc1(x)，得到线性变换后的结果。然后将这个结果通过 F.relu() 激活函数。

Q4：log_softmax()中的dim=1
dim 参数决定了我们在计算函数（比如 softmax）时沿哪个维度进行操作。
假设我们有一个形状为 (N, D) 的张量，其中：N 是批量中的样本数量（比如 64 个图像）。D 是每个样本的特征数量（比如 10 个类别的得分）。
当 dim=0 时，操作是在样本的维度上进行。当 dim=1 时，操作是在特征的维度上进行。
使用 F.log_softmax(self.fc3(x), dim=1) 时，dim=1 意味着：对每个样本的 10 个类别得分应用 softmax，计算每个类别的概率。

Q5：
"""