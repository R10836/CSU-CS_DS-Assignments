import torch


def test_pytorch():
    print("正在测试 PyTorch 环境...")

    # 检查 PyTorch 是否安装
    try:
        print(f"PyTorch 版本: {torch.__version__}")
    except ImportError:
        print("PyTorch 没有安装。")
        return

    # 检查是否有 GPU 可用
    if torch.cuda.is_available():
        print(f"CUDA 可用。GPU 数量: {torch.cuda.device_count()}")
        print(f"当前 GPU: {torch.cuda.get_device_name(torch.cuda.current_device())}")
    else:
        print("CUDA 不可用。正在使用 CPU。")

    # 测试张量操作
    try:
        x = torch.rand(5, 3)
        y = torch.rand(5, 3)
        z = x + y
        print(f"张量加法成功。结果:\n{z}")
    except Exception as e:
        print(f"张量操作失败: {e}")


if __name__ == "__main__":
    test_pytorch()
