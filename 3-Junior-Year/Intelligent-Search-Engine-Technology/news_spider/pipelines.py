# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html


# useful for handling different item types with a single interface


import configparser
import json
import sqlite3

from utils.utils import get_seq_dict


class NewsspiderPipeline:
    def process_item(self, item, spider):
        config=configparser.ConfigParser()
        config.read('config.ini',encoding='utf-8')
        conn = sqlite3.connect(config['DEFAULT']['db_path'])
        cursor = conn.cursor()

        content = item['content']
        words_dict = get_seq_dict(content)
        item['words_dict'] = json.dumps(words_dict)

        cursor.execute(
            "create table if not exists news (id integer primary key autoincrement,url text,title text,content text,datetime text,words_dict text);")

        cursor.execute("insert into news (url,title,content,datetime,words_dict) values (?,?,?,?,?)",
                       (item['url'], item['title'], item['content'], item['datetime'], item['words_dict']))
        conn.commit()
        cursor.close()
        conn.close()
        return item
