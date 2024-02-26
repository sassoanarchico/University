-- 1. Mostrare il codice e la galassia delle stelle nelle quali è stato effettuata una missione in un secolo diverso dal primo del millennio.
SELECT distinct st.codicestella, galassia
FROM stella as st JOIN missione as mi ON st.codicestella = mi.codicestella
WHERE anno > 100

-- 2. Chiamiamo “esplorata” una stella nel sistema della quale è stato effettuata almeno una missione
-- da parte di un equipaggio. Per ogni stella esplorata della galassia “Andromeda”, mostrare il codice
-- della stella ed il numero di missioni effettuate in quella stella.
SELECT mi.codicestella, count(*) as missioni
FROM missione as mi JOIN stella as st ON mi.codicestella = st.codicestella
WHERE galassia = 'Andromeda'
GROUP BY mi.codicestella

-- 3. Mostrare il codice di ogni equipaggio che ha effettuato missioni solo a stelle della galassia “Magellano”.

SELECT distinct t.equipaggio
FROM (SELECT equipaggio FROM missione UNION SELECT equipaggio from membro) t
WHERE t.equipaggio not in (SELECT equipaggio
						 FROM missione as mi JOIN stella as st ON mi.codicestella = st.codicestella
						 WHERE galassia != 'Magellano')



-- 4. Se un astronauta a è membro di un equipaggio g e tale equipaggio ha effettuato una missione al
-- sistema di una stella s nell’anno n, diciamo che l’astronauta ha visitato la stella s nell’anno n. Per
-- ogni stella, mostrare il codice della stella ed il numero di astronauti diversi che hanno effettuato visite in quella stella.
SELECT codicestella, count(distinct nomeastronauta) as astronauti
FROM missione as mi LEFT JOIN membro as me ON mi.equipaggio = me.equipaggio
GROUP BY codicestella
UNION
SELECT codicestella, 0 as astronauti
FROM stella
WHERE codicestella not in (SELECT codicestella FROM missione)

-- Diciamo che due stelle sono “equipollenti” se in ogni anno l’insieme degli astronauti che hanno
-- visitato una è uguale all’insieme degli astronauti che hanno visitato l’altra. Mostrare tutte le
-- coppie di stelle equipollenti, evitando ridondanze nel risultato, ossia evitando coppie di tipo ⟨s, s⟩
-- ed evitando coppie di tipo ⟨s2, s1⟩ se la coppia ⟨s1, s2⟩ è già presente.
SELECT s1.codicestella as equipollente1, s2.codicestella as equipollente2
FROM stella as s1, stella as s2
WHERE s1.codicestella < s2.codicestella and NOT EXISTS (SELECT nomeastronauta, anno
				  						    FROM missione as mi1 JOIN membro as m1 ON mi1.equipaggio = m1.equipaggio
				  						    WHERE mi1.codicestella = s1.codicestella and (nomeastronauta, anno) NOT IN (
												SELECT nomeastronauta, anno
				  						    	FROM missione as mi2 JOIN membro as m2 ON mi2.equipaggio = m2.equipaggio
				  						    	WHERE mi2.codicestella = s2.codicestella
										   )
	) and NOT EXISTS (SELECT nomeastronauta, anno
					  FROM missione as mi1 JOIN membro as m1 ON mi1.equipaggio = m1.equipaggio
					  WHERE mi1.codicestella = s2.codicestella and (nomeastronauta, anno) NOT IN (
							SELECT nomeastronauta, anno
							FROM missione as mi2 JOIN membro as m2 ON mi2.equipaggio = m2.equipaggio
							WHERE mi2.codicestella = s1.codicestella
						    )
					 )