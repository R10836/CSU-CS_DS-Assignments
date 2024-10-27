import wx
import re
import json
import urllib
import pandas
import wx.grid
import requests
import threading
import mpl_finance
import pandas as pd
import mplfinance as mpf
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
from ru_exp1_more import insert_to_byd, select_all_byd, select_for_byd, get_data, pot_candlestick_ohlc


column = ['日期', '开盘价', '最高价', '最低价', '收盘价', '涨跌额', '成交量', '成交额']


# 设置要爬取的URL
url = 'https://q.stock.sohu.com/hisHq?code=cn_002594&stat=1&order=D&period=d&callback=historySearchHandler&rt=jsonp&0.7380906540612318'
# 创建一个请求对象
req = urllib.request.Request(url)


# 发送请求并获取响应
with urllib.request.urlopen(req) as response:
    # 读取响应数据
    data = response.read()
    # 将数据解码为字符串（假设使用UTF-8编码）
    htmlstr = data.decode('utf-8', errors='ignore')

    # 使用正则表达式匹配数据部分并提取JSON数据
    match = re.search(r'historySearchHandler\((.*)\)', htmlstr)
    if match:
        json_data = match.group(1)
        stock_data = json.loads(json_data)

        # 测试：看看有没有爬到数据
        # print(stock_data)

data = []  # 创建一个名为 data 的空列表来存储数据

# 测试:看看[]
# for i in data:
#     print(type(data))

# 遍历 stock_data 中的数据
for stock in stock_data:
    for item in stock['hq']:
        # 使用正则表达式提取每个数据项的字段
        rows = re.search(r'\[\'(\w+-\w+-\w+)\'\, \'(\w*.\w*)\'\, \'(\w*.\w*)\'\, \'(.\w*.\w*)\'\, \'(.\w*.\w*%)\'\, \'(\w+.\w+)\'\, \'(\w+.\w+)\'\, \'(\w+)\'\, \'(\w+.\w+)\'\, \'(\w*.\w*%)\'\]', str(item))
        fields = {}
        fields['日期'] = rows.group(1)
        fields['开盘价'] = float(rows.group(2))
        fields['收盘价'] = float(rows.group(3))
        fields['涨跌额'] = float(rows.group(4))
        s1 = rows.group(5).replace('%', '')
        fields['涨跌幅'] = float(s1)
        fields['最低价'] = float(rows.group(6))
        fields['最高价'] = float(rows.group(7))
        fields['成交量'] = int(rows.group(8))
        fields['成交额'] = float(rows.group(9))
        s2 = rows.group(10).replace('%', '')
        fields['换手率'] = float(s2)
        data.append(fields)  # 将字典添加到 data 列表中

    # 测试：看看有没有将数据转化为想要的格式
    # for item in data:
    #     print(item)

        # 测试:插入并检查
        insert_to_byd(fields)
# selectall_byd()


class MyGridTable(wx.grid.GridTableBase):
    def __init__(self, data):
        super().__init__()
        self.colLabels = column  # 列标签
        self.data = data  # 表格数据

    def GetNumberRows(self):
        return len(self.data)  # 获取行数

    def GetNumberCols(self):
        return len(column)  # 获取列数

    def GetValue(self, row, col):
        return self.data[row][col]  # 获取指定行列的单元格值

    def GetColLabelValue(self, col):
        return self.colLabels[col]  # 获取指定列的列标签值


