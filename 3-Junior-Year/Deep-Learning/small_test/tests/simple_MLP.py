import torch
from torch import nn
from torch.utils.data import DataLoader

import torchvision
import torchvision.transforms as transforms


def load_data(batch_size, input_size):
    # 定义数据预处理
    trans = transforms.Compose([
        transforms.ToTensor(),
        transforms.Lambda(lambda x: x.view(-1))  # Flatten the input image
    ])

    # 加载数据集（不重复下载）
    mnist_train = torchvision.datasets.FashionMNIST(root="../data", train=True, transform=trans, download=False)
    mnist_test = torchvision.datasets.FashionMNIST(root="../data", train=False, transform=trans, download=False)

    # 创建数据加载器
    train_loader = DataLoader(mnist_train, batch_size=batch_size, shuffle=True)
    test_loader = DataLoader(mnist_test, batch_size=batch_size, shuffle=False)

    return train_loader, test_loader


class MLP(nn.Module):
    def __init__(self, input_size, hidden_size, output_size):
        super(MLP, self).__init__()
        self.fc1 = nn.Linear(input_size, hidden_size)
        self.fc2 = nn.Linear(hidden_size, output_size)

    def forward(self, x):
        x = torch.relu(self.fc1(x))
        x = self.fc2(x)
        return x


def train_model(model, train_loader, test_loader, num_epochs, lr):
    criterion = nn.CrossEntropyLoss()
    optimizer = torch.optim.SGD(model.parameters(), lr=lr)

    for epoch in range(num_epochs):
        model.train()
        running_loss = 0.0
        for X, y in train_loader:
            optimizer.zero_grad()
            outputs = model(X)
            loss = criterion(outputs, y)
            loss.backward()
            optimizer.step()
            running_loss += loss.item() * X.size(0)

        epoch_loss = running_loss / len(train_loader.dataset)
        print(f'Epoch {epoch + 1}, Loss: {epoch_loss:.4f}')

        model.eval()
        correct = 0
        total = 0
        with torch.no_grad():
            for X, y in test_loader:
                outputs = model(X)
                _, predicted = torch.max(outputs, 1)
                total += y.size(0)
                correct += (predicted == y).sum().item()

        accuracy = correct / total
        print(f'Epoch {epoch + 1}, Accuracy: {accuracy:.4f}')

    print("Training Complete!")


if __name__ == "__main__":
    # 超参数
    input_size = 784
    hidden_size = 256
    output_size = 10
    batch_size = 64
    num_epochs = 10
    lr = 0.1

    # 加载数据
    train_loader, test_loader = load_data(batch_size, input_size)

    # 初始化模型
    model = MLP(input_size, hidden_size, output_size)

    # 训练模型
    train_model(model, train_loader, test_loader, num_epochs, lr)
