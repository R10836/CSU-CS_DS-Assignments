import numpy as np
import pandas as pd
from sklearn.utils.multiclass import type_of_target
import tree_plottter
import pruning
import matplotlib as plt

plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False


class Node(object):  # 节点类
    def __init__(self):  # 初始化
        self.feature_name = None  # 特征名
        self.feature_index = None  # 特征索引
        self.subtree = {}
        self.impurity = None  # 不纯度
        self.is_continuous = False  # 是否是连续值
        self.split_value = None  # 划分值
        self.is_leaf = False  # 是否是叶节点
        self.leaf_class = None  # 叶节点类别
        self.leaf_num = None  # 叶节点个数
        self.high = -1  # 树的高度


class DecisionTree(object):  # 决策树类
    """
    没有针对缺失值的情况作处理。
    """

    def __init__(self, criterion='gini', pruning=None):  # 初始化
        """

        :param criterion: 划分方法选择，'gini', 'infogain', 'gainratio', 三种选项
        :param pruning:   是否剪枝 'pre_pruning' 'post_pruning'
        """
        self.columns = None
        assert criterion in ('gini', 'infogain', 'gainratio')  # 断言
        assert pruning in (None, 'pre_pruning', 'post_pruning')  # 断言
        self.criterion = criterion  # 划分方法
        self.pruning = pruning  # 剪枝方法

    def fit(self, X_train, y_train, X_val=None, y_val=None):  # 拟合
        """
        生成决策树
        -------
        :param X:  只支持DataFrame类型数据，因为DataFrame中已有列名，省去一个列名的参数。不支持np.array等其他数据类型
        :param y:
        :return:
        """

        if self.pruning is not None and (X_val is None or y_val is None):  # 如果剪枝不为空，但是验证集为空
            raise Exception('you must input X_val and y_val if you are going to pruning')  # 抛出异常

        X_train.reset_index(inplace=True, drop=True)  # 重置索引
        y_train.reset_index(inplace=True, drop=True)  # 重置索引

        if X_val is not None:  # 如果验证集不为空
            X_val.reset_index(inplace=True, drop=True)  # 重置索引
            y_val.reset_index(inplace=True, drop=True)  # 重置索引

        self.columns = list(X_train.columns)  # 包括原数据的列名
        self.tree_ = self.generate_tree(X_train, y_train)  # 生成决策树

        if self.pruning == 'pre_pruning':  # 如果是预剪枝
            pruning.pre_pruning(X_train, y_train, X_val, y_val, self.tree_)  #
        elif self.pruning == 'post_pruning':  # 如果是后剪枝
            pruning.post_pruning(X_train, y_train, X_val, y_val, self.tree_)

        return self

    def generate_tree(self, X, y):  # 生成决策树
        my_tree = Node()  # 节点类
        my_tree.leaf_num = 0  # 叶节点个数
        if y.nunique() == 1:  # 属于同一类别
            my_tree.is_leaf = True  # 是叶节点
            my_tree.leaf_class = y.values[0]  # 叶节点类别
            my_tree.high = 0  # 高度
            my_tree.leaf_num += 1  # 叶节点个数
            return my_tree  # 返回节点类

        if X.empty:  # 特征用完了，数据为空，返回样本数最多的类
            my_tree.is_leaf = True  # 是叶节点
            my_tree.leaf_class = pd.value_counts(y).index[0]  # 叶节点类别
            my_tree.high = 0  # 高度
            my_tree.leaf_num += 1  # 叶节点个数
            return my_tree  # 返回节点类

        best_feature_name, best_impurity = self.choose_best_feature_to_split(X, y)  # 选择最佳特征

        my_tree.feature_name = best_feature_name  # 特征名
        my_tree.impurity = best_impurity[0]  # 不纯度
        my_tree.feature_index = self.columns.index(best_feature_name)  # 特征索引

        feature_values = X.loc[:, best_feature_name]  # 特征值

        if len(best_impurity) == 1:  # 离散值
            my_tree.is_continuous = False

            unique_vals = pd.unique(feature_values)  # 特征值去重
            sub_X = X.drop(best_feature_name, axis=1)

            max_high = -1
            for value in unique_vals:  # 对于每一个特征值
                my_tree.subtree[value] = self.generate_tree(sub_X[feature_values == value],
                                                            y[feature_values == value])  # 生成子树
                if my_tree.subtree[value].high > max_high:  # 记录子树下最高的高度
                    max_high = my_tree.subtree[value].high  # 最高高度
                my_tree.leaf_num += my_tree.subtree[value].leaf_num  # 叶节点个数

            my_tree.high = max_high + 1  # 高度

        elif len(best_impurity) == 2:  # 连续值
            my_tree.is_continuous = True  # 是连续值
            my_tree.split_value = best_impurity[1]
            up_part = '>= {:.3f}'.format(my_tree.split_value)
            down_part = '< {:.3f}'.format(my_tree.split_value)

            my_tree.subtree[up_part] = self.generate_tree(X[feature_values >= my_tree.split_value],
                                                          y[feature_values >= my_tree.split_value])
            my_tree.subtree[down_part] = self.generate_tree(X[feature_values < my_tree.split_value],
                                                            y[feature_values < my_tree.split_value])

            my_tree.leaf_num += (my_tree.subtree[up_part].leaf_num + my_tree.subtree[down_part].leaf_num)

            my_tree.high = max(my_tree.subtree[up_part].high, my_tree.subtree[down_part].high) + 1

        return my_tree

    def predict(self, X):  # 预测
        """
        同样只支持 pd.DataFrame类型数据
        :param X:  pd.DataFrame 类型
        :return:
        """
        if not hasattr(self, "tree_"):  # 如果没有属性
            raise Exception('you have to fit first before predict.')  # 抛出异常
        if X.ndim == 1:  # 如果维度为1
            return self.predict_single(X)  # 预测单一样本
        else:
            return X.apply(self.predict_single, axis=1)  # 预测多个样本

    def predict_single(self, x, subtree=None):  # 预测单一样本
        """
        预测单一样本。
        :param x:
        :param subtree: 根据特征，往下递进的子树。
        :return:
        """
        if subtree is None:  # 如果子树为空
            subtree = self.tree_  # 子树为整个树

        if subtree.is_leaf:  # 如果是叶节点
            return subtree.leaf_class  # 返回叶节点类别

        if subtree.is_continuous:  # 若是连续值，需要判断是
            if x[subtree.feature_index] >= subtree.split_value:
                return self.predict_single(x, subtree.subtree['>= {:.3f}'.format(subtree.split_value)])
            else:
                return self.predict_single(x, subtree.subtree['< {:.3f}'.format(subtree.split_value)])
        else:
            return self.predict_single(x, subtree.subtree[x[subtree.feature_index]])

    def choose_best_feature_to_split(self, X, y):  # 选择最佳特征
        assert self.criterion in ('gini', 'infogain', 'gainratio')  # 断言

        if self.criterion == 'gini':  # 如果是gini
            return self.choose_best_feature_gini(X, y)

    def choose_best_feature_gini(self, X, y):  # 选择最佳特征gini
        features = X.columns  # 特征名
        best_feature_name = None  # 最佳特征名
        best_gini = [float('inf')]  # 最佳gini
        for feature_name in features:  # 对于每一个特征#
            is_continuous = type_of_target(X[feature_name]) == 'continuous'  # 判断是否为连续值
            gini_idex = self.gini_index(X[feature_name], y, is_continuous)  # 计算gini指数
            if gini_idex[0] < best_gini[0]:  # 如果gini指数小于最佳gini
                best_feature_name = feature_name  # 最佳特征名为当前特征名
                best_gini = gini_idex  # 最佳gini为当前gini

        return best_feature_name, best_gini

    def gini_index(self, feature, y, is_continuous=False):  # 计算基尼指数
        """
        计算基尼指数， 对于连续值，选择基尼系统最小的点，作为分割点
        -------
        :param feature:
        :param y:
        :return:
        """
        m = y.shape[0]
        unique_value = pd.unique(feature)  # 特征值
        if is_continuous:
            unique_value.sort()  # 排序, 用于建立分割点
            # 这里其实也可以直接用feature值作为分割点，但这样会出现空集， 所以还是按照书中4.7式建立分割点。好处是不会出现空集
            split_point_set = [(unique_value[i] + unique_value[i + 1]) / 2 for i in range(len(unique_value) - 1)]

            min_gini = float('inf')
            min_gini_point = None
            for split_point_ in split_point_set:  # 遍历所有的分割点，寻找基尼指数最小的分割点
                Dv1 = y[feature <= split_point_]
                Dv2 = y[feature > split_point_]
                gini_index = Dv1.shape[0] / m * self.gini(Dv1) + Dv2.shape[0] / m * self.gini(Dv2)

                if gini_index < min_gini:
                    min_gini = gini_index
                    min_gini_point = split_point_
            return [min_gini, min_gini_point]
        else:
            gini_index = 0
            for value in unique_value:
                Dv = y[feature == value]
                m_dv = Dv.shape[0]
                gini = self.gini(Dv)  # 原书4.5式
                gini_index += m_dv / m * gini  # 4.6式

            return [gini_index]

    def gini(self, y):
        p = pd.value_counts(y) / y.shape[0]
        gini = 1 - np.sum(p ** 2)
        return gini


if __name__ == '__main__':
    data_path2 = r'D:\JueCeShu\watermelon.txt'
    data = pd.read_table(data_path2, encoding='gbk', delimiter=',', index_col=0)

    train = [1, 2, 3, 6, 7, 10, 14, 15, 16, 17]
    train = [i - 1 for i in train]
    X = data.iloc[train, :6]
    y = data.iloc[train, 6]

    test = [4, 5, 8, 9, 11, 12, 13]
    test = [i - 1 for i in test]

    X_val = data.iloc[test, :6]
    y_val = data.iloc[test, 6]

    tree = DecisionTree('gini', 'pre_pruning')
    tree.fit(X, y, X_val, y_val)

    print(np.mean(tree.predict(X_val) == y_val))
    tree_plottter.create_plot(tree.tree_)