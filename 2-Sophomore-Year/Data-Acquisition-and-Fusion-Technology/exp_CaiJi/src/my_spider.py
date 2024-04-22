#!/usr/bin/env python3
# coding: utf-8

"""
大数据采集与融合技术实验
数据采集和数据存储
大数据2103 茹湘原 8204193010
"""


import re

import pandas as pd
import requests
from pyquery import PyQuery as pq


# 获取页面内容
def fetch_page(url, headers, trying_time):
    """
    尝试多次获取页面内容，直到成功或达到最大尝试次数。

    :param url: 目标URL
    :param headers: 请求头信息
    :param trying_time: 最大尝试次数
    :return: 成功获取到的响应对象或None
    """
    for second in range(1, trying_time + 1):
        try:
            response = requests.get(url, headers=headers, timeout=(3, 7))
            if response.status_code == 200:
                return response
        except requests.RequestException as e:
            print(f'Request failed {second} time: {e}')

    print('Failed to fetch the page after multiple attempts.')
    return None


# 获取每一页的信息
def get_one_page(district, page):
    """
    获取指定区域和页码的房屋信息并存储到CSV文件中。

    :param district: 区域信息
    :param page: 页码
    :return: None
    """
    # 构造请求的 URL 和请求头
    url = original_url.format(district) + 'pg{}/'.format(page)
    headers = {"User-Agent": user_agent}

    # 获取页面内容
    res = fetch_page(url, headers, time)
    if res is None:
        return None
    doc = pq(res.text)  # 使用 PyQuery 解析页面

    # 获取房屋信息所在的<ul>标签
    ul = doc('.sellListContent')

    # 获取每个房屋信息的<div>标签
    divs = ul.children('.clear .info.clear').items()

    # 通过字典的形式创建DataFrame
    df = pd.DataFrame(columns=column)

    # 遍历每个房屋信息的<div>标签
    for div in divs:
        # 基础信息
        title = div.children('.title a').text()  # 标题信息
        community = div.children('.address .flood .positionInfo a').text()  # 小区信息
        msg = div.children('.address .houseInfo').text()  # 其他信息

        # 楼层
        try:
            floor = re.findall('[低|中|高]楼层', msg)[0]
        except IndexError:
            floor = None

        # 建成年份
        try:
            year = re.findall(r'\d+年', msg)[0].split('年')[0]
        except IndexError:
            year = None

        # 几室几厅
        try:
            model = re.findall(r'\d室\d厅', msg)[0]
            bedroom = int(re.findall(r'\d', model)[0])  # 室
            living_room = int(re.findall(r'\d', model)[1])  # 厅
        except IndexError:
            bedroom = None
            living_room = None

        # 面积
        try:
            area = float(re.findall(r'\d+\.*\d*平米', msg)[0].split('平米')[0])  # 面积
        except IndexError:
            area = None

        # 总价、单价
        price = div.children('.address .priceInfo .totalPrice span').text()  # 价格
        yuan_per_meter = int(
            div.children('.address .priceInfo .unitPrice span').text().split('元/平')[0].replace(',', ''))

        # 将提取的信息存入DataFrame
        df.loc[len(df)] = {'district': districts[district], 'title': title,
                           'community': community, 'floor': floor, 'year': year,
                           'bedroom': bedroom, 'living_room': living_room, 'area': area, 'price': price,
                           'unit_price': yuan_per_meter}

    # 将DataFrame数据追加到CSV文件
    df.to_csv('../data/prices.csv', mode='a', index=False, columns=column, encoding="utf-8", header=None)


# 获得末页的页码
def get_end_page(district):
    """
    获取指定行政区的二手房信息的尾页页码。

    :param district: 行政区名称
    :return: 尾页的页码，如果获取失败则返回 None
    """
    # 构造请求的 URL 和请求头
    url = original_url.format(district)
    headers = {"User-Agent": user_agent}

    # 获取页面内容
    res = fetch_page(url, headers, time)
    if res is None:
        return None
    doc = pq(res.text)  # 使用 PyQuery 解析页面

    # 提取页面中的页码信息
    html = doc('.page-box').html()
    end_page = int(re.findall(r'\d+', html)[0])  # 正则筛选出数字
    return end_page


# 原始url
original_url = 'https://cs.ke.com/ershoufang/{}/'

# 用户代理
user_agent = ('Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/119.0.0.0 '
              'Safari/537.36')

# 规定相应的城区，建立相应的字典
districts = {'yuhua': '雨花', 'yuelu': '岳麓', 'tianxin': '天心', 'kaifu': '开福', 'furong': '芙蓉', 'wangcheng': '望城',
             'ningxiang': '宁乡', 'liuyang': '浏阳', 'changshaxian': '长沙县'}

# 规定相应的列
column = ['district', 'title', 'community', 'floor', 'year', 'bedroom', 'living_room', 'area', 'price', 'unit_price']

# 重复请求的次数
time = 5


# 表头先写入CSV文件
df = pd.DataFrame(columns=column)
df.to_csv('../data/prices.csv', mode='a', index=False,
          columns=column, encoding="utf-8")

# 按区遍历爬取
for area in districts.keys():
    end_page = get_end_page(area)  # 获取每个区的最后一页的页码
    for p in range(1, end_page + 1):
        print('The page being crawled: {}'.format(p))
        get_one_page(area, p)
