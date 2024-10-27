select fk.name,fk.object_id,OBJECT_NAME(fk.parent_object_id) as referenceTableName
from sys.foreign_keys as fk
join sys.objects as o on fk.referenced_object_id=o.object_id
where o.name='Student'

ALTER TABLE dbo.Score DROP CONSTRAINT FK__Score__sno__24134F1B


drop table Student
go

create table Student(
      sno       varchar(20) primary key,
	  sname     varchar(10) not null,
	  sex       varchar(2)  default ('男'),
	  birthday  date default(getdate()),
	  class     varchar(20),
)
go

--插入数据
insert into Student
       values
	   ('108','曾华','男','1977-09-01','95033'),
	   ('105','匡明','男','1975-10-02','95031'),
	   ('107','王丽','女','1976-01-23','95033'),
	   ('101','李军','男','1976-02-20','95033'),
	   ('109','王芳','女','1975-02-10','95031'),
	   ('103','陆军','男','1974-06-03','95031')
go


select * from Student
go

drop table Teacher
go

create table Teacher(
      tno       varchar(20) primary key,
	  tname     varchar(10) not null,
	  sex       varchar(2)  default ('男'),
	  birthday  date default(getdate()),
	  prof      varchar(50),
	  depart    varchar(50)
)
go

insert into Teacher
      values
	  ('804','李诚','男','1958-12-02','副教授','计算机系'),
	  ('856','张旭','男','1969-03-12','讲师','电子工程系'),
	  ('825','王萍','女','1972-05-05','助教','计算机系'),
	  ('831','刘冰','女','1977-08-14','助教','电子工程系')
go


select * from Teacher
go

drop table Course
go

create table Course(
      cno     varchar(20) primary key,
	  cname   varchar(50),
	  tno     varchar(20) foreign key references Teacher(tno)
	  )
go

insert into Course
      values
	  ('3-105','计算机导论','825'),
	  ('3-245','操作系统','804'),
	  ('6-166','数字电路','856'),
	  ('9-888','高等数学','825')
go

select * from Course
go

drop table Score
go

create table Score
	  (
	  sno       varchar(20) foreign key references Student(sno),
	  cno       varchar(20) foreign key references Course(cno),
	  degree    int,
	  primary key (sno,cno)
	  )
	  go

insert into Score
      values
	  ('103','3-245',86),
	  ('105','3-245',75),
	  ('109','3-245',68),
	  ('103','3-105',92),
	  ('105','3-105',88),
	  ('109','3-105',76),
	  ('101','3-105',64),
	  ('107','3-105',91),
	  ('108','3-105',78),
	  ('101','6-166',85),
	  ('107','6-166',79),
	  ('108','6-166',81)
go

select * from Score
go


--1、列出student表中所有记录的sname、sex和class列。
select sname,sex,class  from student
go
--2、显示教师所有的单位即不重复的depart列。
select distinct depart from teacher 
go
--3、显示学生表的所有记录。
select * from student
go 
--4、显示score表中成绩在60到80之间的所有记录。
select * from score  
where degree between 60 and 80
go
--5、显示score表中成绩为85，86或88的记录。
select * from score
where degree in (85,86,88)
go
--6、显示student表中“95031”班或性别为“女”的同学记录。
select * from student 
where class = '95031' or sex = '女'
go
--7、以class降序显示student表的所有记录。
select * from student
order by class desc
go
--8、以cno升序、degree降序显示score表的所有记录。
select * from score
order by cno ,degree desc
go
--9、显示“95031”班的学生人数。
select class , count(sno) number  from student
group by class having class = '95031'
go
--10、显示score表中的最高分的学生学号和课程号。
select sno,cno from score where degree=(select max(degree) from score)
go
--11、显示“3-105”号课程的平均分。
select cno course,avg(degree) avg from score
group by cno having cno ='3-105'
go
--12、显示score表中至少有5名学生选修的并以3开头的课程号的平均分数。
select cno course,avg(degree) avg from score
group by cno having(count(sno) > 4 and cno like '3%')
go
--13、显示最低分大于70，最高分小于90 的sno列。
select sno from score 
group by sno having (max(degree) < 90 and min(degree) > 70)
go
--14、显示所有学生的 sname、 cno和degree列。
select student.sname,cno,degree from student,Score
where Student.sno = Score.sno
go
--15、显示所有学生的 sname、 cname和degree列。
select sname,cname,degree from Student,Course,Score
where (Student.sno = Score.sno and Course.cno = Score.cno)
go
--16、列出“95033”班所选课程的平均分。
select  cname course , avg(degree) as avg from Student,Course,Score
where (Student.sno = Score.sno and Course.cno = Score.cno and class = '95033')
group by cname
go
--17、显示选修“3-105”课程的成绩高于“109”号同学成绩的所有同学的记录。
select * from Student,Score 
where Student.sno = Score.sno and cno = '3-105'and degree > (
    select degree  from score where sno = '109' and cno ='3-105')
