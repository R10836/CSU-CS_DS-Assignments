#!/usr/bin/python
# -*- coding: UTF-8 -*-

import pymysql


# 连接mysql，创建连接并返回连接对象
def connect():
    # 请在这里补充代码，完成本关任务，注意缩进格式为4个空格
    # ********* Begin ********* #
    try:
        conn = pymysql.connect(
            host='127.0.0.1',
            port=3306,
            user='root',
            passwd='123123',
            autocommit=True
        )
        return conn
    except pymysql.Error as e:
        print(f"Error connecting to MySQL: {e}")
        return None
    # *********  End  ********* #


def test():
    # 创建连接，并且返回连接对象
    conn = connect()
    # 创建游标对象
    cursor = conn.cursor()
    # 请在这里补充代码，完成本关任务，注意缩进格式为4个空格
    # ********* Begin ********* #

    cursor.execute("CREATE DATABASE my_db CHARACTER SET utf8 COLLATE utf8_general_ci;")
    # *********  End  ********* #
    # 关闭游标
    cursor.close()
    # 关闭连接
    conn.close()
