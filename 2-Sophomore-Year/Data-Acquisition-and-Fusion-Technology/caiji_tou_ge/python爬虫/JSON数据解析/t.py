import urllib.request
from lxml import etree
import http.cookiejar
import json


def request_sess(url, headers):
    cj = http.cookiejar.CookieJar()
    opener = urllib.request.build_opener(urllib.request.HTTPCookieProcessor(cj))
    request = urllib.request.Request(url=url, headers=headers)
    r = opener.open(fullurl=request)
    html = r.read().decode('utf-8')
    return html


def save_data(path):
    """
    :param path: 文件保存路径
    :return: 无
    """
    url = 'http://127.0.0.1:8080/index'
    headers = {
        'User-Agent': 'Mozilla/5.0 (Linux; Android 8.0.0; Pixel 2 XL Build/OPD1.170816.004) AppleWebKit/537.36 ('
                      'KHTML, like Gecko) Chrome/83.0.4103.116 Mobile Safari/537.36'
    }
    # ********** Begin ************** #

    # 调用函数 request_sess() 获取网页的 JSON 数据
    json_data = json.loads(request_sess(url, headers))

    # 输出 JSON 数据中的 key 值为 code 对应的数据
    code_data = json_data.get('code', None)
    print(code_data)

    # 将爬取下来的 JSON 数据保存到本地
    with open(path, 'w', encoding='utf-8') as file:
        json.dump(json_data, file, ensure_ascii=False)

    # ********** End ************** #
