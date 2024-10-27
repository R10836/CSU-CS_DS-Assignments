create database if not exists the_byd;
use the_byd;
drop table if exists quote_of_byd;
create table quote_of_byd
(HDate date not null, Open decimal(8,4), Close decimal(8,4), changeamount decimal(8,4), changerate decimal(8,4), Low decimal(8,4), High decimal(8,4), Volume bigint, Volumeamount decimal(14,4), turnoverrate decimal(8,4), primary key (HDate));
select * from quote_of_byd;
delete from quote_of_byd;