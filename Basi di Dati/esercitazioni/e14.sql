--Q1
select distinct codice
from autore 
	join scritto on codicea = codice
	join libro on nomel = nome
where copieVendute >= 10
order by codice;

--Q2
select codice, cognome
from autore 
	join scritto on codicea = codice
	join libro on nomel = nome
where copieVendute >= 20 and eta <= 30;

--Q3
select codice, cognome
from autore
where not exists (
    select 1
    from scritto
    	join libro on nomel = nome
    where copievendute > 10 and codicea = codice
);

--Q4
select nome as nome_libro, count(codice) as numero_autori
from autore 
	join scritto on codicea = codice
	join libro on nomel = nome
where eta > 40 and copieVendute >= 15
group by nome;

--Q5
with autore_famoso as (
	select codicea
	from scritto 
		join libro on nomel = nome
	where copieVendute > 10
	group by codicea
	having count(distinct nomel) >= 2
)

select distinct af1.codicea as autore1, af2.codicea as autore2
from autore_famoso af1
	join autore_famoso af2 on af1.codicea < af2.codicea;

--Q6
with q6 as(
	select distinct codice, avg(copieVendute) as media_copie
	from autore 
		join scritto on codicea = codice
		join libro on nomel = nome
	group by codice
	union
	select codice, NULL
	from autore
	where codice not in (
		select distinct codicea
		from autore 
			join scritto s on s.codicea = codice
			join libro on nomel = nome
		group by s.codicea
	)
)

select *
from q6
order by codice;

--Q7
select codicea, sum(copieVendute)
from scritto 
	join libro on nomel = nome
	join autore on codicea = codice
where eta > 30
group by codicea
having count(nomel) >= 2
order by codicea;

--Q8
select nomel
from scritto 
group by nomel
having count(distinct codicea) = 1 
order by nomel;

--Q9
select distinct codice, cognome
from autore
	join scritto on codice = codicea
	join libro on nomel = nome
group by codice, cognome
having sum(copieVendute) = (
	select max(somma) as massimo
	from (
		select codicea, sum(copieVendute) as somma
		from libro
			join scritto on nomel = nome
		group by codicea
	)	
)

