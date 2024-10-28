import json

import scrapy
import scrapy.http
import news_spider.configs
import re

from news_spider.items import NewsItem


class QqspiderSpider(scrapy.Spider):
    name = "qqspider"
    allowed_domains = ["news.qq.com", "new.qq.com"]
    base_url = "https://i.news.qq.com/trpc.qqnews_web.kv_srv.kv_srv_http_proxy/list?sub_srv_id=24hours&srv_id=pc&offset={}&limit=20&strategy=1&ext={{\"pool\":[\"top\",\"hot\"],\"is_filter\":7,\"check_type\":true}}"

    def start_requests(self):
        urls = [self.base_url.format(
            20*i) for i in range(news_spider.configs.QQSPIDER_SCRAPY_NUM)]
        for url in urls:
            yield scrapy.Request(url, callback=self.parse)

    def parse(self, response: scrapy.http.Response):
        json_string = json.loads(response.body)
        item_dict_list = json_string['data']['list']
        for item_dict in item_dict_list:
            url = item_dict['url']
            yield scrapy.Request(url, callback=self.get_text)

    def get_text(self, response: scrapy.http.Response):
        news_item = NewsItem()
        news_item['url'] = response.url
        news_item['title'] = response.xpath("//h1/text()").extract_first()
        paras=response.xpath("//p[@class='one-p']/text()").extract()
        news_item['content']=''.join([para.strip() for para in paras])
        string = ''.join(response.xpath("//script/text()").extract())
        news_item['datetime'] = re.search(
            r'\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}', string).group(0)
        yield news_item
