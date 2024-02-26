/* ===================================================================
-- Eliminazione dello schema e definizione dello schema stesso 
=================================================================== */

   DROP DATABASE IF EXISTS esame;
   CREATE DATABASE esame; 
   \c esame;

/* ===================================================================
-- Creazione delle tabelle 
-- ================================================================ */

create table attivita
(
    codice   integer not null
        constraint attivita_pk
            primary key,
    progetto varchar not null,
    durata   integer not null
);

create table partecipa
(
    codiceattivita integer not null
        constraint partecipa_pk
            primary key
        constraint partecipa_attivita_codice_fk
            references attivita,
    lavoratore     integer not null
);

/*  ====================================================================
-- Inserimento nelle tabelle
-- ================================================================== */

INSERT INTO attivita (codice, progetto, durata) VALUES (100, 'Basic101', 15);
INSERT INTO attivita (codice, progetto, durata) VALUES (101, 'Basic101', 7);
INSERT INTO attivita (codice, progetto, durata) VALUES (102, 'Basic101', 8);
INSERT INTO attivita (codice, progetto, durata) VALUES (103, 'Basic101', 9);
INSERT INTO attivita (codice, progetto, durata) VALUES (104, 'Basic101', 10);
INSERT INTO attivita (codice, progetto, durata) VALUES (200, 'Intermediate25', 7);
INSERT INTO attivita (codice, progetto, durata) VALUES (201, 'Intermediate25', 8);
INSERT INTO attivita (codice, progetto, durata) VALUES (202, 'Intermediate25', 12);
INSERT INTO attivita (codice, progetto, durata) VALUES (203, 'Intermediate25', 22);
INSERT INTO attivita (codice, progetto, durata) VALUES (300, 'Advanced41', 30);
INSERT INTO attivita (codice, progetto, durata) VALUES (301, 'Advanced41', 35);
INSERT INTO attivita (codice, progetto, durata) VALUES (302, 'Advanced41', 41);
INSERT INTO attivita (codice, progetto, durata) VALUES (303, 'Advanced41', 30);
INSERT INTO attivita (codice, progetto, durata) VALUES (304, 'Advanced41', 8);
INSERT INTO attivita (codice, progetto, durata) VALUES (305, 'Advanced41', 15);
INSERT INTO attivita (codice, progetto, durata) VALUES (400, 'Void10', 11);
INSERT INTO attivita (codice, progetto, durata) VALUES (401, 'Void10', 11);
INSERT INTO attivita (codice, progetto, durata) VALUES (500, 'Void20', 15);
INSERT INTO attivita (codice, progetto, durata) VALUES (600, 'Singleton42', 6);
INSERT INTO attivita (codice, progetto, durata) VALUES (601, 'Singleton42', 8);
INSERT INTO attivita (codice, progetto, durata) VALUES (602, 'Singleton42', 16);
INSERT INTO attivita (codice, progetto, durata) VALUES (700, 'Singleton44', 20);
INSERT INTO attivita (codice, progetto, durata) VALUES (800, 'YAS152', 12);
INSERT INTO attivita (codice, progetto, durata) VALUES (801, 'YAS152', 7);
INSERT INTO attivita (codice, progetto, durata) VALUES (802, 'YAS152', 22);
INSERT INTO attivita (codice, progetto, durata) VALUES (900, 'YBest43', 2);
INSERT INTO attivita (codice, progetto, durata) VALUES (901, 'YBest43', 18);

INSERT INTO partecipa (codiceattivita, lavoratore) VALUES (305, 300811);
INSERT INTO partecipa (codiceattivita, lavoratore) VALUES (101, 100151);
INSERT INTO partecipa (codiceattivita, lavoratore) VALUES (102, 200262);
INSERT INTO partecipa (codiceattivita, lavoratore) VALUES (301, 100151);
INSERT INTO partecipa (codiceattivita, lavoratore) VALUES (303, 300811);
INSERT INTO partecipa (codiceattivita, lavoratore) VALUES (103, 300811);
INSERT INTO partecipa (codiceattivita, lavoratore) VALUES (201, 300811);
INSERT INTO partecipa (codiceattivita, lavoratore) VALUES (203, 200262);
INSERT INTO partecipa (codiceattivita, lavoratore) VALUES (200, 100151);
INSERT INTO partecipa (codiceattivita, lavoratore) VALUES (100, 200262);
INSERT INTO partecipa (codiceattivita, lavoratore) VALUES (600, 448811);
INSERT INTO partecipa (codiceattivita, lavoratore) VALUES (601, 448811);
INSERT INTO partecipa (codiceattivita, lavoratore) VALUES (602, 448811);
INSERT INTO partecipa (codiceattivita, lavoratore) VALUES (700, 448811);
INSERT INTO partecipa (codiceattivita, lavoratore) VALUES (800, 121516);
INSERT INTO partecipa (codiceattivita, lavoratore) VALUES (802, 121516);
INSERT INTO partecipa (codiceattivita, lavoratore) VALUES (304, 121516);
INSERT INTO partecipa (codiceattivita, lavoratore) VALUES (801, 121516);
INSERT INTO partecipa (codiceattivita, lavoratore) VALUES (900, 121516);
