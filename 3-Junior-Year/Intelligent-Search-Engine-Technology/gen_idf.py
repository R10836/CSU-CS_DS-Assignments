import json
import math
import configparser
import sqlite3


def gen_idf_file():
    config = configparser.ConfigParser()
    config.read('config.ini', encoding="utf-8")
    conn = sqlite3.connect(config['DEFAULT']['db_path'])
    cur = conn.cursor()
    cur.execute('select * from news;')
    results = cur.fetchall()
    cur.close()
    conn.close()

    word_idf_dict: dict[str, int] = {}
    word_sum_cnt = 0
    for result in results:
        word_dict = json.loads(result[5])
        for word, [word_cnt, _] in word_dict.items():
            if word not in word_idf_dict.keys():
                word_idf_dict[word] = word_cnt
            else:
                word_idf_dict[word] += word_cnt
            word_sum_cnt += word_cnt

    idf_file = open(config['DEFAULT']['idf_path'], 'w', encoding='utf-8')
    for word, cnt in word_idf_dict.items():
        idf_file.write('{} {}\n'.format(word, math.log(word_sum_cnt/cnt)))
    idf_file.close()


if __name__ == "__main__":
    gen_idf_file()
