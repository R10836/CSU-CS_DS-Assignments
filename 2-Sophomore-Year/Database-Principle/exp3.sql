
--����һ����ѯͼ�������Ĵ洢���̡�cx_tskcl_proc��
--��������ݰ������š�ͼ���š�ͼ�����ơ���������������ݡ�

drop procedure cx_tskcl_proc
go

create procedure cx_tskcl_proc  
as	
select * from ͼ����ϸ��
go

exec cx_tskcl_proc
go

--�����������Ĵ洢����
drop procedure cx_ͼ��_proc
go

create procedure cx_ͼ��_proc @name varchar(50)
as
select * from ͼ����ϸ�� where ͼ������ = @name
go

exec  cx_ͼ��_proc '����Ӣ��'
go


--����һ����ΪTS_CX_PROC�Ĵ洢���̣�������һ��������������ڽ���ͼ���ţ���ʾ��ͼ������ơ����ߡ�����͸�������

drop procedure TS_CX_PROC
go

create procedure TS_CX_PROC @book_no varchar(50)
as
select ͼ������,����,������,������ from ͼ����ϸ�� where ͼ���� = @book_no
go

exec TS_CX_PROC '07410139';
go

--�޸�TS_CX_PROC�洢���̣�ʹ֮�ܰ�ͼ�����Ʋ�ѯͼ��������Ϣ��
--ִ���޸ĺ��TS_CX_PROC�洢���̣��ֱ��ѯ������Ӣ������պ���������ͼ�����Ϣ��

alter procedure TS_CX_PROC @book_name varchar(50)
as
select ͼ������,����,������,������ from ͼ����ϸ�� where ͼ������ = @book_name
go

exec TS_CX_PROC '����Ӣ��'
go

exec  TS_CX_PROC '�պ�����'
go

--ɾ���洢����

drop procedure TS_CX_PROC
go

--ͼ�������ϴ���һ����Ϊtslb_insert_trigger�Ĵ���������ִ��INSERT����ʱ���ô���������������ֹ�����¼��
create trigger tslb_insert_trigger on ͼ����� for insert
as 
print'��ֹ�����¼'
rollback transaction
go

insert into ͼ�����
values
     ('hisad','wuli')
go

drop trigger tslb_insert_trigger

--��ͼ����ϸ���ϴ���һ����Ϊts_delete_trigger�Ĵ���������ִ��DELETE����ʱ���ô���������������ֹɾ����¼��

create trigger ts_delete_trigger on ͼ����ϸ�� for delete
as
print'��ֹɾ����¼'
rollback transaction
go

delete from ͼ����ϸ��
where ����='U66'
go

drop trigger ts_delete_trigger

--�ڶ�����Ϣ���ϴ���һ����Ϊdzxx_insert_trigger�Ĵ����������ڶ�����Ϣ���в����¼ʱ�����ü�¼�еĽ���֤���Զ�����軹��ϸ���С�
drop trigger dzxx_insert_trigger
go

create trigger dzxx_insert_trigger on ������Ϣ�� for insert
as
declare @no varchar(50)
select @no = ����֤�� from inserted
insert into �軹��ϸ��(����֤��)
values(@no)
print'�Ѿ����軹��ϸ�������������'
go

insert into ������Ϣ��
    values
	('12345678','r','��','2020-10-10', 1 ,'�����ϵ','87654321','r@163.com')

select *from ������Ϣ��
select *from �軹��ϸ��

drop trigger dzxx_insert_trigger
 