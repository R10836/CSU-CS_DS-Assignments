# -*- coding: utf-8 -*-
import pandas as pd
from matplotlib import pyplot as plt

hot_dog = pd.read_csv(r"matplotlib_bar/csv/hot-dog-contest-winners.csv")


def plot():
    # ********* Begin *********#
    fig, ax = plt.subplots()  # subplots返回画布和子图
    ax.bar(hot_dog["Year"], hot_dog["Dogs eaten"])  # 绘制柱形图，第一个参数为x轴变量，第二个参数为y轴变量
    plt.show()  # 显示图像
    # ********* End *********#
    plt.savefig('matplotlib_bar/studentfile/studentanswer/level_1/US.png')
    plt.close()