class MyFrame2(wx.Frame):
    def __init__(self, savapath, savepath1, savepath2, savepath3, savepath4):
        super().__init__(parent=None, title='大数据1234ryan', pos=(2000, 2000), size=(2500, 1500))
        
        # 创建位图对象列表
        self.bmps = [wx.Bitmap(savapath, wx.BITMAP_TYPE_PNG),
                     wx.Bitmap(savapath, wx.BITMAP_TYPE_PNG),
                     wx.Bitmap(savepath2, wx.BITMAP_TYPE_PNG),
                     wx.Bitmap(savepath1, wx.BITMAP_TYPE_PNG),
                     wx.Bitmap(savepath3, wx.BITMAP_TYPE_PNG),
                     wx.Bitmap(savepath4, wx.BITMAP_TYPE_PNG)]

        # 设置字体
        fnt = wx.Font(pointSize=10, family=wx.ROMAN, style=wx.NORMAL, weight=wx.NORMAL)

        # 最大化窗口并居中显示
        self.Maximize(True)
        self.Centre()

        # 创建面板
        self.panel = wx.Panel(parent=self)

        # 创建水平方向的Box布局管理器对象
        hbox = wx.BoxSizer(wx.HORIZONTAL)

        # 创建静态位图和静态文本控件
        image0_sbitmap = wx.StaticBitmap(self.panel, -1)
        statictext = wx.StaticText(parent=self.panel, label='实验1：网络爬虫开发及数据的可视化')
        fnt1 = wx.Font(pointSize=15, family=wx.ROMAN, style=wx.NORMAL, weight=wx.NORMAL)
        statictext.SetFont(fnt1)

        # 创建按钮控件
        label1 = "OHLC柱状图"
        b1 = wx.Button(parent=self.panel, id=1, label='蜡烛图')
        b12 = wx.Button(parent=self.panel, id=2, label='多日图')
        b13 = wx.Button(parent=self.panel, id=3, label='均线图')
        b2 = wx.Button(self.panel, id=4, label='折线图')
        b3 = wx.Button(self.panel, id=5, label=label1)
        b4 = wx.Button(self.panel, id=6, label='返回')

        # 绑定按钮点击事件
        self.Bind(wx.EVT_BUTTON, self.on_click, id=1, id2=6)

        # 设置按钮控件的字体
        b1.SetFont(fnt)
        b12.SetFont(fnt)
        b13.SetFont(fnt)
        b2.SetFont(fnt)
        b3.SetFont(fnt)
        b4.SetFont(fnt)

        # 创建静态位图控件
        self.image = wx.StaticBitmap(self.panel, -1, self.bmps[0])

        # 添加控件到水平布局管理器
        hbox.Add(b1, proportion=1, flag=wx.CENTER)
        hbox.Add(b12, proportion=1, flag=wx.CENTER)
        hbox.Add(b13, proportion=1, flag=wx.CENTER)
        hbox.Add(b2, proportion=1, flag=wx.CENTER)
        hbox.Add(b3, proportion=1, flag=wx.CENTER)

        # 创建垂直方向的Box布局管理器对象
        vbox = wx.BoxSizer(wx.VERTICAL)
        vbox.Add(statictext, proportion=1, flag=wx.ALIGN_CENTER_HORIZONTAL)
        vbox.Add(image0_sbitmap, proportion=2, flag=wx.ALIGN_CENTER_HORIZONTAL)
        vbox.Add(hbox, proportion=2, flag=wx.CENTER)
        vbox.Add(b4, proportion=1, flag=wx.CENTER)
        vbox.Add(self.image, proportion=1, flag=wx.CENTER | wx.FIXED_MINSIZE)

        # 将垂直布局管理器应用于面板
        self.panel.SetSizer(vbox)

    # 按钮点击事件处理函数
    def on_click(self, event):
        event_id = event.GetId()
        if event_id == 1:
            self.image.SetBitmap(self.bmps[1])
            self.panel.Layout()
        elif event_id == 4:
            self.image.SetBitmap(self.bmps[2])
            self.panel.Layout()
        elif event_id == 5:
            self.image.SetBitmap(self.bmps[3])
            self.panel.Layout()
        elif event_id == 2:
            self.image.SetBitmap(self.bmps[4])
            self.panel.Layout()
        elif event_id == 3:
            self.image.SetBitmap(self.bmps[5])
            self.panel.Layout()
        else:
            self.Close()
            self.Destroy()
            workthread = threading.Thread(target=workthread_body(), name='WorkThread')
            workthread.start()


