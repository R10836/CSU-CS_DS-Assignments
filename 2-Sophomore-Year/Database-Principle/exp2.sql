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
	  sex       varchar(2)  default ('��'),
	  birthday  date default(getdate()),
	  class     varchar(20),
)
go

--��������
insert into Student
       values
	   ('108','����','��','1977-09-01','95033'),
	   ('105','����','��','1975-10-02','95031'),
	   ('107','����','Ů','1976-01-23','95033'),
	   ('101','���','��','1976-02-20','95033'),
	   ('109','����','Ů','1975-02-10','95031'),
	   ('103','½��','��','1974-06-03','95031')
go


select * from Student
go

drop table Teacher
go

create table Teacher(
      tno       varchar(20) primary key,
	  tname     varchar(10) not null,
	  sex       varchar(2)  default ('��'),
	  birthday  date default(getdate()),
	  prof      varchar(50),
	  depart    varchar(50)
)
go

insert into Teacher
      values
	  ('804','���','��','1958-12-02','������','�����ϵ'),
	  ('856','����','��','1969-03-12','��ʦ','���ӹ���ϵ'),
	  ('825','��Ƽ','Ů','1972-05-05','����','�����ϵ'),
	  ('831','����','Ů','1977-08-14','����','���ӹ���ϵ')
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
	  ('3-105','���������','825'),
	  ('3-245','����ϵͳ','804'),
	  ('6-166','���ֵ�·','856'),
	  ('9-888','�ߵ���ѧ','825')
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


--1���г�student�������м�¼��sname��sex��class�С�
select sname,sex,class  from student
go
--2����ʾ��ʦ���еĵ�λ�����ظ���depart�С�
select distinct depart from teacher 
go
--3����ʾѧ��������м�¼��
select * from student
go 
--4����ʾscore���гɼ���60��80֮������м�¼��
select * from score  
where degree between 60 and 80
go
--5����ʾscore���гɼ�Ϊ85��86��88�ļ�¼��
select * from score
where degree in (85,86,88)
go
--6����ʾstudent���С�95031������Ա�Ϊ��Ů����ͬѧ��¼��
select * from student 
where class = '95031' or sex = 'Ů'
go
--7����class������ʾstudent������м�¼��
select * from student
order by class desc
go
--8����cno����degree������ʾscore������м�¼��
select * from score
order by cno ,degree desc
go
--9����ʾ��95031�����ѧ��������
select class , count(sno) number  from student
group by class having class = '95031'
go
--10����ʾscore���е���߷ֵ�ѧ��ѧ�źͿγ̺š�
select sno,cno from score where degree=(select max(degree) from score)
go
--11����ʾ��3-105���ſγ̵�ƽ���֡�
select cno course,avg(degree) avg from score
group by cno having cno ='3-105'
go
--12����ʾscore����������5��ѧ��ѡ�޵Ĳ���3��ͷ�Ŀγ̺ŵ�ƽ��������
select cno course,avg(degree) avg from score
group by cno having(count(sno) > 4 and cno like '3%')
go
--13����ʾ��ͷִ���70����߷�С��90 ��sno�С�
select sno from score 
group by sno having (max(degree) < 90 and min(degree) > 70)
go
--14����ʾ����ѧ���� sname�� cno��degree�С�
select student.sname,cno,degree from student,Score
where Student.sno = Score.sno
go
--15����ʾ����ѧ���� sname�� cname��degree�С�
select sname,cname,degree from Student,Course,Score
where (Student.sno = Score.sno and Course.cno = Score.cno)
go
--16���г���95033������ѡ�γ̵�ƽ���֡�
select  cname course , avg(degree) as avg from Student,Course,Score
where (Student.sno = Score.sno and Course.cno = Score.cno and class = '95033')
group by cname
go
--17����ʾѡ�ޡ�3-105���γ̵ĳɼ����ڡ�109����ͬѧ�ɼ�������ͬѧ�ļ�¼��
select * from Student,Score 
where Student.sno = Score.sno and cno = '3-105'and degree > (
    select degree  from score where sno = '109' and cno ='3-105')
