from pymysql import connect
from datetime import datetime

# 连接到数据库
conn_params = {
    'host': 'localhost',
    'port': 3306,
    'user': 'ru',
    'password': '8204193010',
    'database': 'my_imdb',
    'autocommit': True
}

conn = connect(**conn_params)
cursor = conn.cursor()

# 获取用户输入
码 = int(input("请输入码: "))
观影日期_str = input("请输入观影日期 (YYYY-MM-DD): ")
简中常见片名 = input("请输入简中常见片名: ")
原名 = input("请输入原名: ")
产地 = input("请输入产地: ")
首映年 = int(input("请输入首映年: "))
我的评分 = int(input("请输入我的评分: "))
类型 = input("请输入类型: ")
主要艺术家1 = input("请输入主要艺术家1: ")
主要艺术家2 = input("请输入主要艺术家2: ")
主要艺术家3 = input("请输入主要艺术家3: ")
主要艺术家4 = input("请输入主要艺术家4: ")

# 将观影日期字符串转换为日期对象
观影日期 = datetime.strptime(观影日期_str, '%Y-%m-%d').date()

# 插入新数据
insert_query = """
INSERT INTO movie_table (码, 观影日期, 简中常见片名, 原名, 产地, 首映年, 我的评分, 类型, 主要艺术家1, 主要艺术家2, 主要艺术家3, 主要艺术家4)
VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)
"""

new_data = (码, 观影日期, 简中常见片名, 原名, 产地, 首映年, 我的评分, 类型, 主要艺术家1, 主要艺术家2, 主要艺术家3, 主要艺术家4)
cursor.execute(insert_query, new_data)

# 关闭连接
cursor.close()
conn.close()
