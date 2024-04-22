import csv
import pandas
import pymysql
import mpl_finance
import matplotlib.pyplot as plt
import matplotlib.dates as mdates


def insert_to_byd(row):
    # 建立数据库连接
    connection = pymysql.connect(
        host='localhost',  # 数据库主机名
        user='ru',  # 数据库用户名
        password='8204193010',  # 数据库密码
        database='the_byd',  # 数据库名
        charset='utf8'  # 字符集
    )

    try:
        with connection.cursor() as cursor:
            # 定义要执行的 SQL 插入语句
            sql = 'insert into quote_of_byd ' \
                  '(HDate,Open,Close,changeamount,changerate,Low,High,Volume,Volumeamount,turnoverrate)' \
                  'values  (%(日期)s,%(开盘价)s,%(收盘价)s,%(涨跌额)s,%(涨跌幅)s,%(最低价)s,%(最高价)s,%(成交量)s,%(成交额)s,%(换手率)s)'

            # 测试：
            affectedcount = cursor.execute(sql, row)
            print('影响的数据行数:{0}'.format(affectedcount))

            connection.commit()  # 提交事务

    except pymysql.DatabaseError as error:
        connection.rollback()  # 发生异常时进行回滚
        print(error)
    finally:
        connection.close()  # 关闭数据库连接

# 测试：显示全部表格
def select_all_byd():
    connection = pymysql.connect(host='localhost',
                                 user='ru',
                                 password='8204193010',
                                 database='the_byd',
                                 charset='utf8')

    data = []
    try:
        with connection.cursor() as cursor:
            sql = """
                  select 
                  HDate, Open, Close, changeamount, changerate, Low, High, Volume, Volumeamount, turnoverrate
                  from quote_of_byd 
                  """
            cursor.execute(sql)

            result_set = cursor.fetchall()
            print("查询成功")
            for row in result_set:
                fields = {}
                fields['日期'] = row[0]
                fields['开盘价'] = float(row[1])
                fields['收盘价'] = float(row[2])
                fields['涨跌额'] = float(row[3])
                fields['涨跌幅'] = float(row[4])
                fields['最低价'] = float(row[5])
                fields['最高价'] = float(row[6])
                fields['成交量'] = float(row[7])
                fields['成交额'] = float(row[8])
                fields['换手率'] = float(row[9])
                data.append(fields)
        # print(data)

    except pymysql.DatabaseError as error:
        print('数据查询失败' + error)
    finally:
        connection.close()
    return data


def select_for_byd(startmonth, startday, endmonth, endday):
    connection = pymysql.connect(host='localhost',
                                 user='ru',
                                 password='8204193010',
                                 database='the_byd',
                                 charset='utf8')

    data = []
    # 创建开始时间和结束时间字符串，格式为 'YYYY-MM-DD'
    starttime = '2023-'+startmonth+'-'+startday
    endtime = '2023-'+endmonth+'-'+endday
    # 测试：
    # print('starttime'+starttime)
    # print('endtime'+endtime)

    try:
        with connection.cursor() as cursor:
            # 定义SQL查询，以选择在开始时间和结束时间之间的数据
            sql = 'SELECT HDate, Open, Close, changeamount, changerate, Low, High, Volume, Volumeamount, turnoverrate ' \
                  'FROM quote_of_byd WHERE hdate BETWEEN %s AND %s'
            
            # 使用提供的开始时间和结束时间值执行SQL查询
            cursor.execute(sql, [starttime, endtime])

            # 获取查询返回的所有行
            result_set = cursor.fetchall()

            # 遍历结果集中的每一行
            for row in result_set:
                fields = {}
                # 从每行的每一列提取值
                fields['日期'] = str(row[0])
                fields['开盘价'] = float(row[1])
                fields['收盘价'] = float(row[2])
                fields['涨跌额'] = float(row[3])
                fields['涨跌幅'] = float(row[4])
                fields['最低价'] = float(row[5])
                fields['最高价'] = float(row[6])
                fields['成交量'] = float(row[7])
                fields['成交额'] = float(row[8])
                fields['换手率'] = float(row[9])
                data.append(fields)
    except pymysql.DatabaseError as error:
        print('数据查询失败' + error)
    finally:
        # 关闭数据库连接
        connection.close()
    
    # 返回检索到的数据列表
    return data


def get_data(startmonth, startday, endmonth, endday):
    # 调用select_for_byd函数获取数据
    data = select_for_byd(startmonth, startday, endmonth, endday)
    print('data=' + str(data))

    # 列名
    colsname = ['日期', '开盘价', '最高价', '最低价', '收盘价', '涨跌额', '成交量', '成交额']
    # 临时数据文件名
    datafile = '  from ' + startmonth + '-' + startday + 'to ' + endmonth + '-' + endday + ' ' + 'temp.csv'
    
    # 写入数据到临时数据文件
    with open(datafile, 'w', newline='', encoding='utf-8') as wf:
        writer = csv.writer(wf)
        writer.writerow(colsname)
        for quotes in data:
            row = [quotes['日期'], quotes['开盘价'], quotes['最高价'],
                   quotes['最低价'], quotes['收盘价'], quotes['涨跌额'], quotes['成交量'], quotes['成交额']]
            writer.writerow(row)
    
    # 返回临时数据文件名
    return datafile


def pot_candlestick_ohlc(datafile):
    # 从CSV文件中读取数据
    quotes = pandas.read_csv(datafile,
                             index_col=0,
                             parse_dates=True,
                             infer_datetime_format=True)

    # 创建一个绘图窗口和子图对象，设置子图大小
    fig, ax = plt.subplots(figsize=(30, 10))

    # 调整子图参数SubplotParams，使底部空白区域留给x轴标签
    fig.subplots_adjust(bottom=0.2)

    # 绘制蜡烛图
    mpl_finance.candlestick_ohlc(ax, zip(mdates.date2num(quotes.index.to_pydatetime()),
                                         quotes['开盘价'], quotes['最高价'],
                                         quotes['最低价'], quotes['收盘价']),
                                 width=1, colorup='r', colordown='g', alpha=0.6)

    # 设置x轴为日期格式
    ax.xaxis_date()

    # 自动调整子图视图范围
    ax.autoscale_view()

    # 设置x轴标签旋转角度为45度，水平对齐方式为右对齐
    plt.setp(plt.gca().get_xticklabels(), rotation=45, horizontalalignment='right')

    # 显示图形
    plt.show()