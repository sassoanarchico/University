
CREATE TABLE autore(
   codice VARCHAR(5)  NOT NULL PRIMARY KEY,
   cognome VARCHAR(20) NOT NULL,
   eta INTEGER NOT NULL
);

CREATE TABLE libro(
   titolo VARCHAR(20) NOT NULL PRIMARY KEY,
   copieVendute INTEGER NOT NULL
);

CREATE TABLE scritto(
	codicea VARCHAR(5) NOT NULL,
	titolo VARCHAR(20) NOT NULL,
	CONSTRAINT scritto_pkey PRIMARY KEY (codicea,nomel),
	CONSTRAINT scritto_codicea_fkey FOREIGN KEY (codicea)
		REFERENCES autore(codice)
		ON UPDATE CASCADE
		ON DELETE NO ACTION
		DEFERRABLE INITIALLY DEFERRED,
	CONSTRAINT scritto_titolo_fkey FOREIGN KEY (titolo)
		REFERENCES libro(nome)
		ON UPDATE CASCADE
		ON DELETE NO ACTION
		DEFERRABLE INITIALLY DEFERRED
);

insert into autore values
('A1','COA1',31),
('A2','COA2',30),
('A3','COA3',29),
('A4','COA4',19),
('A5','COA5',29),
('A6','COA6',41),
('A7','COA7',45),
('A8','COA8',20),
('A9','COA9',18);
insert into libro values
('L1',11),
('L2',30),
('L3',24),
('L4',10),
('L5',20),
('L6',54);
insert into scritto values 
('A1','L1'),
('A2','L2'),
('A1','L3'),
('A4','L4'),
('A3','L2'),
('A3','L3'),
('A5','L5'),
('A6','L2'),
('A7','L2'),
('A6','L5'),
('A9','L6');