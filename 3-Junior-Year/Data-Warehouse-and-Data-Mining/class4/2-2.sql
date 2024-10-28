USE studentdb; -- 切换到 studentdb 数据库
GO

SET NOCOUNT ON; -- 设置不返回受影响的行数
GO

/********** Begin **********/
--********** create score_view_cdept **********--

CREATE VIEW score_view_cdept AS
SELECT
    Student.sno,
    Student.name,
    Course.cname,
    Score.grade
FROM
    Student
    INNER JOIN Score ON Student.sno = Score.sno
    INNER JOIN Course ON Score.cno = Course.cno;

--********** create end **********/
/********** End **********/
GO
