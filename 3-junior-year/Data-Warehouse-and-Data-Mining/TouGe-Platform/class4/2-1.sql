USE studentdb
go

SET NOCOUNT ON
go
/********** Begin **********/
--********** create begin **********--

CREATE TABLE Student (
    sno VARCHAR(50),
    name VARCHAR(50),
    sex VARCHAR(10),
    birthday DATE,
    discipline VARCHAR(50),
    school VARCHAR(100),
);

CREATE TABLE Course (
    cno VARCHAR(50),
    cname VARCHAR(50),
    description VARCHAR(256),
    credit FLOAT,
    cinstitution VARCHAR(128)
);

CREATE TABLE Score (
    sno VARCHAR(50),
    cno VARCHAR(50),
    grade FLOAT
);

--********** create end **********--
go
select name, length, COLLATION from syscolumns where id=object_Id('student')
go
select name, length, COLLATION from syscolumns where id=object_Id('course')
go
select name, length, COLLATION from syscolumns where id=object_Id('score')
go

--********** insert begin **********--

INSERT INTO Score (sno, cno, grade)
VALUES
    ('09011101', '101', 89),
    ('09011101', '102', 78);

--********** insert end **********--
select * from  score
go


--********** alt student table **********--

ALTER TABLE Student
ADD addr VARCHAR(256);

--********** alt end **********--
go

select name, length, COLLATION from syscolumns where id=object_Id('student')
go

--********** del score table **********--

DROP TABLE Score;

--********** del end **********--
/********** End **********/
go

GO
IF NOT EXISTS(Select 1 From Sysobjects Where Name='score')  --查询表是否存在
BEGIN
PRINT 'NOT EXISTS TABLE score'
END
GO