go
--18、显示score中选修多门课程的同学中分数为非最高分成绩的记录。
select sno from score 
where degree not in (
	select max(degree) from score group by cno)
	group by sno
	having count(cno) >= 2
--19、显示成绩高于学号为“109”、课程号为“3-105”的成绩的所有记录。
select Score.sno,cno,degree from Student,Score 
      where Student.sno=Score.sno and cno = '3-105' 
	  and degree>(select degree from Score 
	  where cno='3-105' and sno = '109')
--20、显示出和学号为“108”的同学同年出生的所有学生的sno、sname和 birthday列。
select sno,sname,birthday from Student 
      where year(birthday) = (select year(birthday) from Student 
	  where sno = '108') 
--21、显示“张旭”老师任课的学生成绩。
select sname,cname,degree,tname 
      from Course,Score,Student,Teacher 
      where Student.sno = Score.sno and
            Score.cno = Course.cno and 
	        Course.tno=Teacher.tno and
	        Teacher.tname='张旭'

--22、显示选修某课程的同学人数多于5人的老师姓名。
select tname from Teacher
where Teacher.tno in
(select Course.tno from Score, Course
        where Score.cno = Course.cno
        group by Course.tno,Course.cno
        having count(*)>5)
go
--23、显示“95033”班和“95031”班全体学生的记录。
select * from Student where class in('95033','95031')
--24、显示存在有85分以上成绩的课程cno。
select cno from Score where degree >85 group by cno
--25、显示“计算机系”老师所教课程的成绩表。
select * from Score,Course,Teacher
      where Score.cno = Course.cno
	  and   Course.tno = Teacher.tno
	  and   Teacher.depart='计算机系'
--26、显示“计算机系”和“电子工程系”不同职称的老师的tname和prof。
select tname,prof from Teacher 
       where depart = '计算机系' 
	   and prof not in
	   (select prof from Teacher
	   where depart = '电子工程系')

select tname,prof from Teacher where prof not in(select prof from Teacher group by prof having count(*)>1)
--27、显示选修编号为“3-105”课程且成绩至少高于“3-245”课程的同学的cno、sno和degree，并按degree从高到低次序排列。
select cno,sno,degree from Score 
      where cno = '3-105' 
	  and degree>any
	  (select degree from Score 
	  where cno = '3-245' 
	  )
	  order by degree Desc
--28、显示选修编号为“3-105”课程且成绩高于“3-245”课程所有同学的成绩的cno、sno和degree。
select cno,sno,degree from Score
      where cno = '3-105' 
	  and degree>all
	  (select degree from Score 
	  where cno = '3-245' 
	  and sno = sno
	  )
--29、列出所有任课老师的tname和depart。
select tname,depart from Teacher where exists (select * from Course where Teacher.tno = Course.tno)

select tname,depart from Teacher where tno in (select tno from Course)
--30、列出所有未讲课老师的tname和depart。
select tname,depart from Teacher where not exists (select * from Course where Teacher.tno = Course.tno)

select tname,depart from Teacher where tno not in (select tno from Course)
--31、列出所有老师和同学的 姓名、性别和生日。
select tname,sex,birthday  from teacher
  union 
 select sname,sex,birthday from student

--*32、检索所学课程包含学生“103”所学课程的学生学号。
select distinct sno from Score,
(select cno from Score
where sno = 103
) as temp
where Score.cno = temp.cno
and Score.sno <> 103
go
--*33、检索选修所有课程的学生姓名。
select student.sname from student where not exists     (select *  from  Course 
     where not exists 
          ( select * from  score where
      student.sno=score.sno and course.cno=score.cno))

select sname from Student
where sno in 
(
select sno from Score
group by sno
having count(*)>(select count(*) from Course)
)
