-- Query 1
select codiceg
from bambino join richiesta on codice = codiceb
where preferenza = 1 and citta = 'Roma'



-- Query 2
select r1.codiceg
from richiesta r1,
     richiesta r2,
     bambino b1,
     bambino b2
where r1.codiceg = r2.codiceg
  and r1.codiceb = b1.codice
  and r2.codiceb = b2.codice
  and r1.codiceb > r2.codiceb
  and b1.citta <> b2.citta
  and r1.preferenza = r2.preferenza



-- Query 3
select codiceg, categoria, max(preferenza)
from richiesta join giocattolo on codice = codiceg
group by codiceg, categoria



-- Query 4
select r.codiceb, g.categoria, count(distinct codiceg)
from richiesta r join giocattolo g on r.codiceg = g.codice
group by r.codiceb, g.categoria
 
union
 
select b.codice, c.categoria, 0
from bambino b, (select distinct categoria from giocattolo) c
where b.codice not in (select codiceb from richiesta join giocattolo g1 on g1.codice = codiceg and g1.categoria= c.categoria)


-- Query 5
select r1.codiceb
from richiesta r1, richiesta r2
where r1.codiceb = r2.codiceb
  and r1.codiceg != r2.codiceg or r1.preferenza != r2.preferenza
  and not exists (select *
                  from richiesta r3, richiesta r4
                  where r3.codiceb = r1.codiceb and r4.codiceb = r1.codiceb and r3.codiceg != r4.codiceg
                        and r3.preferenza = r4.preferenza)
  and not exists (select *
                  from richiesta r5, giocattolo g
                  where r5.codiceb = b1.codice and r5.codiceg = g.codice and g.categoria <> 5)
