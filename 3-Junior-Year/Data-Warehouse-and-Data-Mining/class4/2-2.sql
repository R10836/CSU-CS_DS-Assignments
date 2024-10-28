USE studentdb; -- �л��� studentdb ���ݿ�
GO

SET NOCOUNT ON; -- ���ò�������Ӱ�������
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
