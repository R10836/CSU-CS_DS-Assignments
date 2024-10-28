# -*- coding: utf-8 -*-
# File: t03.py
# Author: Ru Shawn
# Date: 2024/8/9

"""
当然可以！下面是一个稍微进阶的题目：

**题目：**

你需要实现一个多层感知机（MLP），用于对更复杂的数据集进行分类。具体要求如下：

1. **数据集：** 使用 `sklearn.datasets.make_moons` 函数生成一个包含两个类别的半月形数据集。数据集应包含500个样本，每个样本有两个特征。数据集的噪声设置为0.2。

2. **模型：** 创建一个包含两个隐藏层的神经网络：
   - 第一个隐藏层有64个神经元，使用ReLU激活函数。
   - 第二个隐藏层有32个神经元，使用ReLU激活函数。
   - 输出层有1个神经元，使用Sigmoid激活函数。

3. **损失函数：** 使用二元交叉熵损失函数（`BCELoss`）。

4. **优化器：** 使用Adam优化器。

5. **训练：** 训练模型30个epochs，每个epoch使用整个数据集进行训练。使用训练数据的80%作为训练集，20%作为验证集进行训练和评估。

6. **测试：** 在训练完成后，使用训练好的模型在一个新生成的测试集上进行预测，并计算准确率。测试集也使用`make_moons`函数生成。

7. **额外要求：**
   - 在训练过程中绘制训练损失和验证损失的曲线。
   - 在训练完成后，绘制数据点和决策边界。

完成后，将代码发给我，我会帮你检查。
"""

import torch
from sklearn.datasets import make_moons
from sklearn.model_selection import train_test_split
from torch import nn


class MyMLP(nn.Module):
    def __init__(self):
        super().__init__()
        self.cf1 = nn.Linear(2, 64)
        self.cf2 = nn.Linear(64, 32)
        self.cf3 = nn.Linear(32, 1)

    def forward(self, x):
        x = torch.relu(self.cf1(x))
        x = torch.relu(self.cf2(x))
        x = torch.sigmoid(self.cf3(x))
        return x


def evaluate(model, X_test, y_test):
    model.eval()
    with torch.no_grad():
        predict = model(X_test).round()  # outputs = model(X_train)
        accuracy = predict.eq(y_test).sum() / y_test.shape[0]
    return accuracy.item()


if __name__ == "__main__":
    # 生成数据集
    X, y = make_moons(n_samples=500, noise=0.2, random_state=42)
    # df = pd.DataFrame(X, columns=['Feature 1', 'Feature 2'])
    # df['Label'] = y
    # print(df.head())
    #
    # plt.figure(figsize=(8, 6))
    # plt.scatter(X[y == 0][:, 0], X[y == 0][:, 1], color='blue', label='Class 0', s=30, edgecolor='k')
    # plt.scatter(X[y == 1][:, 0], X[y == 1][:, 1], color='red', label='Class 1', s=30, edgecolor='k')
    # plt.title('Moons Dataset')
    # plt.xlabel('Feature 1')
    # plt.ylabel('Feature 2')
    # plt.legend()
    # plt.show()

    # 划分训练集和测试集
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
    # 转换为PyTorch张量
    X_train = torch.tensor(X_train, dtype=torch.float32)
    X_test = torch.tensor(X_test, dtype=torch.float32)
    y_train = torch.tensor(y_train, dtype=torch.float32).view(-1, 1)  # BCELoss 需要标签是 [batch_size, 1] 形式
    y_test = torch.tensor(y_test, dtype=torch.float32).view(-1, 1)

    model = MyMLP()
    criterion = nn.BCELoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=0.001)

    epochs = 1000
    for epoch in range(epochs):
        model.train()

        optimizer.zero_grad()
        outputs = model(X_train)
        loss = criterion(outputs, y_train)
        loss.backward()
        optimizer.step()

        accuracy = evaluate(model, X_test, y_test)
        print(f"轮数：{epoch}； 损失：{loss.item():.6f}； 准确率：{accuracy * 100:.4f}%。")
