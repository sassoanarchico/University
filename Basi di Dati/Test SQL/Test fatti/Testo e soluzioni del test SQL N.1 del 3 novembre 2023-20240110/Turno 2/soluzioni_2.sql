-- 1. Mostrare il codice e la citta dei musei per i quali e stato registrato almeno un ingresso di un gruppo in un mese diverso da gennaio.
SELECT distinct ms.codicemuseo, citta
FROM museo as ms JOIN ingresso as ing ON ms.codicemuseo = ing.codicemuseo
WHERE giorno > 31

-- 2. Chiamiamo “aperto” un museo per cui è stato registrato almeno un ingresso da parte di un gruppo.
-- Per ogni museo aperto di tipo “arte moderna”, mostrare il codice del museo ed il numero di ingressi
-- registrati in quel museo.
SELECT ing.codicemuseo, count(*) as ingressi
FROM ingresso as ing JOIN museo as ms ON ing.codicemuseo = ms.codicemuseo
WHERE tipo = 'arte moderna'
GROUP BY ing.codicemuseo

-- 3. Mostrare il codice di ogni gruppo che ha fatto registrare ingressi solo a musei di Roma.
SELECT DISTINCT gruppo
FROM (SELECT gruppo FROM ingresso UNION SELECT gruppo FROM iscritto) t
WHERE t.gruppo not in (SELECT gruppo
					   FROM ingresso as ing JOIN museo as ms ON ing.codicemuseo = ms.codicemuseo
					   WHERE citta <> 'Roma')

-- 4. Se una persona p è iscritta ad un gruppo g e per tale gruppo è stato registrato un ingresso ad un
-- museo m nel giorno d, diciamo che la persona ha effettuato una visita al museo m nel giorno d.
-- Per ogni museo, mostrare il codice del museo ed il numero di persone diverse che hanno effettuato visite in quel museo.
SELECT codicemuseo, count(distinct nomepersona) as persone
FROM ingresso as ing LEFT JOIN iscritto as isc ON ing.gruppo = isc.gruppo
GROUP BY codicemuseo
UNION
SELECT codicemuseo, 0 as persone
FROM museo
WHERE codicemuseo not in (SELECT codicemuseo FROM ingresso)

-- 5. Diciamo che due musei sono “equipollenti” se in ogni giorno l’insieme delle persone che hanno effettuato visita in uno è uguale all’insieme di persone 
-- che hanno effettuato visita all’altro. Mostrare tutte le coppie di musei equipollenti, evitando ridondanze nel risultato, ossia evitando coppie di
-- tipo ⟨m, m⟩ e coppie di tipo ⟨m2, m1⟩ se la coppia ⟨m1, m2⟩ è già presente.
SELECT m1.codicemuseo as equipollente1, m2.codicemuseo as equipollente2
FROM museo as m1, museo as m2
WHERE m1.codicemuseo < m2.codicemuseo and NOT EXISTS (SELECT nomepersona, giorno
				  						    FROM ingresso as ing1 JOIN iscritto as ins1 ON ing1.gruppo = ins1.gruppo
				  						    WHERE ing1.codicemuseo = m1.codicemuseo and (nomepersona,giorno) NOT IN (
												SELECT nomepersona, giorno
				  						    	FROM ingresso as ing2 JOIN iscritto as ins2 ON ing2.gruppo = ins2.gruppo
				  						    	WHERE ing2.codicemuseo = m2.codicemuseo
										   )
	) and NOT EXISTS (SELECT nomepersona, giorno
					  FROM ingresso as ing1 JOIN iscritto as ins1 ON ing1.gruppo = ins1.gruppo
					  WHERE ing1.codicemuseo = m2.codicemuseo and (nomepersona, giorno) NOT IN (
							SELECT nomepersona, giorno
							FROM ingresso as ing2 JOIN iscritto as ins2 ON ing2.gruppo = ins2.gruppo
							WHERE ing2.codicemuseo = m1.codicemuseo
						    )
					 )
