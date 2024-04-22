USE hello;

-- 1. 建表 stud
CREATE TABLE stud (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255),
    phone_number VARCHAR(20)
);

-- 2. 插入数据
INSERT INTO stud (name, phone_number) VALUES
    ('张三', '1234567890'),
    ('李四', '9876543210'),
    ('王五', '1234567890'),
    ('赵六', '5555555555'),
    ('钱七', '1111111111'),
    ('孙八', '5555555555'),
    ('李九', '2222222222'),
    ('周十', '3333333333'),
    ('吴十一', '1234567890'),
    ('郑十二', '4444444444');

-- 3. 用 DISTINCT 查询 stud 表格中重复的电话号码，返回完整的记录
SELECT DISTINCT s1.*
FROM stud s1, stud s2
WHERE s1.id <> s2.id
    AND s1.phone_number = s2.phone_number;

-- 4. 如果两个人的电话号码重复，只保留其中任意一个人的记录，删除其他重复记录
DELETE s1
FROM stud s1, stud s2
WHERE s1.id > s2.id
    AND s1.phone_number = s2.phone_number;

-- 5. 查看修改后的表
SELECT * FROM stud;
