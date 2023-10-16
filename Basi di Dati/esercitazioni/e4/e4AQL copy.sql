CREATE TABLE automobile (
	targa varchar(6) constraint pk1 primary key,
	cilindrata numeric not null,
	citta varchar(20) not null
);

insert into automobile values ('A1', 500, 'Roma');
insert into automobile values ('A2', 1200, 'Roma');
insert into automobile values ('A3', 900, 'Milano');
insert into automobile values ('A4', 1000, 'Firenze');
insert into automobile values ('A5', 2000, 'Palermo');
insert into automobile values ('A6', 3000, 'Torino');
insert into automobile values ('A7', 2000, 'Torino');
insert into automobile values ('A8', 4000, 'Roma');
insert into automobile values ('A9', 4000, 'Napoli');
insert into automobile values ('A10', 2500, 'Siena');

CREATE TABLE garage (
	codice varchar(6) constraint pk2 primary key,
	citta varchar(20)
);

insert into garage values ('G1', 'Roma');
insert into garage values ('G2', 'Firenze'); 
insert into garage values ('G3', 'Firenze'); 
insert into garage values ('G4', 'Milano'); 
insert into garage values ('G5', 'Milano'); 
insert into garage values ('G6', 'Palermo'); 
insert into garage values ('G7', 'Roma'); 
insert into garage values ('G8', 'Palermo'); 
insert into garage values ('G9', 'Roma'); 
insert into garage values ('G10', 'Milano'); 
insert into garage values ('G11', 'Roma'); 
insert into garage values ('G12', 'Siena'); 

CREATE TABLE custodita (
	targaauto varchar(6) not null,
	codgarage varchar(6) not null,
	numero numeric,
	constraint targa foreign key (targaauto) references automobile(targa),
	constraint codice foreign key (codgarage) references garage(codice),
	constraint pk3 primary key(targaauto)
);

insert into custodita values ('A1', 'G1', 2);
insert into custodita values ('A1', 'G2', 1);
insert into custodita values ('A3', 'G5', 1);
insert into custodita values ('A2', 'G6', 15);
insert into custodita values ('A2', 'G7', 17);
insert into custodita values ('A5', 'G6', 18);
insert into custodita values ('A5', 'G1', 2);
insert into custodita values ('A4', 'G3', 1);
insert into custodita values ('A6', 'G1', 1);
insert into custodita values ('A5', 'G8', 1);
insert into custodita values ('A8', 'G9', NULL);
insert into custodita values ('A8', 'G2', 3);
insert into custodita values ('A10', 'G12', 5);
