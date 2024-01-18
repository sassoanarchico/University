DROP DATABASE IF EXISTS esame;
CREATE DATABASE esame;
\c esame

CREATE TABLE giocatore(
   codice VARCHAR(2)  NOT NULL PRIMARY KEY,
   cognome VARCHAR(20) NOT NULL,
   eta INTEGER NOT NULL
);

CREATE TABLE squadra(
   nome VARCHAR(20) NOT NULL PRIMARY KEY,
   prestigio INTEGER NOT NULL
);

CREATE TABLE giocato(
	codiceg VARCHAR(2) NOT NULL,
	nomes VARCHAR(20) NOT NULL,
	gol INTEGER NOT NULL,
	CONSTRAINT giocato_pkey PRIMARY KEY (codiceg,nomes),
	CONSTRAINT giocato_codiceg_fkey FOREIGN KEY (codiceg)
		REFERENCES giocatore (codice)
		ON UPDATE CASCADE
		ON DELETE NO ACTION
		DEFERRABLE INITIALLY DEFERRED,
	CONSTRAINT giocato_nomes_fket FOREIGN KEY (nomes)
		REFERENCES squadra (nome)
		ON UPDATE CASCADE
		ON DELETE NO ACTION
		DEFERRABLE INITIALLY DEFERRED
);

insert into giocatore values
('AP','Pirlo',29),
('FI','Inzaghi',24),
('GB','Batistuta',28),
('FT','Totti',24),
('ND','Dida',28),
('LR','Ronaldo',30),
('DH','Hubner',40),
('RB','Baggio',27),
('JZ','Zanetti',30),
('PM','Maldini',32);
insert into squadra values
('Brescia',2),
('Bologna',2),
('Inter',5),
('Reggina',1),
('Milan',5),
('Juventus',5),
('Fiorentina',3),
('Roma',4),
('Atalanta',2);
insert into giocato values 
('AP','Brescia',6),
('AP','Inter',0),
('AP','Reggina',6),
('AP','Milan',41),
('AP','Juventus',19),
('FI','Atalanta',25),
('FI','Juventus',89),
('FI','Milan',126),
('GB','Fiorentina',207),
('GB','Roma',33),
('FT','Roma',307),
('ND','Milan',0),
('LR','Inter',59),
('LR','Milan',9),
('DH','Brescia',85),
('RB','Fiorentina',55),
('RB','Juventus',115),
('RB','Milan',19),
('RB','Bologna',23),
('RB','Inter',17),
('RB','Brescia',46),
('JZ','Inter',21),
('PM','Milan',33);