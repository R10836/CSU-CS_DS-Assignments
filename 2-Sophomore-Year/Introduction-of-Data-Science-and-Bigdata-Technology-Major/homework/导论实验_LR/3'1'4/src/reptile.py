#!/usr/bin/env python3
# coding: utf-8

"""
爬取猫眼
"""

import requests

from bs4 import BeautifulSoup


# 爬取
def get_html(my_url, my_headers):
    """

    :param my_url:
    :param my_headers:
    :return:requests class
    """
    response = requests.get(my_url, headers=my_headers)

    if response.status_code == 200:
        # print(response.text)
        print('成功：')
    else:
        print('请求失败，状态码：', response.status_code)

    return response.text


# 处理
def parse_html(html):
    """

    :param html:
    :return:
    """
    soup = BeautifulSoup(html, 'html.parser')

    print(soup.prettify())


if __name__ == '__main__':
    url = 'https://ssr1.scrape.center/'
    headers = {
        'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,'
                  'application/signed-exchange;v=b3;q=0.7',
        'Accept-Encoding': 'gzip, deflate, br, zstd',
        'Accept-Language': 'zh-CN,zh;q=0.9,en-US;q=0.8,en;q=0.7',
        'Cache-Control': 'max-age=0',
        'Connection': 'keep-alive',
        'Host': 'ssr1.scrape.center',
        'Referer': 'https://scrape.center/',
        'Sec-Fetch-Dest': 'document',
        'Sec-Fetch-Mode': 'navigate',
        'Sec-Fetch-Site': 'same-site',
        'Sec-Fetch-User': '?1',
        'Upgrade-Insecure-Requests': '1',
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) '
                      'Chrome/119.0.0.0'
                      'Safari/537.36',
        'sec-ch-ua': '"Google Chrome";v="119", "Chromium";v="119", "Not?A_Brand";v="24"',
        'sec-ch-ua-mobile': '?0',
    }

    html_content = get_html(url, headers)
    parse_html(html_content)
