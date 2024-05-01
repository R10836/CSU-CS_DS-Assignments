# -*- coding: utf-8 -*-

from sklearn.datasets import load_iris  # 获取现成的数据集
from sklearn.model_selection import train_test_split  # 将数据集划分为训练集和测试集
from sklearn.feature_extraction import DictVectorizer  # 字典特征抽取
from sklearn.feature_extraction.text import CountVectorizer, TfidfVectorizer  # 文本特征抽取
from sklearn.preprocessing import MinMaxScaler, StandardScaler  # 特征预处理
from sklearn.feature_selection import VarianceThreshold  # 降维：特征选择：过滤式：方差选择法（低方差特征过滤）
from scipy.stats import pearsonr  # 降维：特征选择：过滤式：相关系数
from sklearn.decomposition import PCA  # 降维：主成分分析

import pandas as pd
import jieba  # 中文文本分词


def datasets_demo():
    """
    sklearn数据集使用

    具体来说，load_iris()函数返回一个包含鸢尾花数据集的对象，这个对象是一个类似于字典的数据结构，包含了以下内容：
    data：一个二维数组，每一行代表一个样本，每一列代表一个特征（如花萼长度、花萼宽度、花瓣长度、花瓣宽度）。
    target：一个一维数组，代表每个样本的类别标签，即鸢尾花的种类（如setosa、versicolor、virginica）。
    target_names：一个一维数组，包含了所有可能的类别标签。
    feature_names：一个一维数组，包含了特征的名称。
    DESCR：一个字符串，包含了对数据集的描述信息。
    """

    # 获取数据集
    iris = load_iris()
    # 打印鸢尾花数据集
    # print("鸢尾花数据集：\n", iris)
    # print("查看数据集描述：\n", iris["DESCR"])
    # print("查看特征值的名字：\n", iris.feature_names)
    # print("查看特征值：\n", iris.data, iris.data.shape)  # .shape 是 NumPy 数组对象的属性之一，用于获取数组的形状信息。具体来说，iris.data.shape的值是一个二元组，第一个元素表示数组的行数（样本数量），第二个元素表示数组的列数（特征数量）
    x_train, x_test, y_train, y_test = train_test_split(iris.data, iris.target, test_size=0.2,
                                                        random_state=22)  # train_test_split()函数是scikit-learn库中的一个函数，用于将数据集划分为训练集和测试集。
    print("训练集的特征值：\n", x_train, x_train.shape)  # 打印训练集的特征值和形状。因为test_size=0.2，故训练集条数为 (0.8*数据集) 。
    return None


def save_iris_dataset():
    """
    保存鸢尾花数据集到本地文件
    sepal length 是 萼片长度
    sepal width  是 萼片宽度
    petal length 是 花瓣长度
    petal width  是 花瓣宽度
    setosa 山鸢尾
    versicolor 变色鸢尾
    virginica 弗吉尼亚鸢尾
    """
    # 加载鸢尾花数据集
    iris = load_iris()

    # 创建一个DataFrame对象，将特征值和目标值合并到一起
    df = pd.DataFrame(data=iris.data, columns=iris.feature_names)

    # 将目标名称加载到DataFrame中
    df['target'] = iris.target
    df['target_name'] = iris.target_names[iris.target]

    # 将DataFrame保存为CSV文件
    df.to_csv('iris_dataset.csv', index=False)
    print("鸢尾花数据集已保存到 iris_dataset.csv 文件。")


def dict_demo():
    """

    :return:
    """
    data = [{'city': 'peking', 'temperature': 10}, {'city': 'new york', 'temperature': 80},
            {'city': 'london', 'temperature': -50}]
    # 1：实例化一个转换器类
    transfer = DictVectorizer(sparse=False)
    # 2：调用fit_transform()方法，传入字典或字典迭代器
    new_data = transfer.fit_transform(data)
    print("new data:\n", new_data)
    print("特征名字(feature name):\n", transfer.get_feature_names_out())

    return None


def count_demo():
    """
    文本特征抽取，用CountVecotrizer方法
    """
    data = ["life is short, I like like python", "life is too long, I dislike python"]
    # 步骤1：实例化一个转换器类
    transfer = CountVectorizer()
    # 步骤2：调用转化器类里面的fit_transform方法
    new_data = transfer.fit_transform(data)
    print("new data:\n", new_data.toarray())
    print("特征名字:\n", transfer.get_feature_names_out())
    return None


def count_demo_chinese():
    """
    中文文本特征抽取，用CountVecotrizer方法
    """
    data = ["所有 动物 一律 平等", "但 有些 动物 比 其他 动物 更 平等"]
    # 步骤1：实例化一个转换器类
    transfer = CountVectorizer()
    # 步骤2：调用转化器类里面的fit_transform方法
    new_data = transfer.fit_transform(data)
    print("new data:\n", new_data.toarray())
    print("特征名字:\n", transfer.get_feature_names_out())
    return None


