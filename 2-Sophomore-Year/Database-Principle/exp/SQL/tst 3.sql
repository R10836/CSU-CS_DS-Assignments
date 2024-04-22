
--创建一个查询图书库存量的存储过程“cx_tskcl_proc”
--输出的内容包含类别号、图书编号、图书名称、库存数等数据内容。

drop procedure cx_tskcl_proc
go

create procedure cx_tskcl_proc  
as	
select * from 图书明细表
go

exec cx_tskcl_proc
go

--创建带参数的存储过程
drop procedure cx_图书_proc
go

create procedure cx_图书_proc @name varchar(50)
as
select * from 图书明细表 where 图书名称 = @name
go

exec  cx_图书_proc '航海英语'
go


--创建一个名为TS_CX_PROC的存储过程，它带有一个输入参数，用于接受图书编号，显示该图书的名称、作者、出版和复本数。

drop procedure TS_CX_PROC
go

create procedure TS_CX_PROC @book_no varchar(50)
as
select 图书名称,作者,出版社,副本数 from 图书明细表 where 图书编号 = @book_no
go

exec TS_CX_PROC '07410139';
go

--修改TS_CX_PROC存储过程，使之能按图书名称查询图书的相关信息。
--执行修改后的TS_CX_PROC存储过程，分别查询“航海英语”、“艺海潮音”等图书的信息。

alter procedure TS_CX_PROC @book_name varchar(50)
as
select 图书名称,作者,出版社,副本数 from 图书明细表 where 图书名称 = @book_name
go

exec TS_CX_PROC '航海英语'
go

exec  TS_CX_PROC '艺海潮音'
go

--删除存储过程

drop procedure TS_CX_PROC
go

--图书类别表上创建一个名为tslb_insert_trigger的触发器，当执行INSERT操作时，该触发器被触发，禁止插入记录。
create trigger tslb_insert_trigger on 图书类别 for insert
as 
print'禁止插入记录'
rollback transaction
go

insert into 图书类别
values
     ('hisad','wuli')
go

drop trigger tslb_insert_trigger

--在图书明细表上创建一个名为ts_delete_trigger的触发器，当执行DELETE操作时，该触发器被触发，禁止删除记录。

create trigger ts_delete_trigger on 图书明细表 for delete
as
print'禁止删除记录'
rollback transaction
go

delete from 图书明细表
where 类别号='U66'
go

drop trigger ts_delete_trigger

--在读者信息表上创建一个名为dzxx_insert_trigger的触发器，当在读者信息表中插入记录时，将该记录中的借书证号自动插入借还明细表中。
drop trigger dzxx_insert_trigger
go

create trigger dzxx_insert_trigger on 读者信息表 for insert
as
declare @no varchar(50)
select @no = 借书证号 from inserted
insert into 借还明细表(借书证号)
values(@no)
print'已经给借还明细表中添加了数据'
go

insert into 读者信息表
    values
	('12345678','茹湘原','男','2000-10-08', 1 ,'计算机系','87654321','rxy@163.com')

select *from 读者信息表
select *from 借还明细表

drop trigger dzxx_insert_trigger
 