/* ===================================================================
-- Eliminazione dello schema e definizione dello schema stesso 
=================================================================== */

DROP DATABASE IF EXISTS esame WITH (force); /* Aggiunto "WITH (force)" per evitare il bug*/
CREATE DATABASE esame;
\c esame

/* ===================================================================
-- Creazione delle tabelle 
-- ================================================================ */
CREATE TABLE astronauta(
    nome varchar(50),
    sesso varchar(1),
    eta integer,

    constraint persona_pk primary key(nome)
);

CREATE TABLE membro(
    nomeastronauta varchar(50),
    equipaggio integer,

    constraint membro_pk primary key(nomeastronauta, equipaggio),
    constraint membro_fk foreign key (nomeastronauta) references astronauta
);

CREATE TABLE stella(
    codicestella varchar(20),
    galassia varchar(50),
    
    constraint stella_pk primary key(codicestella)
);

CREATE TABLE missione(
    equipaggio integer,
    codicestella varchar(20), 
    anno integer,

    constraint missione_pk primary key(equipaggio,codicestella,anno),
    constraint codicestella_fk foreign key(codicestella) references stella,
    constraint valid_anno check (anno > 0 and anno < 1001) 
);

/*  ====================================================================
-- Inserimento nelle tabelle
-- ================================================================== */

INSERT INTO astronauta VALUES ('Samantha', 'F', 42),('Anna', 'F', 30), ('Carlo', 'M', 24), 
                           ('Maria', 'F', 32), ('Roberto', 'M', 37), ('Paola', 'F', 20), 
                           ('Silvia', 'F', 23), ('Marco', 'M', 53), ('Franco', 'M', 60), ('Cristina', 'F', 38),
                           ('Luca', 'M', 25), ('Ilaria', 'F', 35);

INSERT INTO membro VALUES ('Samantha', 1),('Maria', 1),
							('Anna', 2), ('Roberto', 2), ('Marco', 2),('Silvia', 2),
							('Samantha', 3), ('Maria', 3), ('Silvia', 3),
							('Samantha', 4), ('Maria', 4),
                            ('Silvia', 5), 
                            ('Franco', 6),
                            ('Luca', 7),
                            ('Ilaria', 8);

INSERT INTO stella VALUES ('S1','Andromeda'),
						 ('S2','Magellano'),
						 ('S3','Andromeda'),
						 ('S4','Antenne'),
						 ('S5','Andromeda'),
                         ('S6','Sombrero'),
                         ('S7','Via Lattea'),
                         ('S8','Sigaro'),
                         ('S9','Girandola');
						 					 
INSERT INTO missione VALUES (1, 'S1', 200),
							(2, 'S3', 310),
                            (7, 'S3', 310),
                            (8, 'S3', 310),
							(3, 'S3', 800),
							(4, 'S5', 200),
                            (3, 'S9', 200),
                            (1, 'S2', 500),
							(1, 'S2', 230),
							(1, 'S2', 410),
							(1, 'S6', 349),
							(2, 'S2', 107),
                            (7, 'S2', 107),
                            (8, 'S3', 107),
							(3, 'S2', 633),
							(3, 'S2', 790),
							(3, 'S6', 229),
                            (1, 'S7', 39),
                            (3, 'S7', 780),
                            (4, 'S7', 202),
                            (8, 'S7', 202),
                            (9, 'S1', 1);