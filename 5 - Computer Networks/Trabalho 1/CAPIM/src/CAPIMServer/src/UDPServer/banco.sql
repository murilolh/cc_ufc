create database capim;

use capim;

create table usuarios(
   user_login varchar(30),
   user_pass varchar(15),
   user_ip varchar(15),
   user_port integer,
   user_status integer,
   primary key(user_login)
)

create table contatos(
  name1 varchar(30),
  name2 varchar(30)  
)

create table requisicoes(
  name2 varchar(30),
  name1 varchar(30)  
)
