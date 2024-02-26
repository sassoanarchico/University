-- Creazione della tabella 'Prodotto'
CREATE TABLE Prodotto (
    codice VARCHAR(10) PRIMARY KEY,
    categoria VARCHAR(50)
);

-- Inserimento dei dati nella tabella 'Prodotto'
INSERT INTO Prodotto (codice, categoria) VALUES
('P1', 'Sport'),
('P2', 'Edilizia'),
('P3', 'Elettronica'),
('P4', 'Sport'),
('P5', NULL),  -- categoria sconosciuta
('P6', 'Meccanica');

-- Creazione della tabella 'TipoComponente'
CREATE TABLE TipoComponente (
    codice VARCHAR(10) PRIMARY KEY,
    materiale VARCHAR(50) NOT NULL,
    costo DECIMAL(10, 2) NOT NULL
);

-- Inserimento dei dati nella tabella 'TipoComponente'
INSERT INTO TipoComponente (codice, materiale, costo) VALUES
('C1', 'Legno', 10.00),
('C2', 'Plastica', 5.00),
('C3', 'Ferro', 15.00),
('C4', 'Vetro', 8.00),
('C5', 'Silicio', 20.00),
('C6', 'Ferro', 12.00);

-- Creazione della tabella 'Contenuto'
CREATE TABLE Contenuto (
    codiceT VARCHAR(10),
    codiceP VARCHAR(10),
    quantita INT NOT NULL,
    PRIMARY KEY (codiceT, codiceP),
    FOREIGN KEY (codiceT) REFERENCES TipoComponente(codice),
    FOREIGN KEY (codiceP) REFERENCES Prodotto(codice)
);

-- Inserimento dei dati nella tabella 'Contenuto'
INSERT INTO Contenuto (codiceT, codiceP, quantita) VALUES
('C1', 'P1', 2),
('C2', 'P2', 3),
('C3', 'P3', 5),
('C4', 'P4', 1),
('C5', 'P1', 4),
('C6', 'P6', 3),
('C3', 'P4', 1),
('C2', 'P5', 2),
('C6', 'P2', 4);
