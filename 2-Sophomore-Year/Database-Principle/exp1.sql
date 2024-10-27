select fk.name,fk.object_id,OBJECT_NAME(fk.parent_object_id) as referenceTableName
from sys.foreign_keys as fk
join sys.objects as o on fk.referenced_object_id=o.object_id
where o.name='������Ϣ��'

ALTER TABLE dbo.ͼ�������ϸ�� DROP CONSTRAINT FK__ͼ�������ϸ��__����֤��__6AA5C795


--����������

drop table ������Ϣ�� --�Ѿɱ��ɾ��
go

CREATE TABLE ������Ϣ��(--�����±�
--������֤������Ϊ����Լ���������е��������Ͳ��ޣ������б�����Ψһ���ҷǿա�
	����֤��  varchar(50) primary key,
	����      varchar(10) ,
	�Ա�     varchar(2) ,
	��������  date,
	������    int ,
	������λ  varchar(50) ,
	�绰     varchar(50) ,
	[E-mail]    varchar(50)
)
GO

insert into ������Ϣ��--����в����µ��У������ݣ�
    values
	('29307142','����¶','Ů','1989-02-1', 2 ,'������Ϣϵ','85860126','zxl@163.com'),
	('36405216','����','��','1988-12-26', 1 ,'����ϵ','85860729','ly@sina.com.cn'),
	('28308208','����ȫ','��','1988-04-25', 1 ,'��������ϵ','85860618','wxq@yahoo.cn'),
	('16406236','�ż̸�','��','1989-08-18', 1 ,'�ֻ�����ϵ','85860913','zjg@163.com'),
	('16406247','��һ��','��','1981-12-30',' ','�ֻ�����ϵ','85860916','gyf@yahoo.cn')
go

select * from ������Ϣ��
go

drop table �軹��ϸ��
go

create table �軹��ϸ��(
    ����֤�� varchar(50),
	ͼ���� varchar(50),
	[��/��]  char(4),
	�������� date default (getdate()),
	�������� date,
	����     int,
	����     varchar(50),
	--Ϊ����֤�Ž�������Ϊrent_key����������ն�����Ϣ���еĽ���֤��
	constraint FK_����֤�� foreign key (����֤��) references ������Ϣ��(����֤��)
)
go

insert into �軹��ϸ��
       values
	   ('29307142','07108667','��','2008-03-28','2008-04-14',1,'002016'),
	   ('29307142','99011818','��','2008-04-27',NULL,1,'002016'),
	   ('36405216','07410802','��','2008-04-27',NULL,1,'002018'),
	   ('29307142','07410298','��','2008-04-28',NULL,1,'002018'),
	   ('36405216','00000746','��','2008-04-29','2008-05-09',1,'002016'),
	   ('28308208','07410139','��','2008-05-10',NULL,1,'002019'),
	   ('16406236','07410139','��','2008-05-11',NULL,1,'002017')
go

select * from �軹��ϸ��
go

drop table ͼ�����
go

create table ͼ�����(
--�ǿ�Լ��ֻ����һ�ִ�����ʽ
     ����    char(10) not null,
	 ͼ�����  char(10),
)
go

insert into ͼ�����
       values
	   ('H31','Ӣ��'),
	   ('I267','������Ʒ'),
	   ('TP312','��������'),
	   ('TP393','���������'),
	   ('U66','��������')
go

select * from ͼ�����
go

--�ڴ�����֮��Ա�����޸ģ���������Ӷ�����Լ��
alter table ͼ�����
     add constraint UQ_���� unique(����)
go

drop table ͼ�������ϸ��
go

create table ͼ�������ϸ��(
     ͼ����   varchar(50) ,
	 ͼ������   varchar(50),
	 --�ڴ������Ե�ʱ��Ϊ����������Լ��
	 ����֤��   varchar(50) foreign key references ������Ϣ��(����֤��),
	 �������   date,
	 �黹����   date,
	 �����     int,
)
go

insert into ͼ�������ϸ�� 
       values
	   ('99011818','�Ļ�����','29307142','2008-04-27',NULL,14),
	   ('07410802','����Ӣ��','36405216','2008-04-27',NULL,24),
	   ('07410298','C++�����������','29307142','2008-04-28',NULL,14),
	   ('07410139','�պ�����','28308208','2008-05-10',NULL,18),
	   ('07410139','�պ�����','16406236','2008-05-11',NULL,17)
go

select * from ͼ�������ϸ��
go

--alter table ͼ�������ϸ��
  -- add 
   --constraint DF_����� default (0) for �����,   --���Ĭ��Լ��������Ĭ��������0���ֶ��ǿ⺯��
  -- constraint PR_ͼ���� primary key (ͼ����)  --�������Լ������������������ͼ����  


drop table ������Ա
go

create table ������Ա(
     ����      varchar(25),
	 ����      varchar(10),
	 --�ڴ����Ա����Ե�ʱ��˳�������˼��Լ����Ĭ��Լ��
	 �Ա�      varchar(2) not null check(�Ա�='��' or �Ա�='Ů') default('��'),
	 ��������  date,
	 ��ϵ�绰  varchar(50),
	 [E-mail]  varchar(50)
)
go

