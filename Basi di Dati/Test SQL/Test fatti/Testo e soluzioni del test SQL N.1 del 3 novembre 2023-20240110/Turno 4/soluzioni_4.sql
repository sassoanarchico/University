-- 1. Mostrare il codice degli equipaggi che nel primo secolo del millennio hanno effettuato almeno una
-- missione nel sistema di una stella della galassia “Andromeda”.
SELECT distinct equipaggio
FROM missione as mi JOIN stella as s ON mi.codicestella = s.codicestella
WHERE galassia = 'Andromeda' and anno <= 100 

-- 2. Chiamiamo “effettivo” un equipaggio che ha almeno un membro ed ha effettuato almeno una
-- missione. Per ogni equipaggio effettivo, mostrare il codice dell’equipaggio ed il numero di missioni
-- effettuate da quell’equipaggio.
SELECT equipaggieffettivi.equipaggio, count(*) as effettuate
FROM (SELECT distinct mi.equipaggio, codicestella, anno
	  FROM missione as mi JOIN membro as m ON mi.equipaggio = m.equipaggio) as equipaggieffettivi
GROUP BY equipaggieffettivi.equipaggio

-- 3. Mostrare il codice di ogni stella nel sistema della quale sono state effettuate solo missioni da parte
-- di equipaggi che hanno almeno un membro.
SELECT codicestella
FROM stella
WHERE codicestella not in (SELECT codicestella
						  FROM missione
						  WHERE equipaggio not in (SELECT equipaggio FROM membro))

-- 4. Per ogni equipaggio, mostrare il numero di astronauti che ne sono membri ed il numero di galassie
-- diverse che sono state visitate (ossia che hanno avuto come meta stelle di quella galassia) nelle
-- missioni di quell’equipaggio.
SELECT m.equipaggio, count(distinct nomeastronauta) as membri, count(distinct galassia) as visitate
FROM membro as m LEFT JOIN missione as mi ON m.equipaggio = mi.equipaggio
				 LEFT JOIN stella as st ON mi.codicestella = st.codicestella
GROUP BY m.equipaggio
UNION
SELECT equipaggio, 0 as membri, count(distinct galassia) as galassie
FROM missione as mi JOIN stella as st ON mi.codicestella=st.codicestella
WHERE equipaggio not in (SELECT equipaggio FROM membro)
GROUP BY mi.equipaggio

-- 5. Se un astronauta a è membro di un equipaggio g e tale equipaggio ha effettuato una missione
-- al sistema di una stella s nell’anno n, diciamo che l’astronauta ha visitato la stella s nell’anno
-- n. Inoltre, diciamo che due astronauti sono “professionalmente gemelli” se in ogni anno hanno
-- visitato lo stesso insieme di stelle. Mostrare tutte le coppie di astronauti professionalmente gemelli,
-- evitando ridondanze nel risultato, ossia evitando coppie di tipo ⟨a, a⟩ ed evitando coppie di tipo
-- ⟨a2, a1⟩ se la coppia ⟨a1, a2⟩ è già presente.
SELECT a1.nome as gemello1, a2.nome as gemello2
FROM astronauta as a1, astronauta as a2
WHERE a1.nome < a2.nome and NOT EXISTS (SELECT codicestella, anno 
				  						FROM membro as m1 JOIN missione as mi1 ON m1.equipaggio = mi1.equipaggio
				  						WHERE m1.nomeastronauta = a1.nome and (codicestella, anno) NOT IN (
												SELECT codicestella, anno  
												FROM membro as m2 JOIN missione as mi2 ON m2.equipaggio = mi2.equipaggio
												WHERE m2.nomeastronauta = a2.nome
										   )
	) and NOT EXISTS (SELECT codicestella, anno 
				  	  FROM membro as m1 JOIN missione as mi1 ON m1.equipaggio = mi1.equipaggio
				  	  WHERE m1.nomeastronauta = a2.nome and (codicestella, anno) NOT IN (
												SELECT codicestella, anno 
												FROM membro as m2 JOIN missione as mi2 ON m2.equipaggio = mi2.equipaggio
												WHERE m2.nomeastronauta = a1.nome
										   )
					 )
