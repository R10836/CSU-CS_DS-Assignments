from matplotlib.dates import MonthLocator
from sqlalchemy import create_engine
import pandas as pd
import pymysql
import matplotlib.pyplot as plt


# PART 1: 读入数据库里面的数据 (sqlalchemy + pandas)
def get_data_from_db_with_pandas():
    # sqlalchemy连接MySQL & 写出需要的SQL语句:
    engine = create_engine('mysql+pymysql://ru:8204193010@127.0.0.1:3306/my_imdb')
    sql_query = 'SELECT * FROM movie_table'

    # pandas实现数据库数据读取:
    # pd.read_sql_query()是Pandas库中的一个函数，用于执行SQL查询并将查询结果读取到Pandas DataFrame中。函数的内部会自动创建和管理一个游标对象。
    df = pd.read_sql_query(sql=sql_query, con=engine, coerce_float=False, parse_dates=['观影日期'])  # 核心代码

    # 关闭数据库连接:
    engine.dispose()

    # 至此，数据库的数据导入到了DataFrame对象的实例--变量df中，下一步开始数据分析、数据可视化:
    return df


# PART 1 读入数据库里面的数据的另一种写法。(pymysql)
def get_data_from_db_with_pymysql():
    # pymysql数据库连接 && 创建游标对象 && 写出需要的SQL语句:
    conn = pymysql.connect(
        host='localhost',
        port=3306,
        user='ru',
        password='8204193010',
        autocommit=True,
        database='my_imdb'
    )
    cursor = conn.cursor()
    sql_query = 'SELECT * FROM movie_table'

    # 执行SQL查询:
    cursor.execute(sql_query)

    # 获取查询结果:
    result = cursor.fetchall()

    # 关闭游标和连接:
    cursor.close()
    conn.close()

    # result是一个包含元组的列表，其中每个元组对应查询结果中的一行数据:
    return result


# PART 1 还可以直接读excel：
def get_data_from_excel():
    # P87
    pass


# PART 2: DataFrame使用，数据预处理、清洗
def play_dataframe(df):
    # df.info()
    pass


# PART 3: matplotlib数据可视化
def data_visualization(df):
    # 设置中文显示，指定字体
    plt.rcParams['font.sans-serif'] = ['Microsoft YaHei']

    # 1 创建画布和子图
    fig, ax = plt.subplots(figsize=(256, 8), dpi=128)  # fig是画布对象，而ax是子图对象。函数用于创建一个包含子图的画布。如果没有参数，默认创建一个包含一个子图的画布。
    fig.patch.set_facecolor('orange')
    ax.set_facecolor('lightyellow')

    # 2 添加画布内容
    # 添加网格线
    plt.grid(True, linestyle='--', alpha=1, axis='y', color='orange')
    # 在子图ax上画柱状图
    ax.bar(x=df['观影日期'], height=df['我的评分'], width=1, color='gold', edgecolor='purple')
    # 在每个柱子顶部显示简中常见片名
    for bar, movie_name in zip(ax.patches, df['简中常见片名']):
        ax.text(bar.get_x() + bar.get_width() / 2, bar.get_height(), movie_name,
                ha='center', va='bottom', rotation=30, color='red', fontsize=8)
    # 设置横坐标每个月显示一次
    ax.xaxis.set_major_locator(MonthLocator())

    # 3 保存与显示图形
    plt.tight_layout()
    plt.savefig('不同电影我的评分柱状图.png')
    plt.show()


if __name__ == '__main__':
    # print(get_data_from_db_with_pandas())
    # print(get_data_from_db_with_pymysql())
    the_df = get_data_from_db_with_pandas()
    # play_dataframe(the_df)
    data_visualization(the_df)
    print('It Works!')
