select fk.name,fk.object_id,OBJECT_NAME(fk.parent_object_id) as referenceTableName
from sys.foreign_keys as fk
join sys.objects as o on fk.referenced_object_id=o.object_id
where o.name='读者信息表'

ALTER TABLE dbo.图书借阅明细表 DROP CONSTRAINT FK__图书借阅明细表__借书证号__6AA5C795


--创建六个表

drop table 读者信息表 --把旧表给删了
go

CREATE TABLE 读者信息表(--创建新表
--将借书证号设置为主键约束，主键列的数据类型不限，但此列必须是唯一并且非空。
	借书证号  varchar(50) primary key,
	姓名      varchar(10) ,
	性别     varchar(2) ,
	出生日期  date,
	借书量    int ,
	工作单位  varchar(50) ,
	电话     varchar(50) ,
	[E-mail]    varchar(50)
)
GO

insert into 读者信息表--向表中插入新的行（其内容）
    values
	('29307142','张晓露','女','1989-02-1', 2 ,'管理信息系','85860126','zxl@163.com'),
	('36405216','李阳','男','1988-12-26', 1 ,'航海系','85860729','ly@sina.com.cn'),
	('28308208','王新全','男','1988-04-25', 1 ,'人文艺术系','85860618','wxq@yahoo.cn'),
	('16406236','张继刚','男','1989-08-18', 1 ,'轮机工程系','85860913','zjg@163.com'),
	('16406247','顾一帆','男','1981-12-30',' ','轮机工程系','85860916','gyf@yahoo.cn')
go

select * from 读者信息表
go

drop table 借还明细表
go

create table 借还明细表(
    借书证号 varchar(50),
	图书编号 varchar(50),
	[借/还]  char(4),
	借书日期 date default (getdate()),
	还书日期 date,
	数量     int,
	工号     varchar(50),
	--为借书证号建立名字为rent_key的外键，参照读者信息表中的借书证号
	constraint FK_借书证号 foreign key (借书证号) references 读者信息表(借书证号)
)
go

insert into 借还明细表
       values
	   ('29307142','07108667','还','2008-03-28','2008-04-14',1,'002016'),
	   ('29307142','99011818','借','2008-04-27',NULL,1,'002016'),
	   ('36405216','07410802','借','2008-04-27',NULL,1,'002018'),
	   ('29307142','07410298','借','2008-04-28',NULL,1,'002018'),
	   ('36405216','00000746','还','2008-04-29','2008-05-09',1,'002016'),
	   ('28308208','07410139','借','2008-05-10',NULL,1,'002019'),
	   ('16406236','07410139','借','2008-05-11',NULL,1,'002017')
go

select * from 借还明细表
go

drop table 图书类别
go

create table 图书类别(
--非空约束只有这一种创建方式
     类别号    char(10) not null,
	 图书类别  char(10),
)
go

insert into 图书类别
       values
	   ('H31','英语'),
	   ('I267','当代作品'),
	   ('TP312','程序语言'),
	   ('TP393','计算机网络'),
	   ('U66','船舶工程')
go

select * from 图书类别
go

--在创建表之外对表进行修改，给类别号添加独立性约束
alter table 图书类别
     add constraint UQ_类别号 unique(类别号)
go

drop table 图书借阅明细表
go

create table 图书借阅明细表(
     图书编号   varchar(50) ,
	 图书名称   varchar(50),
	 --在创建属性的时候为属性添加外键约束
	 借书证号   varchar(50) foreign key references 读者信息表(借书证号),
	 借出日期   date,
	 归还日期   date,
	 库存数     int,
)
go

insert into 图书借阅明细表 
       values
	   ('99011818','文化苦旅','29307142','2008-04-27',NULL,14),
	   ('07410802','航海英语','36405216','2008-04-27',NULL,24),
	   ('07410298','C++程序设计语言','29307142','2008-04-28',NULL,14),
	   ('07410139','艺海潮音','28308208','2008-05-10',NULL,18),
	   ('07410139','艺海潮音','16406236','2008-05-11',NULL,17)
go

select * from 图书借阅明细表
go

--alter table 图书借阅明细表
  -- add 
   --constraint DF_库存数 default (0) for 库存数,   --添加默认约束，这里默认内容是0，字段是库函数
  -- constraint PR_图书编号 primary key (图书编号)  --添加主键约束，所以这里主键是图书编号  


drop table 工作人员
go

create table 工作人员(
     工号      varchar(25),
	 姓名      varchar(10),
	 --在创建性别属性的时候顺带建立了检查约束和默认约束
	 性别      varchar(2) not null check(性别='男' or 性别='女') default('男'),
	 出生日期  date,
	 联系电话  varchar(50),
	 [E-mail]  varchar(50)
)
go

