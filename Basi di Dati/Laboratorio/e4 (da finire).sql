--automobile
create table automobile (
	targa varchar(10) primary key,
	cilindrata numeric not null,
	citta varchar(10) not null
)
insert into automobile values('A1', 500, 'Roma');
insert into automobile values('A2', 1200, 'Roma');
insert into automobile values('A3', 900, 'Milano');
insert into automobile values('A4', 1000, 'Firenze');
insert into automobile values('A5', 2000, 'Palermo');
insert into automobile values('A6', 3000, 'Torino');
insert into automobile values('A7', 2000, 'Torino');
insert into automobile values('A8', 4000, 'Roma');
insert into automobile values('A9', 4000, 'Napoli');
insert into automobile values('A10', 2500, 'Siena');

--garage
create table garage (
	codice varchar(10) primary key,
	citta varchar(20)
)
insert into garage values('G1', 'Roma');
insert into garage values('G2','Firenze');
insert into garage values('G3','Firenze');
insert into garage values('G4','Milano');
insert into garage values('G5','Milano');
insert into garage values('G6','Palermo');
insert into garage values('G7','Roma');
insert into garage values('G8','Palermo');
insert into garage values('G9','Roma');
insert into garage values('G10','Milano');
insert into garage values('G11','Roma');
insert into garage values('G12','Siena');

--custodita
create table custodita (
	targaauto varchar(4),
	codgarage varchar(5) not null,
	numero numeric,
	foreign key(targaauto) references automobile(targa),
	foreign key(codgarage) references garage(codice)
)

insert into custodita values('A1', 'G1', 2);
insert into custodita values('A1', 'G2', 1);
insert into custodita values('A3', 'G5', 1);
insert into custodita values('A2', 'G6', 15);
insert into custodita values('A2', 'G7', 17);
insert into custodita values('A5', 'G6', 18);
insert into custodita values('A5', 'G1', 2);
insert into custodita values('A4', 'G3', 1);
insert into custodita values('A6', 'G1', 1);
insert into custodita values('A5', 'G8', 1);
insert into custodita values('A8', 'G9', null);
insert into custodita values('A8', 'G1', 3);
insert into custodita values('A10', 'G12', 5);

--2.1
DELETE FROM custodita
WHERE targaauto = 'A10'; 
delete from automobile
where citta = 'Siena'

--2.2
update custodita
set numero = numero + 1
where codgarage in (select g.codice
				   	from garage g
				   	where g.citta = 'Roma')
		and targaauto in (select a.targa
						  from automobile a
						  where a.citta = 'Roma')

--3.1
select a.targa, g.codice, g.citta
from automobile a, garage g, custodita c
where c.numero = 1 and 
	  a.targa = c.targaauto and
	  g.codice = c.codgarage
order by targa

--3.2
select distinct a.citta, a.targa
from custodita c
	join automobile a on c.targaauto = a.targa
	join garage g on g.codice = c.codgarage
where a.cilindrata > 100 and c.numero > 10

--3.3
select c.codgarage, sum(c.numero) as numero
from custodita c
	right join garage g on c.codgarage = g.codice
where c.numero > 0
group by c.codgarage
having sum(c.numero) > 0

--3.4
select c.codgarage, sum(c.numero) as numero
from custodita c join garage g on c.codgarage = g.codice
group by c.codgarage
having sum(c.numero) > 10 or sum(c.numero) = null

--3.5
select c.targaauto, sum(c.numero)