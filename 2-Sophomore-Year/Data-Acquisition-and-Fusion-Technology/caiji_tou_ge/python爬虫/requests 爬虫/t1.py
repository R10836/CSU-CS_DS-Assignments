import requests


def get_html(url, headers=None):
    '''
    两个参数
    :param url:统一资源定位符,请求网址
    :param headers:请求头
    :return:html
    '''

    # ***************** Begin ******************** #

    # 补充请求头
    headers = headers or {}

    # get请求网页
    response = requests.get(url, headers=headers)

    # 获取网页信息文本
    html = response.text

    # ***************** End ******************** #

    return html
