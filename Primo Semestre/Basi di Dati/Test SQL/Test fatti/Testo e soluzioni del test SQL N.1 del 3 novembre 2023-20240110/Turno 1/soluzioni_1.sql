-- 1. Mostrare il codice dei gruppi che hanno fatto registrare almeno un ingresso ad un museo di Roma nel mese di gennaio.
SELECT distinct gruppo
FROM ingresso as i JOIN museo as m ON (i.codicemuseo = m.codicemuseo)
WHERE citta = 'Roma' and giorno <= 31

-- 2. Chiamiamo “attivo” un gruppo che ha almeno un iscritto ed ha fatto registrare almeno un ingresso
-- ad un museo. Per ogni gruppo attivo, mostrare il codice del gruppo ed il numero di ingressi registrati per quel gruppo.
SELECT i.gruppo, count(*) as registrati
FROM ingresso as i 
WHERE i.gruppo in (SELECT gruppo FROM iscritto)
GROUP BY i.gruppo

-- 3. Mostrare il codice di ogni museo che ha fatto registrare solo ingressi di gruppi che hanno almeno un iscritto.
SELECT codicemuseo
FROM museo
WHERE codicemuseo not in (SELECT codicemuseo
						  FROM ingresso
						  WHERE gruppo not in (SELECT gruppo FROM iscritto))

-- 4. Per ogni gruppo, mostrare il numero di iscritti a quel gruppo ed il numero di tipi diversi di musei
-- per i quali sono stati registrati ingressi di quel gruppo. 
SELECT isc.gruppo, count(distinct nomepersona) as iscritti, count(distinct tipo) as tipologie
FROM iscritto as isc LEFT JOIN 
     (ingresso as ing JOIN museo as ms ON ing.codicemuseo = ms.codicemuseo) ON isc.gruppo = ing.gruppo
GROUP BY isc.gruppo
UNION
SELECT gruppo, 0 as iscritti, count(distinct tipo) as tipologie
FROM ingresso as ing JOIN museo as ms ON ing.codicemuseo=ms.codicemuseo
WHERE gruppo not in (SELECT gruppo FROM iscritto)
GROUP BY ing.gruppo	

-- 5. Se una persona p è iscritta ad un gruppo g e per tale gruppo è stato registrato un ingresso al
-- museo m nel giorno d, diciamo che p ha visitato il museo m nel giorno d. Inoltre, diciamo che due
-- persone sono “culturamente gemelle” se in ogni giorno hanno visitato lo stesso insieme di musei.
-- Mostrare tutte le coppie di persone culturalmente gemelle, evitando ridondanze nel risultato, ossia
-- evitando coppie di tipo ⟨p, p⟩ ed evitando coppie di tipo ⟨p2, p1⟩ se la coppia ⟨p1, p2⟩ è già presente.
SELECT p1.nome as gemello1, p2.nome as gemello2
FROM persona as p1, persona as p2
WHERE p1.nome < p2.nome and NOT EXISTS (SELECT codicemuseo, giorno 
				  						FROM iscritto as isc1 JOIN ingresso as ing1 ON isc1.gruppo = ing1.gruppo
				  						WHERE isc1.nomepersona = p1.nome and (codicemuseo, giorno) NOT IN 
										      (
												SELECT codicemuseo, giorno 
												FROM iscritto as isc2 JOIN ingresso as ing2 ON (isc2.gruppo = ing2.gruppo)
												WHERE isc2.nomepersona = p2.nome
										      )
	                                   )
	                    and NOT EXISTS (SELECT codicemuseo, giorno 
				  	                    FROM iscritto as isc1 JOIN ingresso as ing1 ON isc1.gruppo = ing1.gruppo
				  	                    WHERE isc1.nomepersona = p2.nome and (codicemuseo, giorno) NOT IN 
										      (
												SELECT codicemuseo, giorno 
												FROM iscritto as isc2 JOIN ingresso as ing2 ON (isc2.gruppo = ing2.gruppo)
												WHERE isc2.nomepersona = p1.nome
										      )
					                   )