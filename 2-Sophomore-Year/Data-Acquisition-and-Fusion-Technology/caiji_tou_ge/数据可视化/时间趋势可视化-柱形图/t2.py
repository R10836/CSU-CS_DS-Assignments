# -*- coding: utf-8 -*-
import pandas as pd
from matplotlib import pyplot as plt

hot_dog = pd.read_csv(r"matplotlib_bar/csv/hot-dog-contest-winners.csv")


def plot():
    # ********* Begin *********#

    fig, ax = plt.subplots()  # subplots返回画布和子图
    ax.bar(hot_dog["Year"], hot_dog["Dogs eaten"], width=[0.6], color=unitedStatesColor())  # 绘制柱形图，第一个参数为x轴变量，第二个参数为y轴变量
    ax.set_xlabel("Year")  # 设置x轴标签
    ax.set_ylabel("Dogs Eaten")  # 设置y轴标签
    ax.set_title("Hotdog game scores 1980-2010")  # 设置标题
    ax.set_xlim(1979, 2011)  # 设置x轴数据限值
    plt.rcParams['figure.figsize'] = (8.0, 4.0)  # 设置figure_size尺寸
    plt.show()  # 显示图像
    # ********* End *********#
    plt.savefig('matplotlib_bar/studentfile/studentanswer/level_2/US.png')
    plt.close()


def unitedStatesColor():
    # ********* Begin *********#

    """打破记录的年份显示为粉红色，其余年份为灰绿色"""
    list = []
    for i in hot_dog["Country"]:
        if i == 'United States ':
            list.append("#DB7093")  # 打破记录的年份显示为粉红色
        else:
            list.append("#5F9F9F")  # 其余年份显示为灰绿色
    return list

    # ********* End *********#



#     Year                        Winner  Dogs eaten        Country  New record
# 0   1980  Paul Siederman & Joe Baldini        9.10  United States           0
# 1   1981               Thomas DeBerry        11.00  United States           0
# 2   1982                Steven Abrams        11.00  United States           0
# 3   1983                  Luis Llamas        19.50         Mexico           0
# 4   1984                Birgit Felden         9.50        Germany           0
# 5   1985              Oscar Rodriguez        11.75  United States           0
# 6   1986                  Mark Heller        15.50  United States           0
# 7   1987                  Don Wolfman        12.00  United States           0
# 8   1988                    Jay Green        14.00  United States           0
# 9   1989                    Jay Green        13.00  United States           0
# 10  1990                  Mike DeVito        16.00  United States           0
# 11  1991              Frank Dellarosa        21.50  United States           1
# 12  1992              Frank Dellarosa        19.00  United States           0
# 13  1993                  Mike DeVito        17.00  United States           0
# 14  1994                  Mike DeVito        20.00  United States           0
# 15  1995               Edward Krachie        19.50  United States           0
# 16  1996               Edward Krachie        22.25  United States           1
# 17  1997            Hirofumi Nakajima        24.50          Japan           1
# 18  1998            Hirofumi Nakajima        19.00          Japan           0
# 19  1999                 Steve Keiner        20.25  United States           0
# 20  2000   Kazutoyo "The Rabbit" Arai        25.13          Japan           1
# 21  2001             Takeru Kobayashi        50.00          Japan           1
# 22  2002             Takeru Kobayashi        50.50          Japan           1
# 23  2003             Takeru Kobayashi        44.50          Japan           0
# 24  2004             Takeru Kobayashi        53.50          Japan           1
# 25  2005             Takeru Kobayashi        49.00          Japan           0
# 26  2006   Takeru "Tsunami" Kobayashi        53.75          Japan           1
# 27  2007                Joey Chestnut        66.00  United States           1
# 28  2008                Joey Chestnut        59.00  United States           0
# 29  2009                Joey Chestnut        68.00  United States           1
# 30  2010                Joey Chestnut        54.00  United States           0