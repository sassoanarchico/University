-- Query 1
select codice, nome
from giocattolo g,
     richiesta r
where categoria <> 5
  and g.codice = r.codiceg
  and preferenza <= 4



-- Query 2
select r1.codiceg 
from richiesta r1, richiesta r2
where r1.codiceb = r2.codiceb
and r1.codiceg = r2.codiceg
and r1.preferenza <> r2.preferenza



-- Query 3
select codiceg, categoria, avg(preferenza)
from richiesta, giocattolo
where codiceg = codice
group by codiceg, categoria



-- Query 4
select r1.codiceb, r1.preferenza, count(codiceg)
from richiesta r1 join giocattolo g on g.codice = r1.codiceg and categoria > 3
group by r1.codiceb, r1.preferenza
union
select codice, preferenza, 0
from (select codice, preferenza
      from bambino,
           (select preferenza from richiesta) t
      except
      select codiceb, preferenza
      from richiesta
               join giocattolo on codiceg = codice and categoria > 3
     ) t1

OPPURE 

select codice, preferenza, 0
from bambino, richiesta r
where codice not in (select codiceb from richiesta, giocattolo where codiceg = codice and categoria >3 and preferenza = r.preferenza)
union
select r1.codiceb, r1.preferenza, count(codiceg)
from richiesta r1 join giocattolo g on g.codice = r1.codiceg and categoria > 3
group by r1.codiceb, r1.preferenza



-- Query 5
select t.codice, avg(t.preferenza)
from ((select codice
       from bambino b1
       except
       select codiceb
       from richiesta r1 join giocattolo g1 on r1.codiceg = g1.codice and categoria <> 1) s left join richiesta r2 on r2.codiceb = s.codice) t
group by t.codice

OPPURE

select codice, preferenza, 0
from bambino, richiesta r
where codice not in (select codiceb from richiesta, giocattolo where codiceg = codice and categoria >3 and preferenza = r.preferenza)
union
select r1.codiceb, r1.preferenza, count(codiceg)
from richiesta r1 join giocattolo g on g.codice = r1.codiceg and categoria > 3
group by r1.codiceb, r1.preferenza