go
--18����ʾscore��ѡ�޶��ſγ̵�ͬѧ�з���Ϊ����߷ֳɼ��ļ�¼��
select sno from score 
where degree not in (
	select max(degree) from score group by cno)
	group by sno
	having count(cno) >= 2
--19����ʾ�ɼ�����ѧ��Ϊ��109�����γ̺�Ϊ��3-105���ĳɼ������м�¼��
select Score.sno,cno,degree from Student,Score 
      where Student.sno=Score.sno and cno = '3-105' 
	  and degree>(select degree from Score 
	  where cno='3-105' and sno = '109')
--20����ʾ����ѧ��Ϊ��108����ͬѧͬ�����������ѧ����sno��sname�� birthday�С�
select sno,sname,birthday from Student 
      where year(birthday) = (select year(birthday) from Student 
	  where sno = '108') 
--21����ʾ��������ʦ�οε�ѧ���ɼ���
select sname,cname,degree,tname 
      from Course,Score,Student,Teacher 
      where Student.sno = Score.sno and
            Score.cno = Course.cno and 
	        Course.tno=Teacher.tno and
	        Teacher.tname='����'

--22����ʾѡ��ĳ�γ̵�ͬѧ��������5�˵���ʦ������
select tname from Teacher
where Teacher.tno in
(select Course.tno from Score, Course
        where Score.cno = Course.cno
        group by Course.tno,Course.cno
        having count(*)>5)
go
--23����ʾ��95033����͡�95031����ȫ��ѧ���ļ�¼��
select * from Student where class in('95033','95031')
--24����ʾ������85�����ϳɼ��Ŀγ�cno��
select cno from Score where degree >85 group by cno
--25����ʾ�������ϵ����ʦ���̿γ̵ĳɼ���
select * from Score,Course,Teacher
      where Score.cno = Course.cno
	  and   Course.tno = Teacher.tno
	  and   Teacher.depart='�����ϵ'
--26����ʾ�������ϵ���͡����ӹ���ϵ����ְͬ�Ƶ���ʦ��tname��prof��
select tname,prof from Teacher 
       where depart = '�����ϵ' 
	   and prof not in
	   (select prof from Teacher
	   where depart = '���ӹ���ϵ')

select tname,prof from Teacher where prof not in(select prof from Teacher group by prof having count(*)>1)
--27����ʾѡ�ޱ��Ϊ��3-105���γ��ҳɼ����ٸ��ڡ�3-245���γ̵�ͬѧ��cno��sno��degree������degree�Ӹߵ��ʹ������С�
select cno,sno,degree from Score 
      where cno = '3-105' 
	  and degree>any
	  (select degree from Score 
	  where cno = '3-245' 
	  )
	  order by degree Desc
--28����ʾѡ�ޱ��Ϊ��3-105���γ��ҳɼ����ڡ�3-245���γ�����ͬѧ�ĳɼ���cno��sno��degree��
select cno,sno,degree from Score
      where cno = '3-105' 
	  and degree>all
	  (select degree from Score 
	  where cno = '3-245' 
	  and sno = sno
	  )
--29���г������ο���ʦ��tname��depart��
select tname,depart from Teacher where exists (select * from Course where Teacher.tno = Course.tno)

select tname,depart from Teacher where tno in (select tno from Course)
--30���г�����δ������ʦ��tname��depart��
select tname,depart from Teacher where not exists (select * from Course where Teacher.tno = Course.tno)

select tname,depart from Teacher where tno not in (select tno from Course)
--31���г�������ʦ��ͬѧ�� �������Ա�����ա�
select tname,sex,birthday  from teacher
  union 
 select sname,sex,birthday from student

--*32��������ѧ�γ̰���ѧ����103����ѧ�γ̵�ѧ��ѧ�š�
select distinct sno from Score,
(select cno from Score
where sno = 103
) as temp
where Score.cno = temp.cno
and Score.sno <> 103
go
--*33������ѡ�����пγ̵�ѧ��������
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