class MyFrame1(wx.Frame):
    def __init__(self):
        super().__init__(parent=None, title='比亚迪股票查询界面', size=(900, 500))
        self.Centre()
        self.SetMinSize((800, 400))
        #self.Maximize(True)
        self.panel = wx.Panel(parent=self)
        self.panel.SetBackgroundColour(wx.Colour(255, 255, 240))
        
        image0_sbitmap = wx.StaticBitmap(self.panel, -1)
        
        statictext = wx.StaticText(parent=self.panel, label='欢迎使用')
        fnt = wx.Font(pointSize=15, family=wx.ROMAN, style=wx.NORMAL, weight=wx.NORMAL)
        statictext.SetFont(fnt)
        
        # 预定义变量
        self.text = ['', '', '', '']  # 初始月份，初始日期，结束月份，结束日期
        self.data = []
        self.savepath = ''
        self.savepath1 = 'his_bar' + self.savepath
        
        statictext2 = wx.StaticText(self.panel, label='         开始月份')
        list2 = ['', '01', '02', '03', '04', '05', '06', '07', '08', '09', '10', '11', '12']
        self.ch2 = wx.Choice(self.panel, -1, choices=list2)
        self.Bind(wx.EVT_CHOICE, self.on_choice2, self.ch2)
        
        statictext3 = wx.StaticText(self.panel, label='         开始日期')
        list3 = ['', '01', '02', '03', '04', '05', '06', '07', '08', '09', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20', '21', '22', '23', '24', '25', '26', '27', '28', '29', '30', '31']
        self.ch3 = wx.Choice(self.panel, -1, choices=list3)
        self.Bind(wx.EVT_CHOICE, self.on_choice3, self.ch3)
        
        statictext4 = wx.StaticText(self.panel, label='         结束月份')
        list4 = ['', '01', '02', '03', '04', '05', '06', '07', '08', '09', '10', '11', '12']
        self.ch4 = wx.Choice(self.panel, -1, choices=list4)
        self.Bind(wx.EVT_CHOICE, self.on_choice4, self.ch4)
        
        statictext5 = wx.StaticText(self.panel, label='         结束日期')
        list5 = ['', '01', '02', '03', '04', '05', '06', '07', '08', '09', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20', '21', '22', '23', '24', '25', '26', '27', '28', '29', '30', '31']
        self.ch5 = wx.Choice(self.panel, -1, choices=list5)
        self.Bind(wx.EVT_CHOICE, self.on_choice5, self.ch5)
        
        b1 = wx.Button(parent=self.panel, label='查询数据')  # 按钮控件
        b1.SetFont(fnt)
        b1.SetBackgroundColour(wx.Colour(255, 255, 204))
        b1.Bind(wx.EVT_BUTTON, self.showdata, b1)  # 绑定事件
        
        b2 = wx.Button(parent=self.panel, label='展示图表')  # 按钮控件
        b2.Bind(wx.EVT_BUTTON, self.showfig, b2)  # 绑定事件
        
        self.showPanel = wx.Panel(parent=self.panel, size=(1200, 800))  # 展示面板
        self.gridpanel = None  #网格面版
        self.kpanel = None  # 图表面版
        
        # 设置布局
        # 创建水平方向的Box布局管理器对象
        hbox = wx.BoxSizer(wx.HORIZONTAL)
        
        # 添加控件到水平Box布局管理
        hbox.Add(statictext2, proportion=1, flag=wx.EXPAND)
        hbox.Add(self.ch2, proportion=1, flag=wx.ALIGN_LEFT)
        
        hbox.Add(statictext3, proportion=1, flag=wx.EXPAND)
        hbox.Add(self.ch3, proportion=1, flag=wx.ALIGN_LEFT)
        
        hbox.Add(statictext4, proportion=1, flag=wx.EXPAND)
        hbox.Add(self.ch4, proportion=1, flag=wx.ALIGN_LEFT)
        
        hbox.Add(statictext5, proportion=1, flag=wx.EXPAND)
        hbox.Add(self.ch5, proportion=1, flag=wx.ALIGN_LEFT)
        
        hbox1 = wx.BoxSizer(wx.HORIZONTAL)
        hbox1.Add(b1, proportion=1, flag=wx.ALIGN_CENTER)
        hbox1.Add(b2, proportion=1, flag=wx.ALIGN_CENTER)
        
        # 创建垂直方向的Box布局管理对象
        vbox = wx.BoxSizer(wx.VERTICAL)
        
        # 添加控件到垂直Box布局管理器
        vbox.Add(statictext, proportion=1, flag=wx.ALIGN_CENTER_HORIZONTAL)
        vbox.Add(image0_sbitmap, proportion=2, flag=wx.ALIGN_CENTER_HORIZONTAL)
        vbox.Add(hbox, proportion=1, flag=wx.ALIGN_LEFT|wx.TOP, border=10)
        vbox.Add(hbox1, proportion=1, flag=wx.ALIGN_CENTER|wx.TOP, border=10)
        vbox.Add(self.showPanel, proportion=10, flag=wx.EXPAND|wx.ALL, border=10)
        
        self.panel.SetSizer(vbox)

    # 获取用户选择的开始月份
    def on_choice2(self, event):
        self.text[0] = self.ch2.GetStringSelection()

    # 获取用户选择的开始日期
    def on_choice3(self, event):
        self.text[1] = self.ch3.GetStringSelection()

    def on_choice4(self, event):
        self.text[2] = self.ch4.GetStringSelection()

    def on_choice5(self, event):
        self.text[3] = self.ch5.GetStringSelection()

    # 查询表格按钮
    def showdata(self, event):
        datafile = get_data(self.text[0], self.text[1], self.text[2], self.text[3])
        self.data = pd.read_csv(datafile, sep=',').values

        # 将数据展示
        if self.gridpanel:
            self.gridpanel.Destroy()
        if self.kpanel:
            self.kpanel.Destroy()
        self.gridpanel = self.creategridpanel(self.showPanel)
        self.gridpanel.Show()

    # 查询图表按钮
    def showfig(self, event):

        plt.rcParams['font.family'] = ['Microsoft YaHei']
        plt.rcParams['axes.unicode_minus'] = False

        datafile = get_data(self.text[0], self.text[1], self.text[2], self.text[3])
        data = select_for_byd(self.text[0], self.text[1], self.text[2], self.text[3])
        self.savepath = self.text[0]+'-'+self.text[1] + 'to' + self.text[2] +'-'+ self.text[3] +' '+ '.png'

        # 成交量折线图
        # 从date中提取成交量数据
        volume_map = map(lambda it: it['成交量'], data)
        # 蒋volume_map转换为成交量列表
        volume_list = list(volume_map)

        # 从data中提取日期数据
        data_map = map(lambda it: it['日期'], data)
        # 将date_map转换为日期列表
        date_list = list(data_map)
        # 设置图表大小
        plt.figure(figsize=(14, 4))

        dates = date_list
        volumes = volume_list
        # 绘制线段
        plt.plot(dates, volumes)
        plt.setp(plt.gca().get_xticklabels(), rotation=20, horizontalalignment='right')

        plt.title('股票历史成交量', fontsize=20)  # 添加图表标题
        plt.ylabel('成交量', fontsize=20)  # 添加y轴标题
        plt.xlabel('日期', fontsize=20)  # 添加x轴标题

        self.savepath2 = 'pot' + self.savepath
        plt.savefig(self.savepath2)

        def pot_his_bar(date_list, p_list, ylabel):
            """绘制OHLC柱状图"""

            # 绘制柱状图
            plt.bar(date_list, p_list)
            plt.title('股票历史成交量')  # 添加图表标题
            plt.ylabel(ylabel)  # 添加y轴标题
            plt.xlabel('日期')  # 添加x轴标题

        # 从data中提取日期数据
        date_map = map(lambda it: it['日期'], data)
        # 将date_map转换为日期列表
        date_list = list(date_map)

        # 从data中提取开盘价价数据
        open_map = map(lambda it: it['开盘价'], data)
        # 将open_map转换为开盘价价列表
        open_list = list(open_map)

        # 从data中提取最高价价数据
        high_map = map(lambda it: it['最高价'], data)
        # 将high_map转换为最高价价列表
        high_list = list(high_map)

        # 从data中提取最低价价数据
        low_map = map(lambda it: it['最低价'], data)
        # 将low_map转换为最低价价列表
        low_list = list(low_map)

        # 从data中提取收盘价价数据
        close_map = map(lambda it: it['收盘价'], data)
        # 将close_map转换为收盘价价列表
        close_list = list(close_map)

        # 设置图表大小
        plt.figure(figsize=(12, 5))

        plt.subplot(411)
        pot_his_bar(date_list, open_list, '开盘价')
        plt.setp(plt.gca().get_xticklabels(), rotation=15, horizontalalignment='right')

        plt.subplot(412)
        pot_his_bar(date_list, close_list, '收盘价')
        plt.setp(plt.gca().get_xticklabels(), rotation=15, horizontalalignment='right')

        plt.subplot(413)
        pot_his_bar(date_list, high_list, '最高价')
        plt.setp(plt.gca().get_xticklabels(), rotation=15, horizontalalignment='right')

        plt.subplot(414)
        pot_his_bar(date_list, low_list, '最低价')
        plt.setp(plt.gca().get_xticklabels(), rotation=15, horizontalalignment='right')

        plt.tight_layout()  # 调整布局
        plt.savefig('his_bar' + self.savepath)

        self.savepath1 = 'his_bar' + self.savepath


        """绘制阴阳烛图1"""
        # 从CSV文件中读取数据到DataFrame数据结构中
        quotes = pandas.read_csv(datafile,
                                 index_col=0,
                                 parse_dates=True,
                                 infer_datetime_format=True)

        # 绘制一个子图，并设置子图大小
        fig, ax = plt.subplots(figsize=(15, 5))
        # 调整子图参数SubplotParams
        fig.subplots_adjust(bottom=0.2)

        mpl_finance.candlestick_ohlc(ax, zip(mdates.date2num(quotes.index.to_pydatetime()),
                                             quotes['开盘价'], quotes['最高价'],
                                             quotes['最低价'], quotes['收盘价']),
                                     width=1, colorup='r', colordown='g', alpha=0.6)
        ax.xaxis_date()
        ax.autoscale_view()
        quotes['日成交量中位数'] = (quotes['最高价'] + quotes['最低价']) / 2
        plt.plot(quotes.index, quotes['开盘价'], 'r-', label='开盘价')
        plt.plot(quotes.index, quotes['收盘价'], 'g-', label='收盘价')
        # plt.plot(quotes.index, quotes['最高价'], 'b-', label='最高价价')
        # plt.plot(quotes.index, quotes['最低价'], 'y-', label='最低价价')
        plt.plot(quotes.index, quotes['日成交量中位数'], 'cyan', label='日成交量中位数')
        plt.legend(loc='best', fontsize=16)
        plt.setp(plt.gca().get_xticklabels(), rotation=20, horizontalalignment='right')

        plt.savefig(self.savepath)


        """绘制阴阳烛图2"""
        # 从CSV文件中读取数据到DataFrame数据结构中
        quotes1 = pandas.read_csv(datafile,     
                                  index_col=0,
                                  parse_dates=True,
                                  infer_datetime_format=True)
        quotes1.reset_index(inplace=True)
        quotes1 = quotes1[['日期', '开盘价', '收盘价', '最低价', '最高价', '成交量']]
        quotes1.columns = ['datetime', 'open', 'close', 'low', 'high', 'volume']

        quotes1["datetime"] = pandas.to_datetime(quotes1["datetime"])

        quotes1.set_index("datetime", inplace=True)

        s = mpf.make_mpf_style(base_mpf_style='yahoo', rc={'font.family': 'Microsoft YaHei'})
        mpf.plot(
            data=quotes1,
            type="candle",
            ylabel="金额(￥)",
            style=s,
            figsize=(14, 5),
            mav=(3, 5),  # 整数，或包含整数的列表/元组
            volume=True,
            savefig='蜡烛图2' + self.savepath,
            ylabel_lower="成交量",
            figscale=2
        )
        self.savepath3 = '蜡烛图2' + self.savepath

        """绘制阴阳烛图3"""
        s1 = mpf.make_mpf_style(base_mpf_style='default', rc={'font.family': 'Microsoft YaHei'})
        mpf.plot(
            data=quotes1,
            type="candle",
            ylabel="金额(￥)",
            style=s1,
            figsize=(15, 5),
            mav=(2),  # 整数，或包含整数的列表/元组
            volume=True,
            savefig='蜡烛图3' + self.savepath,
            ylabel_lower="成交量",
            figscale=2
        )

        self.savepath4 = '蜡烛图3' + self.savepath

        self.Close()
        self.Destroy()

        frame = MyFrame2(self.savepath, self.savepath1, self.savepath2, self.savepath3, self.savepath4)
        frame.Show()

    # 创建表格
    def creategridpanel(self, parent):
        panel = wx.Panel(parent, size=(1000, 600))  # 创建一个大小为(1000, 600)的面板
        grid = wx.grid.Grid(panel, name='grid', size=(1000, 600))  # 在面板上创建一个网格控件，名称为'grid'，大小为(1000, 600)
        self.initGrid()  # 调用初始化表格的函数

        box = wx.BoxSizer()  # 创建一个BoxSizer布局管理器
        box.Add(grid, 1, flag=wx.ALL | wx.EXPAND, border=0)  # 将网格控件添加到BoxSizer中，设置扩展标志和边框
        panel.SetSizer(box)  # 将BoxSizer设置为面板的布局管理器

        return panel  # 返回创建的面板

    # 初始化表格
    def initGrid(self):
        grid = self.FindWindowByName('grid')  # 根据名称查找网格控件
        table = MyGridTable(self.data)  # 创建一个自定义的表格数据对象
        grid.SetTable(table, True)  # 将表格数据对象设置为网格控件的数据源

        # 设置行列宽
        rowsizeinfo = wx.grid.GridSizesInfo(30, [])  # 设置行高信息，行高为30
        grid.SetRowSizes(rowsizeinfo)  # 应用行高信息到网格控件

        colsizeinfo = wx.grid.GridSizesInfo(0, [200, 140, 140, 140, 140, 140, 140, 180, 220, 180, 180])  # 设置列宽信息，第一列宽度为200，其他列宽度依次为140, 140, 140, 140, 140, 140, 180, 220, 180, 180
        grid.SetColSizes(colsizeinfo)  # 应用列宽信息到网格控件

        return grid  # 返回网格控件


class MyFrame(wx.Frame):
    def __init__(self):
        super().__init__(parent=None, title='大数据1234_ryan_888888', size=(600, 370))
        self.Centre()  # 设置窗口居中
        panel = wx.Panel(parent=self)
        fnt1 = wx.Font(pointSize=15, family=wx.ROMAN, style=wx.NORMAL, weight=wx.NORMAL)
        fnt = wx.Font(pointSize=20, family=wx.ROMAN, style=wx.NORMAL, weight=wx.NORMAL)
        
        panel.SetBackgroundColour(wx.Colour(255, 255, 240))  # 设置背景颜色为奶白色
        
        # 创建垂直方向的Box布局管理器
        self.sizer = wx.BoxSizer(wx.VERTICAL)
        
        # 创建静态位图
        image0_sbitmap = wx.StaticBitmap(panel, -1)
        
        # 创建静态文本
        self.statictext = wx.StaticText(parent=panel, label="欢迎使用比亚迪股票数据查询系统", style=wx.ALIGN_CENTER_HORIZONTAL)
        self.statictext.SetFont(fnt)
        
        # 创建按钮
        b1 = wx.Button(parent=panel, label='进入')
        b1.SetBackgroundColour(wx.Colour(255, 255, 204))
        self.Bind(wx.EVT_BUTTON, self.on_click, b1)

        b2 = wx.Button(parent=panel, label='退出')
        b2.SetBackgroundColour(wx.Colour(255, 255, 204))
        self.Bind(wx.EVT_BUTTON, self.on_click1, b2)

        b3 = wx.BitmapButton(panel, -1)
        self.Bind(wx.EVT_BUTTON, self.on_click, b3)

        b1.SetFont(fnt1)
        b2.SetFont(fnt1)

        # 添加控件到Box布局管理器
        self.sizer.Add(20, 20)  # 添加垂直间距
        self.sizer.Add(self.statictext, proportion=1, flag=wx.CENTER | wx.FIXED_MINSIZE)  # 设置静态文本的属性
        self.sizer.Add(image0_sbitmap, proportion=2, flag=wx.CENTER | wx.FIXED_MINSIZE)  # 设置静态位图的属性
        self.sizer.Add(20, 10)  # 添加垂直间距
        self.sizer.Add(b1, proportion=2, flag=wx.CENTER | wx.EXPAND)  # 设置按钮的属性
        self.sizer.Add(b2, proportion=2, flag=wx.CENTER | wx.EXPAND)  # 设置按钮的属性
        self.sizer.Add(b3, proportion=0, flag=wx.CENTER | wx.EXPAND)  # 设置按钮的属性
        self.sizer.Add(20, 20)  # 添加垂直间距
        panel.SetSizer(self.sizer)  # 设置Panel的布局管理器

    def on_click(self, event):
        # 跳转到新界面
        self.Close()
        self.Destroy()
        
        # 创建并启动工作线程
        workthread = threading.Thread(target=workthread_body(), name='WorkThread')
        workthread.start()

    def on_click1(self, event):
        wx.MessageBox("退出!")
        self.Close()
        self.Destroy()


class App1(wx.App):
    def OnInit(self):
        # 创建窗口对象
        frame = MyFrame1()
        frame.Show()
        return True

class App(wx.App):
    def OnInit(self):
        # 创建窗口对象
        frame = MyFrame()
        frame.Show()
        return True

def workthread_head():
    app = App()
    app.MainLoop()   # 进入主事件循环

def workthread_body():
    global result
    app = App1()
    app.MainLoop()  # 进入主事件循环

if __name__ == '__main__':
    workthread = threading.Thread(target=workthread_head(), name='WorkThread')
    workthread.start()