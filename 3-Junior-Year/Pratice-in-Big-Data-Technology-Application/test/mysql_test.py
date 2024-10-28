import mysql.connector
from mysql.connector import Error

try:
    # 尝试连接数据库
    connection = mysql.connector.connect(
        host='localhost',
        database='myemail',
        user='',
        password=''
    )

    if connection.is_connected():
        db_info = connection.get_server_info()
        print("成功连接到MySQL服务器版本 ", db_info)
        cursor = connection.cursor()
        cursor.execute("select database();")
        record = cursor.fetchone()
        print("你已连接到数据库: ", record)

except Error as e:
    print("连接错误：", e)

finally:
    if connection.is_connected():
        cursor.close()
        connection.close()
        print("MySQL连接已关闭")
