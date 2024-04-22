from sklearn.ensemble import RandomForestClassifier


def data_classification(train_data, train_label, test_data):
    """
    使用随机森林对训练集数据进行训练，并对测试集数据进行预测，并返回预测结果
    :param train_data: 训练集数据，类型为ndarray
    :param train_label: 训练集标签，类型为ndarray
    :param test_data: 测试集数据，类型为ndarray
    :return: 分类结果
    """
    # 使用随机森林分类器
    clf = RandomForestClassifier()

    # 对训练集数据进行训练
    clf.fit(train_data, train_label)

    # 对测试集数据进行预测
    predictions = clf.predict(test_data)

    return predictions
