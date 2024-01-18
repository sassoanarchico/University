/* ===================================================================
-- Eliminazione dello schema e definizione dello schema stesso 
=================================================================== */

DROP DATABASE IF EXISTS esame WITH (force); /* Aggiunto "WITH (force)" per evitare il bug*/
CREATE DATABASE esame;
\c esame

/* ===================================================================
-- Creazione delle tabelle 
-- ================================================================ */


CREATE TABLE persona(
    nome varchar(50),
    eta integer,

    constraint persona_pk primary key(nome)
);

CREATE TABLE iscritto(
    nomepersona varchar(50),
    gruppo integer,

    constraint iscritto_pk primary key(nomepersona, gruppo),
    constraint nome_fk foreign key (nomepersona) references persona
);

CREATE TABLE museo(
    codicemuseo varchar(20),
    citta varchar(50),
    tipo varchar(50),

    constraint museo_pk primary key(codicemuseo)
);

CREATE TABLE ingresso(
    gruppo integer,
    codicemuseo varchar(20), 
    giorno integer,

    constraint ingresso_pk primary key(gruppo,codicemuseo,giorno),
    constraint codicemuseo_fk foreign key(codicemuseo) references museo,
    constraint valid_day check (giorno > 0 and giorno < 366) 
);

/*  ====================================================================
-- Inserimento nelle tabelle
-- ================================================================== */


INSERT INTO persona VALUES ('Mario', 42),('Anna', 30), ('Carlo', 24), 
                           ('Maria', 32), ('Roberto', 37), ('Paola', 20), 
                           ('Silvia', 23), ('Marco', 53), ('Franco', 60), ('Cristina', 38),
                           ('Luca', 25), ('Ilaria',35);

INSERT INTO iscritto VALUES ('Mario', 1),('Maria', 1),
							('Anna', 2), ('Roberto', 2), ('Marco', 2),('Silvia', 2),
							('Mario', 3), ('Maria', 3), ('Silvia', 3),
							('Mario', 4), ('Maria', 4),
                            ('Silvia', 5), 
                            ('Franco', 6),
                            ('Luca', 7),
                            ('Ilaria', 8);

INSERT INTO museo VALUES ('M1','Roma','arte contemporanea'),
						 ('M2','Torino','arte egiziana'),
						 ('M3','Roma','arte etrusca'),
						 ('M4','Firenze','arte rinascimentale'),
						 ('M5','Roma','arte moderna'),
                         ('M6','Bologna','arte egiziana'),
                         ('M7','Milano', 'arte moderna'),
                         ('M8','Padova', 'arte classica'),
                         ('M9','Venezia','arte contemporanea');
						 					 
INSERT INTO ingresso VALUES (1, 'M1', 20),
							(2, 'M3', 31),
                            (7, 'M3', 31),
                            (8, 'M3', 31),
							(3, 'M3', 32),
							(4, 'M5', 20),
                            (3, 'M9', 20),
                            (1, 'M2', 50),
							(1, 'M2', 230),
							(1, 'M2', 310),
							(1, 'M6', 349),
							(2, 'M2', 107),
                            (7, 'M2', 107),
                            (8, 'M3', 107),
							(3, 'M2', 63),
							(3, 'M2', 190),
							(3, 'M6', 22),
                            (1, 'M7', 3),
                            (3, 'M7', 78),
                            (4, 'M7', 202),
                            (8, 'M7', 202),
                            (9, 'M1', 1);