def count_demo_chinese2():
    """
    jieba中文文本特征抽取、自动分词
    cut_CN_word = lambda your_str: " ".join(list(jieba.cut(your_str)))
    """

    # 1、将中文文本进行分词
    def cut_cn_word(your_cn_str):
        return " ".join(list(jieba.cut(your_cn_str)))

    data = ["曾经有一份真诚的爱情放在我面前，我没有珍惜，等我失去的时候我才后悔莫及，人世间最痛苦的事莫过于此。",
            "如果上天能够给我一个再来一次的机会，我会对那个女孩说三个字：我爱你。",
            "如果非要在这份爱上加上一个期限，我希望是一万年。"]
    data2 = []
    for sentences in data:
        data2.append(cut_cn_word(sentences))
    print(data2)

    # 2、实例化一个转化器类
    transfer = CountVectorizer(stop_words=["一个", "三个", "一份", "一次"])
    # 3：调用fit_transform()方法，传入字典或字典迭代器
    new_data = transfer.fit_transform(data2)
    print("new data:\n", new_data.toarray())
    print("特征名字(feature name):\n", transfer.get_feature_names_out())


def tfidf_demo():
    """
    用TF-IDF的方法进行文本特征抽取
    """

    # 1、将中文文本进行分词
    def cut_cn_word(your_cn_str):
        return " ".join(list(jieba.cut(your_cn_str)))

    data = ["曾经有一份真诚的爱情放在我面前，我没有珍惜，等我失去的时候我才后悔莫及，人世间最痛苦的事莫过于此。",
            "如果上天能够给我一个再来一次的机会，我会对那个女孩说三个字：我爱你。",
            "如果非要在这份爱上加上一个期限，我希望是一万年。"]
    data2 = []
    for sentences in data:
        data2.append(cut_cn_word(sentences))
    print(data2)

    # 2、实例化一个转化器类
    transfer = TfidfVectorizer(stop_words=["一个", "三个", "一份", "一次"])
    # 3：调用fit_transform()方法，传入字典或字典迭代器
    new_data = transfer.fit_transform(data2)
    print("new data:\n", new_data.toarray())
    print("特征名字(feature name):\n", transfer.get_feature_names_out())


def minmax_demo():
    """
    归一化
    """
    # 1、获取数据
    data = pd.read_csv("dating.txt")
    data = data.iloc[:, :3]
    # print(data)
    # 2、实例化一个转化器类
    transfer = MinMaxScaler()
    # 3、调用fit_transform()
    data_new = transfer.fit_transform(data)
    print(data_new)

    return None


def standard_demo():
    """
    标准化
    """
    # 1、获取数据
    data = pd.read_csv("dating.txt")
    data = data.iloc[:, :3]
    # print(data)
    # 2、实例化一个转化器类
    transfer = StandardScaler()
    # 3、调用fit_transform()
    data_new = transfer.fit_transform(data)
    print(data_new)
    return None


def variance_demo():
    """
    低方差过滤
    """
    # 1、获取数据
    data = pd.read_csv("factor_returns.csv")
    data = data.iloc[:, 1:-2]
    print(data)
    # 2、实例化一个转换器类
    transfer = VarianceThreshold(threshold=10)
    # 3、调用fit_transform()
    data_new = transfer.fit_transform(data)
    print(data_new, data_new.shape)

    # 4、计算某两个变量之间的相关系数r
    r1 = pearsonr(data["pe_ratio"], data["pb_ratio"])
    print("相关系数：\n", r1)
    r2 = pearsonr(data["revenue"], data["total_expense"])
    print("revenue与total_expense的相关性：\n", r2)
    return None


def pca_demo():
    """
    PCA降维
    """
    data = [[2, 8, 4, 5],
            [6, 3, 0, 8],
            [5, 4, 9, 1]]
    # 1、实例化一个转换器类
    transfer = PCA(n_components=2)
    # 2、调用fit_transform()方法
    data_new = transfer.fit_transform(data)
    """
    data_new: [[ 1.28620952e-15  3.82970843e+00]
                [ 5.74456265e+00 -1.91485422e+00]
                [-5.74456265e+00 -1.91485422e+00]]
    """
    print(data_new)
    return None


if __name__ == "__main__":
    # 1-1、sklearn数据集使用：
    # datasets_demo()

    # 1-2：保存数据集到本地文件：
    # save_iris_dataset()

    # 2：字典特征抽取：
    # dict_demo()

    # 3-1：文本特征抽取：
    # count_demo()

    # 3-2：中文文本特征抽取：
    # count_demo_chinese()

    # 3-3：中文文本分词：
    # count_demo_chinese2()

    # 3-4：tfidf
    # tfidf_demo()

    # 4-1：特征预处理：归一化
    # minmax_demo()

    # 4-2：标准化
    # standard_demo()

    # 5-1：降维：特征选择：过滤式：方差选择法（低方差特征过滤）
    # variance_demo()

    # 5-2：降维：主成分分析
    pca_demo()
