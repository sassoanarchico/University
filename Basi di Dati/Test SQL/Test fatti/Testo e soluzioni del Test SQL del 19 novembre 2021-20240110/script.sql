/* ===================================================================
-- Eliminazione dello schema e definizione dello schema stesso 
=================================================================== */

   DROP DATABASE IF EXISTS test_11_16;
   CREATE DATABASE test_11_16; 
   \c test_11_16;

/* ===================================================================
-- Creazione delle tabelle 
-- ================================================================ */

  CREATE TABLE Giocattolo(
  codice      	VARCHAR(20)    PRIMARY KEY,
  nome          	VARCHAR(20),
  categoria       	NUMERIC(2)
  );
  
  CREATE TABLE Bambino(
  codice		NUMERIC(5)	PRIMARY KEY,
  nome          	VARCHAR(20),
  citta          	VARCHAR(20)
  );

  CREATE TABLE Richiesta(
  codiceb		NUMERIC(20),
  codiceg        	VARCHAR(20),
  preferenza     	NUMERIC(1),
  primary key(codiceb,codiceg,preferenza)
  );

/*  ====================================================================
-- Inserimento nelle tabelle
-- ================================================================== */

INSERT INTO Giocattolo(codice,nome,categoria) VALUES ('100','Barbi',10);
INSERT INTO Giocattolo(codice,nome,categoria) VALUES ('200','PS2',5);
INSERT INTO Giocattolo(codice,nome,categoria) VALUES ('300','PS3',8);
INSERT INTO Giocattolo(codice,nome,categoria) VALUES ('400','PS4',15);
INSERT INTO Giocattolo(codice,nome,categoria) VALUES ('500','Biliardino',12);
INSERT INTO Giocattolo(codice,nome,categoria) VALUES ('600','Flipper',20);
INSERT INTO Giocattolo(codice,nome,categoria) VALUES ('700','Dama',9);
INSERT INTO Giocattolo(codice,nome,categoria) VALUES ('800','Monopoli',1);
INSERT INTO Giocattolo(codice,nome,categoria) VALUES ('900','Lego',2);
INSERT INTO Giocattolo(codice,nome,categoria) VALUES ('1000','Meccano',2);
INSERT INTO Giocattolo(codice,nome,categoria) VALUES ('1100','Trenino',5);
INSERT INTO Giocattolo(codice,nome,categoria) VALUES ('1200','Trottola',1);
INSERT INTO Giocattolo(codice,nome,categoria) VALUES ('1300','Bicicletta',20);
INSERT INTO Giocattolo(codice,nome,categoria) VALUES ('1400','Chimico',15);
INSERT INTO Giocattolo(codice,nome,categoria) VALUES ('1500','Scarabeo',2);
INSERT INTO Giocattolo(codice,nome,categoria) VALUES ('1600','Wii',13);



INSERT INTO Bambino(codice,nome,citta) VALUES('10','Paolo','Roma');
INSERT INTO Bambino(codice,nome,citta) VALUES('20','Maria','Roma');
INSERT INTO Bambino(codice,nome,citta) VALUES('30','Giovanni','Milano');
INSERT INTO Bambino(codice,nome,citta) VALUES('40','Anna','Palermo');
INSERT INTO Bambino(codice,nome,citta) VALUES('50','Ugo','Firenze');
INSERT INTO Bambino(codice,nome,citta) VALUES('60','Stefania','Roma');
INSERT INTO Bambino(codice,nome,citta) VALUES('70','Antonella','Milano');
INSERT INTO Bambino(codice,nome,citta) VALUES('80','Antonio','Palermo');
INSERT INTO Bambino(codice,nome,citta) VALUES('90','Giuseppe','Genova');
INSERT INTO Bambino(codice,nome,citta) VALUES('15','Giorgio','Firenze');
INSERT INTO Bambino(codice,nome,citta) VALUES('25','Laura','Milano');
INSERT INTO Bambino(codice,nome,citta) VALUES('35','Carlo','Roma');
INSERT INTO Bambino(codice,nome,citta) VALUES('45','Simona','Pisa');
INSERT INTO Bambino(codice,nome,citta) VALUES('55','Luisa','Genova');
INSERT INTO Bambino(codice,nome,citta) VALUES('65','Fabio','Pisa');

INSERT INTO Richiesta(codiceb,codiceg,preferenza) VALUES('10','100',1);
INSERT INTO Richiesta(codiceb,codiceg,preferenza) VALUES('10','200',2);
INSERT INTO Richiesta(codiceb,codiceg,preferenza) VALUES('10','200',4);
INSERT INTO Richiesta(codiceb,codiceg,preferenza) VALUES('20','300',3);
INSERT INTO Richiesta(codiceb,codiceg,preferenza) VALUES('15','100',5);
INSERT INTO Richiesta(codiceb,codiceg,preferenza) VALUES('25','400',2);
INSERT INTO Richiesta(codiceb,codiceg,preferenza) VALUES('25','300',1);
INSERT INTO Richiesta(codiceb,codiceg,preferenza) VALUES('30','500',2);
INSERT INTO Richiesta(codiceb,codiceg,preferenza) VALUES('30','700',4);
INSERT INTO Richiesta(codiceb,codiceg,preferenza) VALUES('30','200',3);
INSERT INTO Richiesta(codiceb,codiceg,preferenza) VALUES('40','800',1);
INSERT INTO Richiesta(codiceb,codiceg,preferenza) VALUES('40','1100',1);
INSERT INTO Richiesta(codiceb,codiceg,preferenza) VALUES('40','1200',5);
INSERT INTO Richiesta(codiceb,codiceg,preferenza) VALUES('40','600',3);
INSERT INTO Richiesta(codiceb,codiceg,preferenza) VALUES('45','100',5);
INSERT INTO Richiesta(codiceb,codiceg,preferenza) VALUES('50','900',2);
INSERT INTO Richiesta(codiceb,codiceg,preferenza) VALUES('50','1300',3);
INSERT INTO Richiesta(codiceb,codiceg,preferenza) VALUES('50','500',4);
INSERT INTO Richiesta(codiceb,codiceg,preferenza) VALUES('90','400',2);
INSERT INTO Richiesta(codiceb,codiceg,preferenza) VALUES('90','500',4);
INSERT INTO Richiesta(codiceb,codiceg,preferenza) VALUES('65','200',2);
INSERT INTO Richiesta(codiceb,codiceg,preferenza) VALUES('65','600',3);
INSERT INTO Richiesta(codiceb,codiceg,preferenza) VALUES('65','600',5);

