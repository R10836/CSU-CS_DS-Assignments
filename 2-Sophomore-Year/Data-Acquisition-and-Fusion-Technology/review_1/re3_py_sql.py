from pymysql import Connection


# 1、获取到Mysql数据库的链接对象
conn = Connection(
    host='localhost',
    port=3306,
    user='ru',
    password='8204193010',
    autocommit=True
)

# 打印MySQL数据库软件信息
print(conn.get_server_info())

# 2、获取游标对象
cursor = conn.cursor()

conn.select_db('the_byd')   # 3.1、先选择数据库：

# 3.2、执行sql语句：
# 执行非查询性质的SQL语句
# 使用游标对象，执行sql语句
# 删除已存在的表格（如果存在）
cursor.execute('DROP TABLE IF EXISTS test_pymysql')
cursor.execute('create table test_pymysql(id int, info varchar(8))')

# 执行查询性质的sql语句
# 使用游标对象，执行sql语句
cursor.execute('select HDate, Open, Close, Low, High, Volume '
               'from quote_of_byd '
               'where Open <= 271 and Close between 260 and 270')
# 获取查询结构
results: tuple = cursor.fetchall()
for r in results:
    print(r)

# 4、关闭到数据库的链接
conn.close()
