# -*- coding: utf-8 -*-
# File: t02.py
# Author: Ru Shawn
# Date: 2024/8/9

"""
好的，我可以给你设计一个练习题。以下是题目：

### 题目：简单的二分类神经网络

**任务**：使用PyTorch构建一个简单的二分类神经网络。你的网络将接受二维数据输入，并预测数据属于两类中的哪一类。

### 1. 数据集
生成一个由两个类别组成的二维数据集，每个类别的数据点数量为100。类别1的数据点分布在以(2, 2)为中心的高斯分布上，类别2的数据点分布在以(-2, -2)为中心的高斯分布上。数据集的具体要求如下：
- 类别1：100个点，均值为(2, 2)，标准差为1的高斯分布。
- 类别2：100个点，均值为(-2, -2)，标准差为1的高斯分布。

### 2. 模型
构建一个简单的前馈神经网络（即多层感知器，MLP），它包含以下层次：
- 输入层：2个神经元（对应于数据集的2个特征）。
- 隐藏层：一个隐藏层，包含5个神经元，激活函数使用ReLU。
- 输出层：1个神经元，使用Sigmoid激活函数输出二分类结果。

### 3. 损失函数和优化器
- 损失函数：使用二元交叉熵损失（Binary Cross-Entropy Loss）。
- 优化器：使用随机梯度下降（SGD）优化器，学习率为0.01。

### 4. 训练
- 将数据集分为训练集和测试集（比例为8:2）。
- 训练模型，并在测试集上评估模型的准确性。

你可以尝试先完成这个练习，然后把代码贴给我，我会帮你检查和指导。
"""

import numpy as np
import torch
from sklearn.model_selection import train_test_split
from torch import nn


# 生成类别1的数据
mean1 = [2, 2]
cov1 = [[1, 0], [0, 1]]
class1_data = torch.tensor(np.random.multivariate_normal(mean1, cov1, 100), dtype=torch.float32)
class1_labels = torch.zeros(100, 1)  # 标签为0

# 生成类别2的数据
mean2 = [-2, -2]
cov2 = [[1, 0], [0, 1]]
class2_data = torch.tensor(np.random.multivariate_normal(mean2, cov2, 100), dtype=torch.float32)
class2_labels = torch.ones(100, 1)  # 标签为1

# 合并数据集
data = torch.cat([class1_data, class2_data], dim=0)
labels = torch.cat([class1_labels, class2_labels], dim=0)

# 拆分训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(data, labels, test_size=0.2, random_state=42)


class MyMLP(nn.Module):
    def __init__(self):
        super().__init__()
        self.fc1 = nn.Linear(2, 5)
        self.fc2 = nn.Linear(5, 1)

    def forward(self, x):
        x = torch.relu(self.fc1(x))
        x = torch.sigmoid(self.fc2(x))
        return x


def evaluate(model, X_test, y_test):
    model.eval()  # 将模型设置为评估模式：禁用 dropout 等在训练中有用但评估时不需要的层。
    # with 语句会确保在执行代码块时，某些资源能够自动地被正确地获取和释放，比如打开文件、数据库连接、锁定资源、禁用梯度计算等。
    with torch.no_grad():  # 禁用梯度计算。因为在评估阶段我们不需要进行反向传播，所以可以关闭梯度计算。从而节省内存和加速计算。
        predictions = model(X_test)  # outputs = model(X_train)
        predictions = predictions.round()  # 模型的输出是一个概率值（通常在0到1之间）。通过 round()，我们将这些概率值四舍五入为0或1。0表示模型预测样本属于第一个类别（负类），1表示样本属于第二个类别（正类）。
        accuracy = (predictions.eq(y_test).sum() / y_test.shape[0]).item()  # item() 方法从包含单个元素的张量中提取出数值，并将其作为 Python 的 float 或 int 返回。
    return accuracy


if __name__ == "__main__":

    model = MyMLP()
    criterion = nn.BCELoss()
    optimizer = torch.optim.SGD(model.parameters(), lr=0.01)

    epochs = 100
    for epoch in range(epochs):
        model.train()  # 将模型设置为训练模式：告诉模型在训练模式下运行，比如启用 dropout 层（如果有）。
        # 清零梯度：PyTorch 中的梯度是累积的。如果不清零，梯度会累加导致错误的更新。因此每次迭代开始时都需要清零。
        optimizer.zero_grad()
        # 前向传播：将训练数据传入模型，获取模型的预测结果。
        outputs = model(X_train)
        # 计算损失：将训练数据传入模型，获取模型的预测结果。
        loss = criterion(outputs, y_train)
        # 反向传播：计算梯度，自动为每个可学习参数计算它的梯度。
        loss.backward()
        # 更新参数：使用计算得到的梯度，更新模型的参数，使其逐渐向最小损失方向优化。
        optimizer.step()

        # 打印当前的损失和在测试集上的准确性
        if (epoch + 1) % 2 == 0:
            accuracy = evaluate(model, X_test, y_test)
            print(f'Epoch [{epoch + 1}/{epochs}], Loss: {loss.item():.4f}, Accuracy: {accuracy * 100:.2f}%')
            # loss.item() 是 PyTorch 中的一个方法，用来获取 loss 张量（tensor）中的标量值（即数值）并将其作为一个 Python 的浮点数返回。它主要用于打印或记录损失值，因为直接输出张量可能包含其他信息或不方便展示。
            # 具体来说，loss 是一个包含单个元素的张量，它的形状通常是 torch.Size([])，即一个标量张量。通过调用 item()，你可以从这个张量中提取出实际的数值

"""

"""