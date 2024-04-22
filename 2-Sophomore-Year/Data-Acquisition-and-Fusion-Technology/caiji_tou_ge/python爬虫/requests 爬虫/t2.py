import requests


def get_html(url, headers=None):
    '''
    两个参数
    :param url:统一资源定位符,请求网址
    :param headers:请求头
    :return html 网页的源码
    :return sess 创建的会话
    '''

    # ***************** Begin ******************** #

    # 补充请求头
    headers = headers or {}

    # 创建Session, 并使用Session的get请求网页
    sess = requests.Session()
    response = sess.get(url, headers=headers)

    # 获取网页信息文本
    html = response.text

    # ****************** End ********************* #

    return html, sess
