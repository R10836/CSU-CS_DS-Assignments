import pandas as pd
from pymysql import connect

# 读取CSV文件并解析日期列
df = pd.read_csv("D:/Rxy_codings/JetPython/My_Movie_Show/movie_001.csv", encoding='gbk', parse_dates=['观影日期'])

# 1
conn = connect(
    host='localhost',
    port=3306,
    user='ru',
    password='8204193010',
    database='my_imdb',
    autocommit=True
)

# 2
cursor = conn.cursor()

# 3
table_name = 'movie_table'
# 创建新表
create_table_query = f"""
CREATE TABLE IF NOT EXISTS {table_name} (
    码 INT PRIMARY KEY,
    观影日期 DATE,
    简中常见片名 VARCHAR(50),
    原名 VARCHAR(50),
    产地 VARCHAR(20),
    首映年 INT,
    我的评分 INT,
    类型 VARCHAR(10),
    主要艺术家1 VARCHAR(50),
    主要艺术家2 VARCHAR(50),
    主要艺术家3 VARCHAR(50),
    主要艺术家4 VARCHAR(50)
)
"""
cursor.execute(create_table_query)

# 插入数据
for index, row in df.iterrows():
    row.replace({pd.NaT: None}, inplace=True)
    insert_query = f"""
    INSERT INTO {table_name} (码, 观影日期, 简中常见片名, 原名, 产地, 首映年, 我的评分, 类型, 主要艺术家1, 主要艺术家2, 主要艺术家3, 主要艺术家4)
    VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)
    """
    cursor.execute(insert_query, (
        row['码'], row['观影日期'].date(), row['简中常见片名'], row['原名'], row['产地'],
        row['首映年'], row['我的评分'], row['类型'], row['主要艺术家1'],
        row['主要艺术家2'], row['主要艺术家3'], row['主要艺术家4']
    ))

# 4
cursor.close()
conn.close()

print('It Works!')
