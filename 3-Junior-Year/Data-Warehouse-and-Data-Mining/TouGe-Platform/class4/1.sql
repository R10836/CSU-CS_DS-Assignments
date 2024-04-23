/********** Begin **********/
--********** create student database **********/
CREATE DATABASE student
ON
PRIMARY (
    NAME = N'studentdata1',
    FILENAME = N'/home/studentdata1.mdf',
    SIZE = 5MB,
    MAXSIZE = 10MB,
    FILEGROWTH = 1MB
),
FILEGROUP student_data (
    NAME = N'studentdata2',
    FILENAME = N'/home/studentdata2.ndf',
    SIZE = 5MB,
    MAXSIZE = 10MB,
    FILEGROWTH = 1MB
)
LOG ON
(
    NAME = N'studentlog1',
    FILENAME = N'/home/studentlog1.ldf',
    SIZE = 5MB,
    MAXSIZE = 10MB,
    FILEGROWTH = 1MB
);
--********** create end **********
GO

--********** add database file **********
ALTER DATABASE student
ADD FILE (
    NAME = N'studentdata3',
    FILENAME = N'/home/studentdata3.ndf',
    SIZE = 6MB,
    MAXSIZE = 20MB,
    FILEGROWTH = 1MB
)
TO FILEGROUP student_data;
--********** add file end **********
GO

--********** add database log file **********
ALTER DATABASE student
ADD LOG FILE (
    NAME = N'studentlog2',
    FILENAME = N'/home/Cstudentlog2.ldf',
    SIZE = 6MB,
    MAXSIZE = 20MB,
    FILEGROWTH = 1MB
);
--********** add log file end **********
GO

--********** alter database file **********
ALTER DATABASE student
MODIFY FILE (
    NAME = N'studentdata3',
    SIZE = 8MB,
    MAXSIZE = 30MB
);
--********** alter end **********
GO
/********** End **********/
