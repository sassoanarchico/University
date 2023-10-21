--Q1
select distinct a.codice
from scritto s 
	join autore a on a.codice = s.codicea 
	join libro l on l.titolo = s.titolo
where l.copieVendute > 10

--Q2
select distinct a.codice, a.cognome
from scritto s 
	join autore a on a.codice = s.codicea 
	join libro l on l.titolo = s.titolo
where a.eta > 30 and l.copieVendute < 20

--Q3
select distinct a.codice, a.cognome
from scritto s 
	join autore a on a.codice = s.codicea 
	join libro l on l.titolo = s.titolo
where a.codice not in (
	select a.codice
	from scritto s1 
		join autore a1 on a1.codice = s1.codicea 
		join libro l1 on l1.titolo = s1.titolo
	where l1.copieVendute < 10
)

--Q4
select distinct a.codice, sum(l.copieVendute)
from scritto s 
	join autore a on a.codice = s.codicea 
	join libro l on l.titolo = s.titolo
group by a.codice
having count(a.codice) >= 2

--Q5
select distinct a.codice, 
	case 
		when avg(l.copieVendute) is null then 0
		else avg(l.copieVendute)
	end
from autore a
	left join scritto s on a.codice = s.codicea 
	left join libro l on l.titolo = s.titolo
group by a.codice
order by a.codice

--Q6
select l.titolo, count(a.codice)
from libro l
	join scritto s on l.titolo = s.titolo
	join autore a on s.codicea = a.codice
where l.copieVendute > 15 and a.eta > 40
group by l.titolo;


--Q7
select s.titolo
from scritto s
group by s.titolo
having count(s.codicea) = 1;

--Q8
SELECT a.codice, a.cognome
FROM autore a
JOIN scritto s ON a.codice = s.codicea
JOIN libro l ON s.titolo = s.titolo
GROUP BY a.codice, a.cognome
HAVING SUM(l.copieVendute) = (
    SELECT MAX(copie_totali)
    FROM (
        SELECT SUM(l.copieVendute) AS copie_totali
        FROM autore a
        JOIN scritto s ON a.codice = s.codicea
        JOIN libro l ON s.titolo = l.titolo
        GROUP BY a.codice
    ) AS MaxCopiePerAutore
)


--Q9
select distinct s.titolo
from scritto s
where s.codicea in (
    select s.codicea
    from scritto s
    inner join libro l on s.titolo = l.titolo
    where l.copievendute > 10
    group by s.codicea
    having count(distinct s.titolo) >= 2
);


--Q10
select distinct a.codice, a.cognome
from autore a
where a.codice in (
    select s.codicea
    from scritto s
    inner join libro l on s.titolo = l.titolo
    where l.copievendute > 10
    group by s.codicea
    having count(distinct s.titolo) >= 2
)
and a.codice in (
    select codicea
    from scritto
    group by codicea
    having count(titolo) > 1
);








