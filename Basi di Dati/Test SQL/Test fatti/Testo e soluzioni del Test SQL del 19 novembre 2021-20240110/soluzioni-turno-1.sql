-- Query 1
select codice, nome
from bambino b, richiesta r
where b.codice = r.codiceb 
and r.preferenza >= 4
and b.citta <> 'Milano'



-- Query 2
select r1.codiceb
from richiesta r1,
richiesta r2,
giocattolo g1,
giocattolo g2
where g1.codice = r1.codiceg
and g2.codice = r2.codiceg
and g1.categoria <> g2.categoria
and r1.codiceb = r2.codiceb
and r1.preferenza = r2.preferenza



-- Query 3
select codiceb, citta, count(*)
from bambino join richiesta on codice = codiceb 
where preferenza = 1
group by codiceb, citta
union
select codiceb, citta, 0 
from bambino b join richiesta r on codice = codiceb 
where codice not in (select codiceb from richiesta where preferenza = 1)



-- Query 4
select cb, cg, case when max(preferenza) is null then 0
		   else max(preferenza)
	       end
from (select b.codice as cb, g.codice as cg
      from bambino b, giocattolo g) t left join richiesta r on t.cb = r.codiceb and t.cg = r.codiceg
group by cb, cg

OPPURE

select b.codice, g.codice, 0
from bambino b, giocattolo g
where b.codice not in (select codiceb from richiesta where codiceg = g.codice)
union
select r.codiceb, r.codiceg, max(preferenza)
from richiesta r
group by r.codiceb, r.codiceg



-- Query 5
select codice, avg(preferenza)
from (select *
      from giocattolo g
	 except
	 select g1.*
	 from richiesta r1,
	 	giocattolo g1,
	 	bambino b1
	 where r1.codiceg = g1.codice and b1.codice = r1.codiceb and b1.citta = 'Firenze') t1 left join
	 richiesta r2 on t1.codice = r2.codiceg
group by codice

OPPURE 

select codice, null
from giocattolo 
where codice not in (select codiceg from richiesta)
union
select r.codiceg, avg(preferenza)
from richiesta r join bambino b on r.codiceb = b.codice
where r.codiceg not in (select codiceg from richiesta r join bambino b on r.codiceb = b.codice where b.citta = 'Firenze')
group by r.codiceg
