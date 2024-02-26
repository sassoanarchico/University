DROP DATABASE IF EXISTS esame;
CREATE DATABASE esame;
\c esame

CREATE TABLE giornalista(
   codice VARCHAR(4),
   sesso VARCHAR(1),
   cittanascita VARCHAR(20),
   orientamento VARCHAR(20),
   PRIMARY KEY (codice)
);

CREATE TABLE testata(
   nome VARCHAR(4),
   citta VARCHAR(20),
   direttore VARCHAR(4),
   orientamento VARCHAR(20),
   PRIMARY KEY (nome)
);

CREATE TABLE firma(
	codice VARCHAR(4),
	nome VARCHAR(4),
	mese INTEGER,
	anno INTEGER,
	articoli INTEGER,
	PRIMARY KEY (codice, nome, mese, anno)
);


insert into giornalista values
('G1', 'M', 'Napoli', 'sinistra'),
('G2', 'F', 'Roma', 'sinistra'),
('G3', 'M', 'Roma', 'sinistra'),
('G4', 'F', 'Milano', 'radicale'),
('G5', 'M', 'Roma', 'radicale'),
('G6', 'F', 'Roma', 'indipendente'),
('G7', 'M', 'Milano', 'sinistra'),
('G8', 'M', 'Roma', 'centro'),
('G9', 'F', 'Roma', 'sinistra');

insert into testata values
('T1', 'Roma', 'G8', 'centro'),
('T2', 'Roma', 'G2', 'sinistra'),
('T3', 'Milano', 'G5', 'radicale'),
('T4', 'Roma', 'G6', 'indipendente'),
('T5', 'Napoli', 'G3', 'sinistra'),
('T6', 'Napoli', 'G8', 'destra'),
('T7', 'Roma', 'G1', 'sinistra'),
('T8', 'Milano', 'G1', 'sinistra'),
('T9', 'Milano', 'G1', 'sinistra');

insert into firma values 
('G1', 'T1', 1, 2000, 3),
('G2', 'T1', 2, 2001, 2),
('G2', 'T2', 3, 2002, 3),
('G3', 'T1', 4, 1999, 1),
('G4', 'T3', 5, 1984, 2),
('G5', 'T3', 6, 1984, 2),
('G4', 'T4', 7, 1992, 4),
('G6', 'T4', 8, 1992, 5),
('G7', 'T5', 9, 2004, 7),
('G5', 'T6', 10, 2004, 3),
('G7', 'T6', 10, 2003, 2),
('G7', 'T6', 11, 2003, 3),
('G9', 'T6', 10, 2005, 4),
('G1', 'T7', 6, 2003, 4),
('G1', 'T7', 8, 2003, 3),
('G1', 'T7', 1, 2005, 7),
('G2', 'T8', 2, 2010, 4),
('G2', 'T8', 1, 2010, 3),
('G1', 'T8', 1, 2019, 6);