insert into 工作人员
       values
	   ('002016','周学飞','男','1971-05-03','85860715','zxf@163.com'),
	   ('002017','李晓静','女','1979-09-15','85860716','lj@163.com'),
	   ('002018','顾彬','男','1972-04-25','85860717','gb@yahoo.cn'),
	   ('002019','陈欣','女','1968-11-03','85860718','cx@sina.com.cn')
go

select * from 工作人员
go


drop table 图书明细表
go

create table 图书明细表(
       类别号     varchar(50),
	   图书编号   varchar(50), 
	   图书名称   varchar(50),
	   作者       varchar(10),
	   出版社     varchar(50),
	   定价       float,
	   --若没有填写购进日期，就是今天
	   购进日期   date default(getdate()),
	   购入本     int ,
	   副本数     int,
	   库存数     int,
	   constraint CK_图书名称 check(购入本>0 and 副本数>0)
)
go

insert into 图书明细表 
       values
	   ('I267','99011818','文化苦旅','余秋雨','知识出版社',16,'2000-03-19',8,15,14),
	   ('TP312','00000476','Delphi高级开发指南','坎图','电子工业出版社',80,'2000-03-19',15,15,15),
	   ('U66','01058589','船舶制造基础','杨敏','国防工业出版社',19,'2001-07-15',20,20,20),
	   ('I267','07410139','艺海潮音','李叔','江苏文艺出版社',19,'2007-04-12',15,20,18),
	   ('TP312','07410298','C++程序设计','成颖','东南大学出版社',38,'2007-05-08',10,15,14),
	   ('H31','07410802','航海英语','陈宏权','武汉工业大学出版社',42,'2007-10-20',25,25,24),
	   ('H31','07108667','大学英语学习辅导','姜丽蓉','北京理工大学出版社',23.5,'2008-02-06',25,25,25),
	   ('TP393','07410810','网络工程实用教程','汪新民','北京大学出版社',34.8,'2008-08-21',10,15,15)
go

select * from 图书明细表
go


alter table 图书明细表
     add constraint CK_库存数 check(库存数>=0)
go



--查看所有表的所有约束。C:check约束。D:默认约束。F:外键约束。PK:主键约束。UQ:唯一值约束
select * from sys.objects where type in('C','D','F','PK','UQ') ; 
go

--查看单个表中的约束
sp_helpconstraint @objname=图书明细表
go


--删除约束

alter table 图书明细表 drop constraint CK_库存数
go

sp_helpconstraint @objname=图书明细表
go



--建立规则
--create rule rule_name
--AS conditon_expression
create rule rule_score
as @score>=0 
go

--绑定规则
---sp_bindrule 'rule','object_name' [,'futureonly_flag']
--rule为create创建的rule，object_name表示要绑定规则的表或列或别名数据类型
--futureonly_flag：表示仅当将规则绑定到别名数据类型时才能使用

sp_bindrule 'rule_score','图书明细表.定价'
go

--解除规则的绑定
--sp_unbindrule 'object_name' 
sp_unbindrule '图书明细表.定价'
go

--删除规则
--drop rule RuleName
drop rule rule_score
go

--创建默认
create default DF_作者
as '佚名'
go
--绑定默认值对象
sp_bindefault 'DF_作者','图书明细表.作者'
go
--删除绑定
sp_unbindefault '图书明细表.作者'
go

--添加字段
alter table 工作人员
     add 家属名 varchar(50)
go

select * from 工作人员
go

--删除字段
alter table 工作人员
    drop column 家属名
go

select * from 工作人员
go

--修改字段的数据类型
alter table 工作人员
     alter column 性别 varchar(4)
go

--显示修改后的表的字段信息
sp_help @objname=工作人员
go

--修改回字段的数据类型
alter table 工作人员
     alter column 性别 varchar(2)
go

sp_help @objname=工作人员
go


--创建索引，在表中创建主键的时候，会自动生成聚集索引
create unique clustered index IX_图书编号 on 图书明细表(图书编号) 
go

create index  JX_借书证号 on 读者信息表(借书证号)
go

--SQL Server将会根据我们创建的索引，自动优化查询 。
--查看表中的索引
sp_helpindex @objname=图书明细表
go

sp_helpindex @objname=读者信息表
go

--删除索引,sql_server自动生成的主键索引没有办法被删除
drop index 读者信息表.PK__读者信息表__0605635406062A32
go

drop index  IX_图书编号 on 图书明细表
go 

drop index JX_借书证号 on 读者信息表
go

--创建视图，图书的价格大于20
create view VIEW_图书
as
select * from 图书明细表 where 定价>20
go

--查看视图
select * from VIEW_图书
go

--删除视图
drop view VIEW_图书
go