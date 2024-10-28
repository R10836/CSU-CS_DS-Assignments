import configparser
import json
import sqlite3

import jieba.analyse
import numpy as np
import pandas as pd
from sklearn.metrics import pairwise_distances

from utils.index import InvertedIndex
from utils.utils import get_seq_dict


class IDFManager:
    config = configparser.ConfigParser()
    config.read('config.ini', encoding='utf-8')

    def __init__(self):
        self.conn = sqlite3.connect(self.config['DEFAULT']['db_path'])
        self.cursor = self.conn.cursor()
        self.k_nearest = []

    def query(self, content: str, k=10):
        import pickle
        index_file = open(self.config['DEFAULT']['index_path'], 'rb')
        inverted_index: InvertedIndex = pickle.load(index_file)

        seq_list = get_seq_dict(content)
        doc_index_list: list[int] = []
        for word in seq_list:
            doc_index_list = inverted_index.query(word)
        doc_index_set = set(doc_index_list)
        doc_cnt = len(doc_index_set)

        self.cursor.execute('select * from doctags where id = ' +
                            ' or id= '.join(map(str, doc_index_set))+';')

        results = self.cursor.fetchall()
        matrix = [[0 for _ in range(len(seq_list))]
                  for _ in range(doc_cnt)]
        # word -> matrix_word_index
        word_dict = {j: i for i, j in enumerate(seq_list)}
        id_dict = {id: index for index,
                   id in enumerate(map(lambda x: x[0], results))}    # id -> matrix_doc_index
        for result in results:
            tags = json.loads(result[4])
            for word in seq_list:
                if word in tags.keys():
                    matrix[id_dict[result[0]]][word_dict[word]] = tags[word]

        jieba.analyse.set_stop_words(self.config['DEFAULT']['stopwords_path'])
        jieba.analyse.set_idf_path(self.config['DEFAULT']['idf_path'])
        content_tags = jieba.analyse.extract_tags(
            content, topK=200, withWeight=True)
        print(content_tags)
        content_score = [0]*len(seq_list)
        for (content_tag, score) in content_tags:
            content_score[word_dict[content_tag]] = score

        # cosine similarity
        scores = [(index, np.dot(content_score, vector) / (np.linalg.norm(vector)
                   * np.linalg.norm(content_score)))for index, vector in enumerate(matrix)]
        scores.sort(key=lambda x: x[1], reverse=True)
        k_top = list(
            map(lambda x: (results[x[0]][1], results[x[0]][2]), scores))[:k]
        return k_top

    def construct_dt_matrix(self, topK=200):
        jieba.analyse.set_stop_words(self.config['DEFAULT']['stopwords_path'])
        jieba.analyse.set_idf_path(self.config['DEFAULT']['idf_path'])

        self.cursor.execute('select count(*) from news;')
        total_file = int(self.cursor.fetchall()[0][0])

        self.cursor.execute('select id, content from news;')
        results = self.cursor.fetchall()

        word_set = set()
        dt: list[list] = []
        for result in results:
            content = result[1]
            tags = jieba.analyse.extract_tags(
                content, topK=topK, withWeight=True)
            clean_dict: dict[str, float] = {tag[0]: tag[1] for tag in tags}
            dt.append([result[0], clean_dict])
            terms.union(set(tags))

        total_word = len(word_set)
        terms: dict[str, int] = {j: i for i, j in enumerate(
            word_set)}   # word to word_index

        dt_matrix = [[0 for i in range(total_word)]
                     for j in range(total_file)]   # file x word

        i = 0
        for docid, t_tfidf in dt:
            dt_matrix[i][0] = docid
            for term, tfidf in t_tfidf.items():
                dt_matrix[i][terms[term]] = tfidf
            i += 1

        dt_matrix = pd.DataFrame(dt_matrix)
        dt_matrix.index = dt_matrix[0]
        return dt_matrix

    def construct_k_nearest_matrix(self, dt_matrix: pd.DataFrame, k):
        k_nearest = []
        tmp = np.array(
            1 - pairwise_distances(dt_matrix[dt_matrix.columns[1:]], metric="cosine"))
        similarity_matrix = pd.DataFrame(
            tmp, index=dt_matrix.index.tolist(), columns=dt_matrix.index.tolist())
        for i in similarity_matrix.index:
            tmp = [int(i), []]
            j = 0
            while j < k:
                max_col = similarity_matrix.loc[i].idxmax(axis=1)
                similarity_matrix.loc[i][max_col] = -1
                if max_col != i:
                    tmp[1].append(int(max_col))  # max column name
                    j += 1
            k_nearest.append(tmp)
        # k_nearest: list[list[docId, 1st_nearest_docId,...kth_nearest_docId]]
        return k_nearest

    def extract_tags_to_db(self, topK):
        jieba.analyse.set_stop_words(self.config['DEFAULT']['stopwords_path'])
        jieba.analyse.set_idf_path(self.config['DEFAULT']['idf_path'])
        self.cursor.execute("drop table if exists doctags;")
        self.cursor.execute(
            "create table if not exists doctags(id integer primary key,url text,title text,content text,tags text);")
        self.cursor.execute("select id,url,title,content from news")
        results = self.cursor.fetchall()
        for result in results:
            id = result[0]
            url = result[1]
            title = result[2]
            content = result[3]
            tags = jieba.analyse.extract_tags(
                content, topK=topK, withWeight=True)
            tags_dict = {tag[0]: tag[1] for tag in tags}
            self.cursor.execute(
                "insert into doctags values(?,?,?,?,?)", (id, url, title, content, json.dumps(tags_dict)))
        self.conn.commit()

    def write_k_nearest_matrix_to_db(self, k_nearest):
        self.cursor.execute('''drop table if exists knearest''')
        self.cursor.execute('''create table knearest
                        (id integer primary key, recomended text)''')

        for docid, doclist in k_nearest:
            self.cursor.execute(
                "insert into knearest values (?, ?)", (docid, json.dumps(doclist)))

        self.conn.commit()

    def find_k_nearest(self, docid: int) -> list[int]:
        self.cursor.execute('select * from knearest where id = ?', (docid))
        results = self.cursor.fetchall()
        if results == []:
            return None
        else:
            return json.loads(results[0][1])

    def update(self):
        self.extract_tags_to_db()
