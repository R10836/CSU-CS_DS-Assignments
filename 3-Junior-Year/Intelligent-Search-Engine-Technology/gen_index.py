import configparser
import json
import sqlite3

from utils.index import InvertedIndex


def gen_indx():
    config = configparser.ConfigParser()
    config.read('config.ini', encoding='utf-8')
    conn = sqlite3.connect(config['DEFAULT']['db_path'])
    cur = conn.cursor()
    cur.execute('select * from news;')
    results = cur.fetchall()
    cur.close()
    conn.close()

    index = InvertedIndex()
    for result in results:
        index.puts_url(result[0], result[1])
        word_dict = json.loads(result[5])
        for word, [_, position_lst] in word_dict.items():
            index.insert(word, result[1], position_lst)

    index.write_in_file(config['DEFAULT']['index_path'])


if __name__ == "__main__":
    gen_indx()
