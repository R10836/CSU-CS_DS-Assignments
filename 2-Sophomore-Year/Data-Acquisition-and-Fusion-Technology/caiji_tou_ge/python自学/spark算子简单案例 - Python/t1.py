# -*- coding: UTF-8 -*-
from pyspark import SparkContext

if __name__ == "__main__":

    """
        需求：对本地文件系统URI为：/root/wordcount.txt 的内容进行词频统计
    """
    # ********** Begin **********#

    # 创建SparkContext
    sc = SparkContext("local", "WordCount")

    # 读取文本文件
    lines = sc.textFile("/root/wordcount.txt")

    # 切分每一行的单词
    words = lines.flatMap(lambda line: line.split(" "))

    # 统计每个单词的出现次数
    word_counts = words.countByValue()

    # 调整输出格式为列表，将unicode字符串转换为普通字符串
    output = [(str(word), count) for word, count in word_counts.items()]

    # 按照出现次数降序排序
    sorted_output = sorted(output, key=lambda x: x[1], reverse=True)

    # 打印结果
    print(sorted_output)

    # 关闭SparkContext
    sc.stop()

    # ********** End **********#
