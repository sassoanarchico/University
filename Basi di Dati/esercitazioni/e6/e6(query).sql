--Q1

select distinct v.turista codice_fiscale, v.citta codice_viaggio
from visita v 
	join viaggio on viaggio.codice = v.viaggio
where viaggio.anno > 2010;

--Q2
select distinct v.turista codice_fiscale, v.viaggio codice_viaggio, viaggio.anno - t.annonascita as età
from visita v
	join viaggio on viaggio.codice = v.viaggio
	join turista t on t.codicefiscale = v.turista;
	
--Q3
select distinct v.citta, count(v.turista)
from visita v
	join viaggio on viaggio.codice = v.viaggio
	join turista t on t.codicefiscale = v.turista
where viaggio.anno - t.annonascita < 18 
group by v.citta, v.turista
having count(v.turista) > 1;

--Q4
select t.codicefiscale, codice, coalesce(max(coalesce(v.costo, 0)), 0) max_costo
from turista t cross join viaggio left join visita v on t.codicefiscale = v.turista and v.viaggio = viaggio.codice
group by t.codicefiscale, codice
order by t.codicefiscale;

--Q5
--insert into visita values ('30', 'Roma', 2, 400);
--delete from visita where turista = '30' and citta = 'Roma' and  viaggio = 2;
select p.turista, v.citta
from visita v
	join (
		select turista, count(distinct viaggio) as num_viaggi 
		from visita 
		group by turista
		having count(distinct viaggio) > 0
	) as p on p.turista = v.turista
group by p.turista, v.citta, p.num_viaggi
having count(distinct v.viaggio) = p.num_viaggi;

--Q6
select codice codice_viaggio, vis.citta, count(v.turista)
from viaggio
	cross join (select distinct citta from visita) as vis
	left join visita v on codice = v.viaggio and vis.citta = v.citta
group by codice, vis.citta
order by codice;

--Q7
select codice, sum(v.costo) as incasso_totale
from visita v 
	join turista t on v.turista = t.codicefiscale
	join viaggio on codice = v.viaggio
where anno - t.annonascita > 18
group by codice
order by sum(v.costo)
limit 1;

--Q8
--delete from visita where turista = '20' and viaggio = 10;
--insert into visita values ('20', 'Roma', 2, 500);

select v1.viaggio viaggio1, v2.viaggio viaggiov2
from visita v1 
	join visita v2 on v1.turista = v2.turista and v1.citta = v2.citta
where v1.viaggio < v2.viaggio
group by v1.viaggio, v2.viaggio
having count(distinct v1.turista) = (select count(distinct turista)
									 from visita 
									 where viaggio = v1.viaggio)
	 and count(distinct v1.turista) = (select count(distinct turista)
									 from visita 
									 where viaggio = v2.viaggio);
									 
									 
--Q9
select anno, count(citta) as numero_citta_visitate_due_Volte
from (select v.anno, citta, count(citta)
	  from viaggio v
	  join visita on v.codice = visita.viaggio
	  group by v.anno, citta
	  having count(citta) >= 2)
group by anno










