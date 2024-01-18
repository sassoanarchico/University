-- Creazione della tabella 'Prodotto'
CREATE TABLE Prodotto (
    codice VARCHAR(10) PRIMARY KEY,
    categoria VARCHAR(50) NOT NULL
);

-- Inserimento dei dati estesi nella tabella 'Prodotto'
INSERT INTO Prodotto (codice, categoria) VALUES
('P1', 'Automobile'),
('P2', 'Bicicletta'),
('P3', 'Scrivania'),
('P4', 'Edilizia'),
('P5', 'Edilizia'),
('P6', 'Elettronica');

-- Creazione della tabella 'TipoComponente'
CREATE TABLE TipoComponente (
    codice VARCHAR(10) PRIMARY KEY,
    materiale VARCHAR(50) NOT NULL,
    costo DECIMAL(10, 2) NOT NULL
);

-- Inserimento dei dati estesi nella tabella 'TipoComponente'
INSERT INTO TipoComponente (codice, materiale, costo) VALUES
('C1', 'Legno', 10.00),
('C2', 'Plastica', 5.00),
('C3', 'Ferro', 15.00),
('C4', 'Legno', 12.00),
('C5', 'Vetro', 8.00),
('C6', 'Silicio', 20.00);

-- Creazione della tabella 'Contenuto'
CREATE TABLE Contenuto (
    codiceT VARCHAR(10),
    codiceP VARCHAR(10),
    quantita INT NOT NULL,
    PRIMARY KEY (codiceT, codiceP),
    FOREIGN KEY (codiceT) REFERENCES TipoComponente(codice),
    FOREIGN KEY (codiceP) REFERENCES Prodotto(codice)
);

-- Inserimento dei dati estesi nella tabella 'Contenuto'
INSERT INTO Contenuto (codiceT, codiceP, quantita) VALUES
('C1', 'P1', 5),
('C2', 'P2', 10),
('C3', 'P3', 4),
('C4', 'P1', 3),
('C2', 'P3', 2),
('C2', 'P4', 1),
('C5', 'P4', 2),
('C6', 'P6', 3);