insert into ������Ա
       values
	   ('002016','��ѧ��','��','1971-05-03','85860715','zxf@163.com'),
	   ('002017','������','Ů','1979-09-15','85860716','lj@163.com'),
	   ('002018','�˱�','��','1972-04-25','85860717','gb@yahoo.cn'),
	   ('002019','����','Ů','1968-11-03','85860718','cx@sina.com.cn')
go

select * from ������Ա
go


drop table ͼ����ϸ��
go

create table ͼ����ϸ��(
       ����     varchar(50),
	   ͼ����   varchar(50), 
	   ͼ������   varchar(50),
	   ����       varchar(10),
	   ������     varchar(50),
	   ����       float,
	   --��û����д�������ڣ����ǽ���
	   ��������   date default(getdate()),
	   ���뱾     int ,
	   ������     int,
	   �����     int,
	   constraint CK_ͼ������ check(���뱾>0 and ������>0)
)
go

insert into ͼ����ϸ�� 
       values
	   ('I267','99011818','�Ļ�����','������','֪ʶ������',16,'2000-03-19',8,15,14),
	   ('TP312','00000476','Delphi�߼�����ָ��','��ͼ','���ӹ�ҵ������',80,'2000-03-19',15,15,15),
	   ('U66','01058589','�����������','����','������ҵ������',19,'2001-07-15',20,20,20),
	   ('I267','07410139','�պ�����','����','�������ճ�����',19,'2007-04-12',15,20,18),
	   ('TP312','07410298','C++�������','��ӱ','���ϴ�ѧ������',38,'2007-05-08',10,15,14),
	   ('H31','07410802','����Ӣ��','�º�Ȩ','�人��ҵ��ѧ������',42,'2007-10-20',25,25,24),
	   ('H31','07108667','��ѧӢ��ѧϰ����','������','��������ѧ������',23.5,'2008-02-06',25,25,25),
	   ('TP393','07410810','���繤��ʵ�ý̳�','������','������ѧ������',34.8,'2008-08-21',10,15,15)
go

select * from ͼ����ϸ��
go


alter table ͼ����ϸ��
     add constraint CK_����� check(�����>=0)
go



--�鿴���б������Լ����C:checkԼ����D:Ĭ��Լ����F:���Լ����PK:����Լ����UQ:ΨһֵԼ��
select * from sys.objects where type in('C','D','F','PK','UQ') ; 
go

--�鿴�������е�Լ��
sp_helpconstraint @objname=ͼ����ϸ��
go


--ɾ��Լ��

alter table ͼ����ϸ�� drop constraint CK_�����
go

sp_helpconstraint @objname=ͼ����ϸ��
go



--��������
--create rule rule_name
--AS conditon_expression
create rule rule_score
as @score>=0 
go

--�󶨹���
---sp_bindrule 'rule','object_name' [,'futureonly_flag']
--ruleΪcreate������rule��object_name��ʾҪ�󶨹���ı���л������������
--futureonly_flag����ʾ����������󶨵�������������ʱ����ʹ��

sp_bindrule 'rule_score','ͼ����ϸ��.����'
go

--�������İ�
--sp_unbindrule 'object_name' 
sp_unbindrule 'ͼ����ϸ��.����'
go

--ɾ������
--drop rule RuleName
drop rule rule_score
go

--����Ĭ��
create default DF_����
as '����'
go
--��Ĭ��ֵ����
sp_bindefault 'DF_����','ͼ����ϸ��.����'
go
--ɾ����
sp_unbindefault 'ͼ����ϸ��.����'
go

--����ֶ�
alter table ������Ա
     add ������ varchar(50)
go

select * from ������Ա
go

--ɾ���ֶ�
alter table ������Ա
    drop column ������
go

select * from ������Ա
go

--�޸��ֶε���������
alter table ������Ա
     alter column �Ա� varchar(4)
go

--��ʾ�޸ĺ�ı���ֶ���Ϣ
sp_help @objname=������Ա
go

--�޸Ļ��ֶε���������
alter table ������Ա
     alter column �Ա� varchar(2)
go

sp_help @objname=������Ա
go


--�����������ڱ��д���������ʱ�򣬻��Զ����ɾۼ�����
create unique clustered index IX_ͼ���� on ͼ����ϸ��(ͼ����) 
go

create index  JX_����֤�� on ������Ϣ��(����֤��)
go

--SQL Server����������Ǵ������������Զ��Ż���ѯ ��
--�鿴���е�����
sp_helpindex @objname=ͼ����ϸ��
go

sp_helpindex @objname=������Ϣ��
go

--ɾ������,sql_server�Զ����ɵ���������û�а취��ɾ��
drop index ������Ϣ��.PK__������Ϣ��__0605635406062A32
go

drop index  IX_ͼ���� on ͼ����ϸ��
go 

drop index JX_����֤�� on ������Ϣ��
go

--������ͼ��ͼ��ļ۸����20
create view VIEW_ͼ��
as
select * from ͼ����ϸ�� where ����>20
go

--�鿴��ͼ
select * from VIEW_ͼ��
go

--ɾ����ͼ
drop view VIEW_ͼ��
go