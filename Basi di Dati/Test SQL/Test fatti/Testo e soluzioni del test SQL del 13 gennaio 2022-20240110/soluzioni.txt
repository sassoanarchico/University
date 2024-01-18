-- query 1
select distinct p.lavoratore
from partecipa p join attivita a on p.codiceattivita = a.codice
where durata > 10


-- query 2
select a.progetto, count(distinct p.lavoratore) as numero_lavoratori
from attivita a left join partecipa p on a.codice = p.codiceattivita
group by progetto


--query 3
with attperprogetto as (
    select progetto, count(codice) as n_attivita
    from attivita
    group by progetto)
select t.lavoratore, avg(n_attivita) as media_att_progetti
from (select distinct lavoratore, a.progetto, n_attivita
      from partecipa p,
           attperprogetto app,
           attivita a
      where p.codiceattivita = a.codice
        and app.progetto = a.progetto) t
group by t.lavoratore


OPPURE

select t1.lavoratore, avg(t2.somma)
from (select distinct lavoratore, progetto 
	    from attivita a join partecipa p on a.codice = p.codiceattivita) t1
	   join
	   (select progetto, count(codice) as somma
	    from attivita 
	    group by progetto) t2
	   on t1.progetto = t2.progetto
group by t1.lavoratore    

--query 4
select lavoratore, progetto, sum(durata)
from partecipa p join attivita a on a.codice = p.codiceattivita
group by lavoratore, progetto
union
select lavoratore, progetto, 0
from (select lavoratore, progetto
      from partecipa,
           attivita
      except
      select lavoratore, progetto
      from attivita
               join partecipa p2 on attivita.codice = p2.codiceattivita) t


-- query 5
with progettilavoratore as (
    select distinct lavoratore, progetto
    from attivita
             join partecipa p2 on attivita.codice = p2.codiceattivita
)
select lavoratore
from partecipa
except
(
    select lavoratore
    from partecipa
    except
    (
        select j.lavoratore
        from (partecipa p join attivita a on a.codice = p.codiceattivita) j
        where not exists(
                select codice
                from attivita a
                         join progettilavoratore pl on
                            a.progetto = pl.progetto and
                            pl.lavoratore = j.lavoratore and
                            pl.progetto = j.progetto
                except
                (
                    select codiceattivita
                    from partecipa pa
                    where j.lavoratore = pa.lavoratore
                )
            )
    )
)

OPPURE

select distinct p.lavoratore
from attivita a1 join partecipa p on a.codice = p.codiceattivita
where not exists (select codice 
                  from attivita a2
                  where progetto = p.progetto and 
                        p.lavoratore not in (select lavoratore 
                                             from partecipa 
                                            where codiceattivita = a2.codice))