# -*- coding: utf-8 -*-

from sklearn.datasets import load_iris
from sklearn.datasets import fetch_20newsgroups

from sklearn.model_selection import train_test_split  # 划分数据集
from sklearn.preprocessing import StandardScaler  # 特征工程标准化
from sklearn.feature_extraction.text import TfidfVectorizer  # 文本特征抽取

from sklearn.neighbors import KNeighborsClassifier  # KNN算法预估器
from sklearn.model_selection import GridSearchCV  # 模型选择与模型评估，加入网格搜索与交叉验证
from sklearn.naive_bayes import MultinomialNB  # 朴素贝叶斯
from sklearn.tree import DecisionTreeClassifier, export_graphviz  # 决策树


def knn_iris():
    """
    用knn算法对鸢尾花进行分类：
    1、获取数据
    2、划分数据集
    3、特征工程：标准化
    4、KNN算法预估器
    5、模型评估
    """
    # 1、获取数据 from sklearn.datasets import load_iris
    iris = load_iris()

    # 2、划分数据集 from sklearn.model_selection import train_test_split
    x_train, x_test, y_train, y_test = train_test_split(iris.data, iris.target, random_state=6)

    # 3、特征工程：标准化 from sklearn.preprocessing import StandardScaler
    transfer = StandardScaler()
    x_train = transfer.fit_transform(x_train)  # 对训练集进行标准化处理，并且用标准化后的数据来替代原始的训练集特征数据
    x_test = transfer.transform(x_test)  # 对测试集进行标准化处理，使用的是训练集的均值和标准差进行标准化，并且用标准化后的数据来替代原始的测试集特征数据
    # 为什么测试集没有fit操作呢？ 在对测试集进行标准化时，使用的是在训练集上计算得到的均值和标准差来进行标准化处理。这样做的目的是保持训练集和测试集的数据处理方式一致，

    # 4、KNN算法预估器 from sklearn.neighbors import KNeighborsClassifier
    estimator = KNeighborsClassifier(n_neighbors=3)  # 实例化一个估计器类
    """番外：加入网格搜索与交叉验证。若如此，则上面就不用设定n_neighbors值了。---------
    """
    param_dict = {"n_neighbors": [1, 3, 5, 7, 9, 11, 13, 21]}  # 参数准备
    estimator = GridSearchCV(estimator=estimator, param_grid=param_dict, cv=10)  # 调用GridSearchCV()
    """番外结束------------
    """
    estimator.fit(x_train,
                  y_train)  # 调用fit()方法。将训练集的特征数据 x_train 和对应的标签 y_train 作为参数传入，用于训练分类器。在这一步，分类器会根据训练集的数据学习特征之间的关系，并建立分类模型，以便后续用于对新的数据进行分类预测。
    # 这段代码执行后，estimator 对象已经被训练好了，可以用于对新的数据进行分类预测。但是，由于你没有提供测试集数据，我们无法得知模型在测试集上的表现。

    # 5、模型评估
    y_predict = estimator.predict(x_test)  # 这段代码使用训练好的分类器 estimator 对测试集数据 x_test 进行分类预测，并将预测结果保存在 y_predict 中。
    # ^
    # | 即：用train好的规则f，计算x_test对应的f(x_test)即y_predict，下一步比对y_predict和y_test即可。
    # 方法1：直接比对预测值和真实值
    print("y_predict: \n", y_predict)
    print("直接比对真实值（y_test）和预测值（y_predict）：\n", y_test == y_predict)
    # 方法2：计算准确率
    score = estimator.score(x_test,
                            y_test)  # score() 方法会将测试集的特征数据 x_test 输入到训练好的模型中进行预测，并与测试集的真实标签 y_test 进行比较，从而计算模型在测试集上的准确率。
    print("准确率为：\n", score)

    """番外：加入网格搜索与交叉验证。---------
    """
    # 最佳参数：best_params_
    print("最佳参数：\n", estimator.best_params_)
    # 最佳结果：best_score_
    print("最佳结果：\n", estimator.best_score_)
    # 最佳估计器：best_estimator_
    print("最佳估计器:\n", estimator.best_estimator_)
    # 交叉验证结果：cv_results_
    print("交叉验证结果:\n", estimator.cv_results_)
    """番外结束------------
    """
    return None


def nb_news():
    """
    用朴素贝叶斯算法对新闻进行分类
    :return:
    """
    # 1）获取数据
    news = fetch_20newsgroups(subset="all")

    # 2）划分数据集
    x_train, x_test, y_train, y_test = train_test_split(news.data, news.target)

    # 3）特征工程：文本特征抽取-tfidf
    transfer = TfidfVectorizer()
    x_train = transfer.fit_transform(x_train)
    x_test = transfer.transform(x_test)

    # 4）朴素贝叶斯算法预估器流程
    estimator = MultinomialNB()
    estimator.fit(x_train, y_train)

    # 5）模型评估
    # 方法1：直接比对真实值和预测值
    y_predict = estimator.predict(x_test)
    print("y_predict:\n", y_predict)
    print("直接比对真实值和预测值:\n", y_test == y_predict)

    # 方法2：计算准确率
    score = estimator.score(x_test, y_test)
    print("准确率为：\n", score)

    return None


def decision_iris():
    """
    用决策树对鸢尾花进行分类
    :return:
    """
    # 1）获取数据集
    iris = load_iris()

    # 2）划分数据集
    x_train, x_test, y_train, y_test = train_test_split(iris.data, iris.target, random_state=22)

    # 3）决策树预估器
    estimator = DecisionTreeClassifier(criterion="entropy")
    estimator.fit(x_train, y_train)

    # 4）模型评估
    # 方法1：直接比对真实值和预测值
    y_predict = estimator.predict(x_test)
    print("y_predict:\n", y_predict)
    print("直接比对真实值和预测值:\n", y_test == y_predict)

    # 方法2：计算准确率
    score = estimator.score(x_test, y_test)
    print("准确率为：\n", score)

    # 5-plus）可视化决策树
    export_graphviz(estimator, out_file="iris_tree.dot", feature_names=iris.feature_names)

    return None


if __name__ == "__main__":
    # 1-1：用knn算法对鸢尾花进行分类。ps:加入网格搜索与交叉验证
    # knn_iris()

    # 2-1 朴素贝叶斯
    # nb_news()

    # 3-1 决策树
    decision_iris()
