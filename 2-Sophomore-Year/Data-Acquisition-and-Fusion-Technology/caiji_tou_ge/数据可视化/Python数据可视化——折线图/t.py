# -*- coding: utf-8 -*-
import pandas as pd
import numpy as np
from matplotlib import pyplot as plt

population = pd.read_csv(r"LineChart/level1/csv/world-population.csv")


def plot():
    # ********* Begin *********#
    fig, ax = plt.subplots()  # 使用fig, ax创建图形和子图

    # 设置标题和标签
    ax.set_xlabel('Year', fontsize=12)
    ax.set_ylabel('Population', fontsize=12)

    # 修改x轴坐标刻度，按5年的间隔划分
    my_x_ticks = np.arange(1960, 2011, 5)
    plt.xticks(my_x_ticks)

    # 添加网格
    plt.grid(b=True, color='r', linestyle='--', linewidth=1, alpha=0.3, axis='x', which="major")

    # 绘制折线图
    ax.plot(population["Year"], population["Population"], c='#00CC88', marker='*', linewidth=1, markersize=4,
            label='Y1')  # 绘制y

    # ********* End *********#
    plt.savefig('LineChart/level1/studentanswer/world-population.png')  # 保存为png格式
    plt.close()  # 关闭画布窗口
