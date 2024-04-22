from sklearn.ensemble import RandomForestClassifier


def digit_predict(train_image, train_label, test_image):
    """
    实现功能：训练模型并输出预测结果
    :param train_image: 包含多条训练样本的样本集，类型为ndarray, shape为[-1, 8, 8]
    :param train_label: 包含多条训练样本标签的标签集，类型为ndarray
    :param test_image: 包含多条测试样本的测试集，类型为ndarray
    :return: test_image对应的预测标签，类型为ndarray
    """

    # 将训练样本集变形为二维数组
    train_data = train_image.reshape((train_image.shape[0], -1))

    # 创建随机森林分类器，增加树的数量
    clf = RandomForestClassifier(n_estimators=100)

    # 训练模型
    clf.fit(train_data, train_label)

    # 将测试样本集变形为二维数组
    test_data = test_image.reshape((test_image.shape[0], -1))

    # 预测结果
    predictions = clf.predict(test_data)

    return predictions
