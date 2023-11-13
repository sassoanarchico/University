--1
create table turista (
	codicefiscale varchar(20) primary key,
	cognome varchar(50),
	annonascita integer
);

insert into turista (codicefiscale, cognome, annonascita) values ('10', 'Rossi', 1980);
insert into turista (codicefiscale, cognome, annonascita) values ('20', 'Bianchi', 1990);
insert into turista (codicefiscale, cognome, annonascita) values ('30', 'Verdi', 1985);
insert into turista (codicefiscale, cognome, annonascita) values ('40', 'Gialli', 1995);
--

create table viaggio (
	codice integer primary key,
	anno integer
);

insert into viaggio (codice, anno) values (1, 2000);
insert into viaggio (codice, anno) values (2, 2005);
insert into viaggio (codice, anno) values (3, 2010);
insert into viaggio (codice, anno) values (4, 2012);
insert into viaggio (codice, anno) values (5, 2017);
insert into viaggio (codice, anno) values (6, 2020);

create table visita (
	turista varchar(20),
	citta varchar(20),
	viaggio integer,
	costo integer,
	primary key (turista, citta, viaggio),
	foreign key (turista) references turista(codicefiscale),
	foreign key (viaggio) references viaggio(codice)
);

insert into visita (turista, citta, viaggio, costo) values ('10', 'Roma', 1, 500);
insert into visita (turista, citta, viaggio, costo) values ('10', 'Viterbo', 1, 200);
insert into visita (turista, citta, viaggio, costo) values ('10', 'Napoli', 2, 100);
insert into visita (turista, citta, viaggio, costo) values ('20', 'Roma', 1, 300);
insert into visita (turista, citta, viaggio, costo) values ('30', 'Venezia', 2, 700);
insert into visita (turista, citta, viaggio, costo) values ('30', 'Roma', 3, 400);
insert into visita (turista, citta, viaggio, costo) values ('30', 'Torino', 3, 500);
insert into visita (turista, citta, viaggio, costo) values ('40', 'Roma', 4, 600);
insert into visita (turista, citta, viaggio, costo) values ('40', 'Verona', 4, 400);
insert into visita (turista, citta, viaggio, costo) values ('40', 'Genova', 5, 100);
insert into visita (turista, citta, viaggio, costo) values ('40', 'Livorno', 5, 200);
insert into visita (turista, citta, viaggio, costo) values ('40', 'Firenze', 6, 700);


--2
create or replace function viaggi_turista(codicefiscale varchar(20))
returns table (citta_visitata varchar(20)) as
$$
begin
	return query
	select citta
	from visita v
	where v.turista = codicefiscale;
	
end;
$$ language plpgsql;

select * from viaggi_turista('10');

--3 
alter table turista
add column quantiviaggi integer;

create or replace function aggiorna_quanti_viaggi()
returns trigger as $$
begin
	update turista t
	set quantiviaggi = (
		select count(distinct v.viaggio)
		from visita v
		where v.turista = t.codicefiscale
		);
	return new;
end;
$$ language plpgsql;

create trigger trigger_aggiornaviaggi 
before insert or update or delete on turista
for each statement execute procedure aggiorna_quanti_viaggi();

--test


select * from turista;

--4
alter table viaggio
add column incasso integer default 0;

create or replace function somma_incassi()
returns trigger as $$
begin
	update viaggio v 
	set incasso = (
		select sum(costo)
		from visita
		where viaggio = v.codice
	);
end;
$$ language plpgsql;

create trigger trigger_updateincasso
after insert or update or delete on visita
for each statement execute function somma_incassi();


--5
--5.1
select v.turista, v.citta
from visita v 
	join viaggio vg on vg.codice = v.viaggio
where vg.anno > 2010;

--5.2
--select t.codicefiscale, vg.codice, t.annonascita - vg.anno
--drop 








