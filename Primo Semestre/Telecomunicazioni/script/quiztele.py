import difflib
import random
import tkinter as tk
from tkinter import messagebox, StringVar
from PIL import Image, ImageTk
import os

# Variabili globali per tenere traccia delle risposte corrette e del numero totale di domande
risposte_corrette = 0
domande_mostrate = 0

path_immagine = "/Users/paffo/Desktop/telecomunicazioni/script/img/"

# ------------- Dati quiz -------------#
dati_quiz = [
    # - Esame Gennaio - #
    {
        "esame": "Gennaio d1",
        "testo_domanda": "Una multiplazione statica opera su un canale suddiviso in Intervalli Temporali (IT) e organizzato in trame. La trama ha la durata di 0.5 ms. Ciascun IT contiene 10 bit. Qual e' il numero minimo di IT che debbono essere assegnati per servire con sovramultiplazione una sorgente continua che emette al ritmo bianario di 35  Mbit/s",
        "immagine_domanda": None,  # Percorso opzionale
        "opzioni": [
            {"testo": "a. 1"},
            {"testo": "b. 2"},
            {"testo": "c. 3"},
            {"testo": "d. 4"}
        ],
        "risposta_corretta": "b. 2",
        "soluzione": """Il numero minimo di IT necessario per servire la sorgente continua che emette al ritmo binario di 35 Mbit/s, con ciascun IT contenente 10 bit e la trama che ha una durata di 0.5 ms, è 4. Quindi la risposta corretta è 'b. 2', poiché è il numero minimo di IT richiesto."""
    },
'''
    {
        "esame": "Gennaio d2",
        "testo_domanda": "Si consideri lo scenario di rete mostrato in figura, in cui il routing è gestito mediante protocollo Distance Vector. Inizialmente il protocollo è arrivato a convergenza, perciò i percorsi  usati sono quelli a costo minimo. Successivamente il costo del collegamento tra i router C e D diventa  pari a 10. indicare cosa succede immediatamente dopo relativamente al percorso per la destinazione P",
        "immagine_domanda": path_immagine + "gennaio/d2.png",
        "opzioni": [
            {"testo": "a. il router C indivisura il percorso alternativo C-A-B-D"},
            {"testo": "b. si verifica un loop"},
            {"testo": "c. il router C continuua ad usare il percorso C-D"},
            {"testo": "d. il router C individua il percorso alternativo C-B-D"}
        ],
        "risposta_corretta": "b. si verifica un loop"
    },
''',
    {
        "esame": "Gennaio d3",
        "testo_domanda": "Indicare quale tra i seguenti è un protocollo di routing.",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. ICMP"},
            {"testo": "b. BGP"},
            {"testo": "c. ARP"},
            {"testo": "d. DHCP"}
        ],
        "risposta_corretta": "b. BGP",
        "soluzione": "Il protocollo di routing tra le opzioni fornite è 'b. BGP' (Border Gateway Protocol)."
    },
    {
        "esame": "Gennaio d4",
        "testo_domanda": "Siano date le 4 stringhe di 4 bit riportate di seguito: b1) 1001; b2) 1011; b3) 0101; b4) 1010. Qual è la parola di codice calcolata mediante l'internet checksum?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. 1111"},
            {"testo": "b. 0101"},
            {"testo": "c. 1010"}
        ],
        "risposta_corretta": "c. 1010",
        "soluzione": """La parola di codice calcolata mediante l'internet checksum per le stringhe fornite è 'c. 1010'."""
    },
    {
        "esame": "Gennaio d5",
        "testo_domanda": "Nel caso si usi una tecnica di accesso multiplo con allocazione dinamica, il protocollo MAC:",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. è necessario per svolgere la funzione di coordinamento nella condivisione dinamica della capacità del mezzo multiaccesso"},
            {"testo": "b. è un elemento opzionale dell'architettura dei protocolli, utile per migliorare le prestazioni in termini di efficienza di utilizzazione del mezzo multiaccesso"},
            {"testo": "c. è necessario per proteggere dagli errori le unità di dati trasmesse sul mezzo multiaccesso"}
        ],
        "risposta_corretta": "a. è necessario per svolgere la funzione di coordinamento nella condivisione dinamica della capacità del mezzo multiaccesso",
        "soluzione": "Nel caso si utilizzi una tecnica di accesso multiplo con allocazione dinamica, il protocollo MAC è necessario per svolgere la funzione di coordinamento nella condivisione dinamica della capacità del mezzo multiaccesso. Quindi la risposta corretta è 'a'."
    },
    {
        "esame": "Gennaio d6",
        "testo_domanda": "In una procedura di recupero d'errore Go-Back-N si adotta una finestra in emissione che ha larghezza 3. Supponendo che lato emittente (A) la finestra abbia in un dato istante limite inferiore uguale a 5. Come reagisce A ricevendo dal ricevente (B) una PDU con numero di sequenza in ricezione Rnext=7?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Trasmette per la prima volta il trame 5 e 6"},
            {"testo": "b. Aggiorna il limite inferiore della finestra al valore 8"},
            {"testo": "c. Aggiorna il limite inferiore della finestra al valore 7"},
            {"testo": "d. Mantiene il limite inferiore della finestra al valore 5"}
        ],
        "risposta_corretta": "c. Aggiorna il limite inferiore della finestra al valore 7",
        "soluzione": "In una procedura di recupero d'errore Go-Back-N con una finestra in emissione di larghezza 3, se il lato emittente (A) ha il limite inferiore della finestra uguale a 5 e riceve dal ricevente (B) una PDU con numero di sequenza in ricezione Rnext=7, A aggiorna il limite inferiore della finestra al valore 7. Quindi la risposta corretta è 'c'."
    },
    {
        "esame": "Gennaio d7",
        "testo_domanda": "Si consideri un protocollo di controllo dell'errore di tipo Go-BACK-N. Sia: 1) ritardo di propagazione pari a 1/3 del tempo di trasmissione di una trama; 2) il tempo di trasmissione dei riscontri pari a 2/3 del tempo di trasmissione di una trama e l'elaborazione nei nodi trascurabile. Quanto deve essere la dimensione minima della finestra in emissione Ws affinché, se non si verificano errori, il trasmettitore sia in grado di trasmettere trame continuamente (senza soluzione di continuità)?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Ws=3"},
            {"testo": "b. Ws=4"},
            {"testo": "c. Ws=2"}
        ],
        "risposta_corretta": "a. Ws=3",
        "soluzione": """Per garantire una trasmissione continua senza soluzione di continuità in un protocollo di controllo dell'errore di tipo Go-BACK-N, è necessario che il ritardo di propagazione sia coperto dalla finestra in emissione (Ws). In questo caso, il ritardo di propagazione è 1/3 del tempo di trasmissione di una trama. Quindi, la dimensione minima della finestra in emissione Ws deve essere almeno 3 trame (1 trama per la trasmissione e 2 trame per coprire il ritardo di propagazione).

Quindi, la risposta corretta è 'a. Ws=3'."""
        
    },
    {
        "esame": "Gennaio d8",
        "testo_domanda": "Avendo a disposizione un prefisso /24 e considerando lo scenario di rete mostrato in figura, determinare quale tra i seguenti indirizzi può essere assegnato all'interfaccia del router connessa alla LAN B",
        "immagine_domanda": path_immagine + "gennaio/d8.png",
        "opzioni": [
            {"testo": "а. 10.0.1.193"},
            {"testo": "b. 10.0.1.129"},
            {"testo": "c. 10.0.1.33"},
            {"testo": "d. 10.0.1.70"}
        ],
        "risposta_corretta": "d. 10.0.1.70",
        "soluzione": """Dato il prefisso /24, l'indirizzo IP assegnato all'interfaccia del router connessa alla LAN B deve appartenere alla stessa sottorete. Analizzando i bit di rete, l'indirizzo corretto è 'd. 10.0.1.70', poiché il bit di host è 70, che è valido all'interno di una sottorete /24."""
    },
    {
        "esame": "Gennaio d9",
        "testo_domanda": "Il modello OSI mira a rappresentare: \nScegli un'alternativa:",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. le interazioni che avvengono tra la CPU di un computer e i processi del sistema"},
            {"testo": "b. le interazioni che avvengono tra sistemi differenti interconnessi in rete"},
            {"testo": "c. esclusivamente gli scambi di messaggi che si hanno tra host e server di Internet"},
            {"testo": "d. le interazioni tra le applicazioni degli utenti e i sistemi che servono a farle comunicare"}
        ],
        "risposta_corretta": "b. le interazioni che avvengono tra sistemi differenti interconnessi in rete",
        "soluzione": """Il modello OSI mira a rappresentare le interazioni che avvengono tra sistemi differenti interconnessi in rete. Pertanto, la risposta corretta è 'b. le interazioni che avvengono tra sistemi differenti interconnessi in rete'."""
    },
    {
        "esame": "Gennaio d10",
        "testo_domanda": "Avendo un canale in banda traslata di dimensione 40 MHz: \nScegli un'alternativa:",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Con una multiplazione FDM si possono teoricamente multiplare fino a 10 comunicazioni digitali con occupazione di banda 2 MHz ognuna"},
            {"testo": "b. Si puo' avere sempre solo una singola comunicazione digitale per volta di banda 20 MHz"},
            {"testo": "c. Con una multiplazione FDM si possono teoricamente multiplare fino a 20 comunicazioni digitali con occupazione di banda 2 MHz ognuna"},
            {"testo": "d. Si puo' avere sempre solo una singola comunicazione digitale per volta di banda 40 MHZ"}
        ],
        "risposta_corretta": "c. Con una multiplazione FDM si possono teoricamente multiplare fino a 20 comunicazioni digitali con occupazione di banda 2 MHz ognuna"
    },
    {
        "esame": "Gennaio d11",
        "testo_domanda": "Qual è l'obiettivo primario dello Spanning Tree Protocol utilizzato nelle switched LAN?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Prevenire \"routing loops\" in reti LAN dove sono presenti cammini ridondanti tra i router"},
            {"testo": "b. Scegliere il cammino più breve per istradare le trame (frame) tra gli switch"},
            {"testo": "c. Riempire le \"switching table\" degli switch con i cammini a costo minimo per raggiungere tutti gli host della LAN"},
            {"testo": "d. Prevenire \"switching loops\" in reti LAN dove sono presenti cammini ridondanti tra gli switch"}
        ],
        "risposta_corretta": "d. Prevenire \"switching loops\" in reti LAN dove sono presenti cammini ridondanti tra gli switch"
    },
    {
        "esame": "Gennaio d12",
        "testo_domanda": "Con riferimento alla topologia fisica mostrata in figura, determinare il numero di sotto-reti",
        "immagine_domanda": path_immagine + "gennaio/d12.png",
        "opzioni": [
            {"testo": "a. 5"},
            {"testo": "b. 4"},
            {"testo": "c. 7"},
            {"testo": "d. 10"}
        ],
        "risposta_corretta": "a. 5"
    },
    {
        "esame": "Gennaio d13",
        "testo_domanda": "Si considerino i tre nodi A, B, C, che trasmettono in modalità accesso multiplo slotted ALOHA. Data l'evoluzione temporale delle trasmissioni riportata in figura, completando quello che accade sul mezzo condiviso, qual e' la portata utile normalizzata nella finestra temporale F?",
        "immagine_domanda": path_immagine + "gennaio/d13.png",
        "opzioni": [
            {"testo": "a. 1"},
            {"testo": "b. 0,66"},
            {"testo": "c. 0,83"}
        ],
        "risposta_corretta": "b. 0,66"
    },
    {
        "esame": "Gennaio d14",
        "testo_domanda": "Due sistemi terminali stanno scambiando messaggi utilizzando una connessione TCP. Al tempo T=10 secondi, istante in cui si verifica un evento di RTO, la congestion window ha una dimensione pari a 36 MSS. Assumendo che I'RTT è costante e pari a 100 millisecondi, indicare la dimensione della congestion window all'istante T1=10,3 secondi",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. 3 MSS"},
            {"testo": "b. 18 MSS"},
            {"testo": "c. 4 MSS"},
            {"testo": "d. 21 MSS"}
        ],
        "risposta_corretta": "c. 4 MSS"
    },
    {
        "esame": "Gennaio d15",
        "testo_domanda": "Si consideri la rete LAN composta da SWITCH e HUB riportata in Figura dove la numerazione delle porte per tutti i dispositivi e' progressiva da sinistra a destra come quella d'esempio riportata per l'HUB1. \nSi consideri che è gia avvenuto uno scambio di trama tra 52 e 55. Indicare se e come si riempe la tabella dello SW1 al seguito di un frame di risposta di S5 diretto a 52.",
        "immagine_domanda": path_immagine + "gennaio/d15.png",
        "opzioni": [
            {"testo": "a. La tabella si riempe con un'ulteriore riga che indica: 55 su porta 2"},
            {"testo": "b. La tabella si riempie con S2 su porta 8 dell'HUB2"},
            {"testo": "c. La tabella non si riempie ulterioremente in quanto già presente 52 su porta 1"}
        ],
        "risposta_corretta": "a. La tabella si riempe con un'ulteriore riga che indica: 55 su porta 2"
    },
    # - Febbraio - #
    {
        "esame": "Febbraio d1",
        "testo_domanda": "n una rete caratterizzata dal prefisso 151.168.0.0/23, quanti host possono essere indirizzati al massimo ?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. 256"},
            {"testo": "b. 1024"},
            {"testo": "c. 512"}
        ],
        "risposta_corretta": "c. 512"
    },
    {
        "esame": "Febbraio d2",
        "testo_domanda": "Avendo un canale in banda traslata di dimensione 40 MHz: Scegli un'alternativa: ",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Si puo' avere sempre solo una singola comunicazione digitale per volta di banda 40 MHz"},
            {"testo": "b. Si puo' avere sempre solo una singola comunicazione digitale per volta di banda 20 MHz"},
            {"testo": "c Con una multiplazione FDM si possono teoricamente multiplare fino a 10 comunicazioni digitali con occupazione di banda 2 MHz ognuna"},
            {"testo": "d. Con una multiplazione FDM si possono teoricamente multiplare fino a 20 comunicazioni digitali con occupazione di banda 2 MHz ognuna"}
        ],
        "risposta_corretta": "d. Con una multiplazione FDM si possono teoricamente multiplare fino a 20 comunicazioni digitali con occupazione di banda 2 MHz ognuna"
    },
    {
        "esame": "Febbraio d3",
        "testo_domanda": "In una procedura di recupero d'errore Go-Back-N si adotta una finestra in emissione che ha larghezza 4. Supponendo che lato emettitore la finestra abbia in un dato istante limite inferiore uguale a4. Come reagisce Aricevendo dal ricevente (B) una PDU con numero di sequenza in ricezione Rnext=8?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Aggiorna li limite inferiore della finestra al valore 7 e trasmette le trame 7-8"},
            {"testo": "b. Posiziona il limite inferiore della finestra a 5 e trasmette le trame 5-8."},
            {"testo": "c. Aggiorna li limite inferiore della finestra al valore 8 e trasmette le trame v 8-11"},
            {"testo": "d. Trasmette per la prima volta le trame 4-7."}
        ],
        "risposta_corretta": "c. Aggiorna li limite inferiore della finestra al valore 8 e trasmette le trame v 8-11"
    },
    {
        "esame": "Febbraio d4",
        "testo_domanda": "I processi applicativi che sono attivi in un host ricevono idati di propria competenza grazie",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. alle informazioni contenute nei campi indirizzo di destinazione e tipo di protocollo del pacchetto IP che porta idati."},
            {"testo": "b. alle informazioni di indirizzamento contenute nei dati stessi."},
            {"testo": "c. alla funzione di indirizzamento svolta dal livello di trasporto (UDP, TCP)"}
        ],
        "risposta_corretta": "c. alla funzione di indirizzamento svolta dal livello di trasporto (UDP, TCP)"
    },
    {
        "esame": "Febbraio d5",
        "testo_domanda": "Qual è l'obiettivo primario dello Spanning Tree Protocol utilizzato nelle switched LAN?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Scegliere li cammino più breve per istradare le trame (frame) tra gli switch"},
            {"testo": "b. Prevenire \"switching loops\" ni reti LAN dove sono presenti cammini ridondanti tra gli switch"},
            {"testo": "c. Riempire le \"switching table\" degli switch con i cammini a costo minimo per raggiungere tutti gli host della LAN"},
            {"testo": "d. Prevenire \"routing loops\" in reti LAN dove sono presenti cammini ridondanti tra irouter"}
        ],
        "risposta_corretta": "b. Prevenire \"switching loops\" ni reti LAN dove sono presenti cammini ridondanti tra gli switch"
    },
    {
        "esame": "Febbraio d6",
        "testo_domanda": "Siamo date el 4 stringhe di 4 bit riportate di seguito: b1) 1001; b2) 1011; b3) 0110; b4) 1010. Qual e al parola di codice calcolata mediante l'internet checksum?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. 1 0 0 1"},
            {"testo": "b. 0 1 1 0"},
            {"testo": "c. 1 1 1 1"}
        ],
        "risposta_corretta": "a. 1 0 0 1"
    },
    {
        "esame": "Febbraio d7",
        "testo_domanda": "Quale tabella viene consultata per mappare un indirizzo IP noto con un indirizzo MAC sconosciuto?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. La tabella di inoltro di uno switch"},
            {"testo": "b. La tabella ARP"},
            {"testo": "c. La tabella RARP"},
            {"testo": "d. La tabella di routing"}
        ],
        "risposta_corretta": "b. La tabella ARP"
    },
    {
        "esame": "Febbraio d8",
        "testo_domanda": "In una rete CDMA/CD la massima distanza tra due stazioni è di 2000 m. Qual è lil minimo tempo di tramissione di una trama se la velocità di propagazione sul mezzo è di 4 * 10^4 m/sec?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. 0,1s"},
            {"testo": "b. 2s"},
            {"testo": "c. 0,05s"}
        ],
        "risposta_corretta": "a. 0,1s"
    },
    {
        "esame": "Febbraio d9",
        "testo_domanda": "Con riferimento all'operazione di multiplazione dinamica di Unità Infromative (UI) su un canale condiviso :",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. non si verificano mai contese di utilizzazione"},
            {"testo": "b. si possono verificare contese di utilizzazione quando li canale multiplato è impegnato equindi non disponibile per li trasferimento immediato di una Ul"},
            {"testo": "c. e contese di utilizzazione si possono verificare solo se ibuffer di multiplazione non sono adeguatamente dimensionati"}
        ],
        "risposta_corretta": "b. si possono verificare contese di utilizzazione quando li canale multiplato è impegnato equindi non disponibile per li trasferimento immediato di una Ul"
    },
    {
        "esame": "Febbraio d10",
        "testo_domanda": "Lo schema di indirizzamento di livello 2 completamente non gerarchico delle LAN IEEE 802 (indirizzi a 48 bit) ha li principale vantaggio di:",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. rendere univoca l'identificazione dell'applicazione della stazione sulla LAN"},
            {"testo": "b. garantire l'univocità degli indirizzi delle interfacce delle stazioni e eliminare ogni necessità di configurazione di indirizzi."},
            {"testo": "c. rendere particolarmente efficiente l'instradamento delle trame MAC nelle tabelle degli switch"}
        ],
        "risposta_corretta": "b. garantire l'univocità degli indirizzi delle interfacce delle stazioni e eliminare ogni necessità di configurazione di indirizzi."
    },
    {
        "esame": "Febbraio d11",
        "testo_domanda": "Nell' indirizzamento in Internet la maschera di sotto-rete:",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. distingue tra indirizzi in forma binaria e in rappresentazione \"dotted\""},
            {"testo": "b. serve a rendere noto da ogni sistema in che modo li suo indirizzo PI è suddiviso tra net_id e host_id"},
            {"testo": "c. specifica la classe di indirizzamento che è stata adottata"}
        ],
        "risposta_corretta": "b. serve a rendere noto da ogni sistema in che modo li suo indirizzo PI è suddiviso tra net_id e host_id"
    },
    {
        "esame": "Febbraio d12",
        "testo_domanda": "Si consideri un protocollo di controllo d'errore di tipo Go-BACK-N. Sia: 1) ritardo di propogazione pari a 1/5 del tempo di tramissione di una trama; 2) il tempo di trasmissione dei riscontri pari a 3/5 del tempo di tramissione di una trama e l'eleborazione nei nodi trascurabile. Quanto deve essere la dimensione minima della finestra in emissione Ws affinche', se non si verificano errori, li trasmettitore sia in grado di tramettere trame continuamente (senza soluzione di continuita'). ",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Ws = 3"},
            {"testo": "b. Ws = 4"},
            {"testo": "c. Ws = 2"},
        ],
        "risposta_corretta": "c. Ws = 2"
    },
    {
        "esame": "Febbraio d13",
        "testo_domanda": "Con riferimento alla funzione di verifica di errore, si consideri li seguente codice polinomiale (CRC): \nx^5+X^4+X+1 \nQuesto polinomio:",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. è in grado di rivelare solo errori isolati di molteplicià dispari (1, 3, 5 errori)"},
            {"testo": "b. è in grado di rivelare stringhe di errore a raffica di lunghezza 5"},
            {"testo": "c. è in grado di rivelare solo errori isolati di molteplicià uguale a 5"}
        ],
        "risposta_corretta": "b. è in grado di rivelare stringhe di errore a raffica di lunghezza 5"
    },
    {
        "esame": "Febbraio d14",
        "testo_domanda": "Si supponga di avere un file di dimensione 40 kByte e di utilizzare una compressione con rapporto di compressione R=8. Se in una line che ha velocita' di V Mbit/s li file viene trasferito in meno di 0,8 ms, qual è la velocità Vdella linea?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. V=40 Mbit/s"},
            {"testo": "b. V=62,5 Mbit/s"},
            {"testo": "c. V=6,25 Mbit/s"},
            {"testo": "d. V=50 Mbit/s"}
        ],
        "risposta_corretta": "d. V=50 Mbit/s"
    },
    {
        "esame": "Febbraio d15",
        "testo_domanda": "Si consideri un brano musicale analogico di durata di 5 minuti con banda di 15 kHz, se lo si campiona con la frequenza di campionamento minima e si utilizzano 8 bit per ogni campione, qual è la lunghezza del brano digitalizzato risultante?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. 72Mbyte"},
            {"testo": "b. 36 Mbit/s"},
            {"testo": "c. 9Mbyte"}
        ],
        "risposta_corretta": "c. 9Mbyte"
    },
    
    # - Esame di Telecomunicazioni 2021 (sugli esercizi) - #
    {
        "esame": "2021 d1",
        "testo_domanda": "Dovendo trasmettere con una modulazione in banda traslata su un canale altamente rumoroso, è più efficiente",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Non esiste alcun legame tra i punti della costellazione utilizzata e gli effetti degli errori che si possono generare durante la trasmissione"},
            {"testo": "b. Utilizzare una costellazione ad un ridotto numero di punti per essere più"},
            {"testo": "c. Utilizzare una costellazione con un elevato numero di punti per essere più robusti nei confronti degli errori"}
        ],
        "risposta_corretta": "b. Utilizzare una costellazione ad un ridotto numero di punti per essere più"
    },
    {
        "esame": "2021 d2",
        "testo_domanda": "L’errore di quantizzazione derivante dal campionamento di un segnale analogico",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Può essere ridotto aumentando la frequenza di campionamento oltre al doppio della banda del segnale"},
            {"testo": "b. Dipende da fenomeni esterni (rumore, interferenza) che intervengono sul segnale campionato"},
            {"testo": "c. Può essere ridotto aumentando il numero di livelli di quantizzazione"}
        ],
        "risposta_corretta": "c. Può essere ridotto aumentando il numero di livelli di quantizzazione"
    },
    {
        "esame": "2021 d3",
        "testo_domanda": "Supponiamo di voler inviare un segnale digitale in un mezzo con banda Wc. Come possiamo aumentare il bit rate in trasmissione?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Mandando più di 2*Wc impulsi al secondo, compatibilmente con il rumore che si sommerà al segnale digitale."},
            {"testo": "b. Utilizzando impulsi che non generino interferenza intersimbolica."},
            {"testo": "c. Con una codifica multilivello che per ogni impulso codifica più bit contemporaneamente, compatibilmente con il rumore che si sommerà al segnale digitale."}
        ],
        "risposta_corretta": "c. Con una codifica multilivello che per ogni impulso codifica più bit contemporaneamente, compatibilmente con il rumore che si sommerà al segnale digitale."
    },
    {
        "esame": "2021 d4",
        "testo_domanda": "La trasmissione numerica in banda traslata si usa per:",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Collocare la trasmissione digitale in bande di frequenza ben identificate ed idonee alla trasmissione"},
            {"testo": "b. Aumentare il bit rate di trasmissione utilizzando frequenze portanti alte"},
            {"testo": "c. Rendere il segnale digitale più robusto nei confronti del rumore"}
        ],
        "risposta_corretta": "a. Collocare la trasmissione digitale in bande di frequenza ben identificate ed idonee alla trasmissione"
    },
    {
        "esame": "2021 d5",
        "testo_domanda": "I protocolli di strato di collegamento:",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Rendono affidabile la comunicazione tra estremo ad estremo"},
            {"testo": "b. Mirano a rendere affidabile la comunicazione sulle differenti sezioni di rete"},
            {"testo": "c. Si occupano esclusivamente di identificare le unità informative dello strato mediante tecniche di “framing”."}
        ],
        "risposta_corretta": "b. Mirano a rendere affidabile la comunicazione sulle differenti sezioni di rete"
    },
    {
        "esame": "2021 d6",
        "testo_domanda": "Le prestazioni dei meccanismi di rivelazione di errore di tipo CRC:",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Migliorano all’ aumentare della lunghezza del campo CRC ma non dipendono dal tipo di errori che si posso presentare nel collegamento"},
            {"testo": "b. Dipendono dal polinomio generatore adottato e dal tipo di errori che si posso presentare nel collegamento"},
            {"testo": "c. Peggiorano all’aumentare del grado del polinomio CRC"}
        ],
        "risposta_corretta": "b. Dipendono dal polinomio generatore adottato e dal tipo di errori che si posso presentare nel collegamento"
    },
    {
        "esame": "2021 d7",
        "testo_domanda": "I codici CRC vengono utilizzati",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. prevedendo un campo nell’intestazione dell’unità informativa da trasmettere dove memorizzare i coefficienti del polinomio resto della divisione tra il polinomio i cui coefficienti sono i bit da proteggere e il polinomio generatore"},
            {"testo": "b. prevedendo un campo nell’intestazione dell’unità informativa da trasmettere un campo dove memorizzare i coefficienti del polinomio generatore"},
            {"testo": "c. prevedendo un campo nell’intestazione dell’unità informativa da trasmettere dove memorizzare i coefficienti del polinomio quoziente della divisione tra il polinomio i cui coefficienti sono i bit da proteggere e il polinomio generatore"}
        ],
        "risposta_corretta": "a. prevedendo un campo nell’intestazione dell’unità informativa da trasmettere dove memorizzare i coefficienti del polinomio resto della divisione tra il polinomio i cui coefficienti sono i bit da proteggere e il polinomio generatore"
    },
    {
        "esame": "2021 d8",
        "testo_domanda": "Si considerino tre nodi che trasmettono in un modalità accesso multiplo slotted ALOHA. Data l’evoluzione temporale delle trasmissioni riportata in figura completando quello che accade sul mezzo condiviso, qual e’ la portata utile normalizzata nella finestra temporale F?",
        "immagine_domanda": path_immagine + "2021/8.png",
        "opzioni": [
            {"testo": "a. 0,6"},
            {"testo": "b. 0,13"},
            {"testo": "c. 0,4"}
        ],
        "risposta_corretta": "c. 0,4"
    },
    {
        "esame": "2021 d9",
        "testo_domanda": "Supponiamo di voler utilizzare un protocollo ARQ su un collegamento caratterizzato da una velocità di R bit/s. Se l’efficienza del protocollo in questa situazione e’ pari al 10% come ci aspettiamo che cambi se raddoppiamo il bit rate del collegamento, a parità degli altri parametri del sistema?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. diventerà del 5%"},
            {"testo": "b. diventerà del 20%"},
            {"testo": "c. non varia al variare di R se gli altri parametri rimangono invariati."}
        ],
        "risposta_corretta": "a. diventerà del 5%"
    },
    {
        "esame": "2021 d10",
        "testo_domanda": "In una rete in area locale che adotta la tecnologia IEEE 802.3, uno switch",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. apprende la struttura locale della rete (processo di learning) tramite l’indirizzo MAC di destinazione contenuto nell’intestazione delle trame"},
            {"testo": "b. apprende la struttura locale della rete (processo di learning) tramite l’indirizzo MAC di sorgente contenuto nell’intestazione delle trame"},
            {"testo": "c. apprende la struttura locale della rete (processo di learning) tramite l’indirizzo MAC di sorgente e di destinazione contenuto nell’intestazione delle trame"}
        ],
        "risposta_corretta": "b. apprende la struttura locale della rete (processo di learning) tramite l’indirizzo MAC di sorgente contenuto nell’intestazione delle trame"
    },
    {
        "esame": "2021 d11",
        "testo_domanda": "Quali sono gli elementi di una rete IP che effettuano la funzione di instradamento dei pacchetti?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. solo i router"},
            {"testo": "b. solo gli host"},
            {"testo": "c. gli host e i router"}
        ],
        "risposta_corretta": "c. gli host e i router"
    },
    {
        "esame": "2021 d12",
        "testo_domanda": "Perché il servizio offerto da una rete IP è detto \"best effort\"",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. perché in una rete IP l'instradamento dei datagrammi avviene scegliendo il cammino migliore"},
            {"testo": "b. perché una rete IP non offre alcun livello garantito di qualità nel trasferimento"},
            {"testo": "c. perché una rete IP assicura la migliore efficienza possibile nell'uso delle sue risorse"}
        ],
        "risposta_corretta": "b. perché una rete IP non offre alcun livello garantito di qualità nel trasferimento"
    },
    {
        "esame": "2021 d13",
        "testo_domanda": "Rispetto alla tecnica del Subnetting con maschere di lunghezza fissa, quella che impiega maschere di lunghezza variabile",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. risulta in generale più efficiente nell’assegnazione degli indirizzi"},
            {"testo": "b. non richiede alcuna modifica delle informazioni trasportate dal protocollo di routing"},
            {"testo": "c. risulta indipendente dal concetto di Classe"}
        ],
        "risposta_corretta": "b. non richiede alcuna modifica delle informazioni trasportate dal protocollo di routing"
    },
    {
        "esame": "2021 d14",
        "testo_domanda": "Qual è il numero massimo di sottoreti che in cui può essere suddivisa una rete a cui è stato assegnato un indirizzo di classe B utilizzando un prefissi di lunghezza 27 bit ?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. 8"},
            {"testo": "b. 32"},
            {"testo": "c. 2048"}
        ],
        "risposta_corretta": "a. 8"
    },
    {
        "esame": "2021 d15",
        "testo_domanda": "Supponendo che al terminale K sia stato assegnato l'indirizzo 195.213.15.246/27, a quale delle seguenti sottoreti appartiene il terminale?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. 195.213.15.224.0/27"},
            {"testo": "b. 195.213.15.0/24"},
            {"testo": "c. 195.213.15.240.0/27"}
        ],
        "risposta_corretta": "a. 195.213.15.224.0/27"
    },
    {
        "esame": "Quiz Capitolo 3 - 1",
        "testo_domanda": "Nel contesto dei protocolli di trasporto, cosa distingue il protocollo UDP dal TCP?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. UDP fornisce un servizio di trasmissione dati affidabile e orientato alla connessione."},
            {"testo": "b. UDP utilizza un meccanismo di controllo del flusso e di congestione."},
            {"testo": "c. UDP è un protocollo senza connessione che non garantisce la consegna dei pacchetti."},
            {"testo": "d. UDP esegue un handshake a tre vie per stabilire una connessione."}
        ],
        "risposta_corretta": "c. UDP è un protocollo senza connessione che non garantisce la consegna dei pacchetti."
    },
    {
        "esame": "Quiz Capitolo 3 - 2",
        "testo_domanda": "Considerando il protocollo TCP, quale affermazione descrive correttamente il meccanismo di controllo della congestione \"Slow Start\"?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Aumenta esponenzialmente la finestra di congestione dopo ogni ACK duplicato ricevuto."},
            {"testo": "b. Aumenta linearmente la finestra di congestione per ogni round trip time (RTT)."},
            {"testo": "c. Inizia con una piccola finestra di congestione e la aumenta esponenzialmente fino a un limite di soglia."},
            {"testo": "d. Mantiene costante la finestra di congestione fino a che non vengono rilevate perdite di pacchetti."}
        ],
        "risposta_corretta": "c. Inizia con una piccola finestra di congestione e la aumenta esponenzialmente fino a un limite di soglia."
    },
    {
        "esame": "GPT - Domande Avanzate su Strato di Trasporto e Protocolli - 1",
        "testo_domanda": """
            Data una connessione TCP in cui il valore della soglia è impostato a 64 KB, e la finestra di congestione iniziale è di 1 MSS (Maximum Segment Size). Assumendo che non ci siano perdite di segmenti e che ogni ACK è ricevuto in modo tempestivo, qual è la dimensione della finestra di congestione dopo aver ricevuto il terzo ACK?
            """,
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. 2 MSS"},
            {"testo": "b. 4 MSS"},
            {"testo": "c. 8 MSS"},
            {"testo": "d. 16 MSS"}
        ],
        "risposta_corretta": "c. 8 MSS"
    },
    {
        "esame": "GPT - Domande Avanzate su Strato di Trasporto e Protocolli - 2",
        "testo_domanda": "Considerando un ambiente di rete che utilizza il protocollo UDP, quale delle seguenti affermazioni è vera riguardo alla trasmissione di segmenti UDP?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Il destinatario può rilevare segmenti persi tramite numeri di sequenza."},
            {"testo": "b. Il mittente riceve conferme di ricezione per ogni segmento inviato."},
            {"testo": "c. Il destinatario non può rilevare segmenti duplicati senza meccanismi aggiuntivi."},
            {"testo": "d. I segmenti UDP sono sempre consegnati in ordine."}
        ],
        "risposta_corretta": "c. Il destinatario non può rilevare segmenti duplicati senza meccanismi aggiuntivi."
    },
    {
        "esame": "GPT - Domande Avanzate su Strato di Trasporto e Protocolli - 3",
        "testo_domanda": "Se un segmento TCP contiene 20 byte di intestazione e 1460 byte di payload, qual è l'efficienza del protocollo TCP in questo caso (rapporto tra payload e dimensione totale del segmento)?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. 88.41%"},
            {"testo": "b. 93.55%"},
            {"testo": "c. 98.65%"},
            {"testo": "d. 86.73%"}
        ],
        "risposta_corretta": "a. 88.41%"
    },
    {
        "esame": "GPT - Domande Avanzate su Strato di Rete e Indirizzamento - 1",
        "testo_domanda": "Considerando una rete IP con un prefisso /26, quale è il numero massimo di indirizzi IP utilizzabili per gli host in questa sottorete?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. 62"},
            {"testo": "b. 64"},
            {"testo": "c. 126"},
            {"testo": "d. 128"}
        ],
        "risposta_corretta": "a. 62"
    },
    {
        "esame": "Primo Test - d1",
        "testo_domanda": "Che cosa si intende nella commutazione di pacchetto con \"Store and Forward\"?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Una tecnica attraverso cui la rete prima di trasmettere una pacchetto memeorizza il percorso che questo deve fare."},
            {"testo": "b. Una tecnica che prevede che un pacchetto di dati sia completamente ricevuto in un router prima di iniziarne la ritrasmissione"},
            {"testo": "c. Una modalità di accodamento che prevede che il primo pacchetto che arriva in un router sia il primo ad essere ritrasmesso"}
        ],
        "risposta_corretta": "b. Una tecnica che prevede che un pacchetto di dati sia completamente ricevuto in un router prima di iniziarne la ritrasmissione"
    },
    {
        "esame": "Primo Test - d2",
        "testo_domanda": "Il meccanismo di attraversamento di una rete in modalità Circuit Switching:",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Introduce un ritardo elevanto per attraversare i nodi della rete"},
            {"testo": "b. Permette di avere risorse dedicate per la specifica comunicazione"},
            {"testo": "c. Aumenta di molto il numero di comunicazioni che contemporaneamente possono utilizzare la rete"}
        ],
        "risposta_corretta": "b. Permette di avere risorse dedicate per la specifica comunicazione"
    },
    {
        "esame": "Primo Test - d3",
        "testo_domanda": 
"""
            Si consideri la seguente configurazione di rete con tre comunicazioni che si dividono una banda R. Assumendo che la comunicazione tra
            E e F ottenga sul canale condiviso una banda pari a R/2 e le altre due si dividono equamente la banda rimanente.
            Siano Rs=1 Mbit/s, Rc=2 Mbit/s e R=20 Mbit/s.
            Quale delle tre comunicazioni ha il throughput maggiore?
""",
        "immagine_domanda": path_immagine + "test1/d3.png",
        "opzioni": [
            {"testo": "a. Nessuna delle tre. Hanno tutte lo stesso throughput"},
            {"testo": "b. Le due comunicazioni A-B e C-D"},
            {"testo": "c. La comunicazione E-F"}
        ],
        "risposta_corretta": "a. Nessuna delle tre. Hanno tutte lo stesso throughput"
    },
    {
        "esame": "Primo Test - d4",
        "testo_domanda": "In una procedura di recupero d’errore Go-Back-N si adotta una finestra in emissione che ha larghezza 3. Il trasmittente (A) ha sempre pacchetti da trasmettere. Ricordando la convenzione con cui il ricevitore con l'ACK chiede direttamente il prossimo numero di sequenza che si aspetta di ricevere e supponendo che lato emittente la finestra abbia in un dato istante limite inferiore uguale a 4, come reagisce A ricevendo dal ricevente (B) un ACK con numero 6?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Trasmette il pacchetto 6 e non fa altre azioni"},
            {"testo": "b. Aggiorna il limite inferiore della finestra al valore 6 e trasmette i pacchetti 7 e 8"},
            {"testo": "c. Aggiorna il limite inferiore della finestra al valore 6 e trasmette i pacchetti 5-8"}
        ],
        "risposta_corretta": "b. Aggiorna il limite inferiore della finestra al valore 6 e trasmette i pacchetti 7 e 8"
    },
    {
        "esame": "Primo Test - d5",
        "testo_domanda": "Quanti pacchetti di dimensione 50 byte possiamo trovare contemporanemente in \"volo\" su un mezzo tramissivo lungo 20 Km che tramestte a bit rate C=60 Mbit/s e la cui velocità di propagazione è pari a quella della luce nel vuoto (3*10^8",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. 80"},
            {"testo": "b. 10"},
            {"testo": "c. 2000"}
        ],
        "risposta_corretta": "b. 10"
    },
    {
        "esame": "Primo Test - d6",
        "testo_domanda": "Un’applicazione residente nell'host A scambia dati con due altre applicazioni residenti in host distinti B e C, in quale modo l'host A distingue le due connessioni TCP utilizzate",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. dai diversi valori dei relativi socket e, in particolare, dai diversi valori dei numeri di porta assegnati per indirizzare le applicazioni dagli host B e C"},
            {"testo": "b. non e' in grado di distinguerle a livello TCP"},
            {"testo": "c. dai diversi valori dei relativi socket e, in particolare, dai diversi valori degli indirizzi IP dei due host B e C"}
        ],
        "risposta_corretta": "c. dai diversi valori dei relativi socket e, in particolare, dai diversi valori degli indirizzi IP dei due host B e C"
    },
    {
        "esame": "Primo Test - d7",
        "testo_domanda": "Si consideri un protocollo di controllo d’errore di tipo Go-BACK-N. Sia: 1) ritardo di propogazione pari a 1/5 del tempo di tramissione di un pacchetto; 2) il tempo di trasmissione dei riscontri pari a 3/5 del tempo di tramissione di un pacchetto e l’eleborazione nei nodi trascurabile. Quanto deve essere la dimensione minima della finestra in emissione N affinche’, se non si verificano errori, il trasmettitore sia in grado di tramettere pacchetti continuamente (senza soluzione di continuita’).",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. N=4"},
            {"testo": "b. N=2"},
            {"testo": "c. N=3"}
        ],
        "risposta_corretta": "b. N=2"
    },
    {
        "esame": "Primo Test - d8",
        "testo_domanda": "Si consideri il seguente schema. Quante volte un datagramma viene INCAPSULATO in un frame nel percorso di un messaggio M dall'origine alla destinazione?",
        "immagine_domanda": path_immagine + "/test1/d8.png",
        "opzioni": [
            {"testo": "a. 4"},
            {"testo": "b. 2"},
            {"testo": "c. 1"}
        ],
        "risposta_corretta": "b. 2"
    },
    {
        "esame": "Primo Test - d9",
        "testo_domanda": "Per quale motivo nei protocolli di trasferimento dati affidabili è necessario aggiungere i numeri di sequenza?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Per permettere a chi trasmette di accorgersi di eventuali pacchetti persi quando si riceve un ACK che chiede un pacchetto con numero di sequenza differente da quello per cui si aspetta il riscontro."},
            {"testo": "b. Per permettere a chi riceve sia di accorgersi di eventuali pacchetti duplicati che di pacchetti persi."},
            {"testo": "c. Per permettere a chi trasmettere di controllare la sequanza dei pacchetti tramessi."}
        ],
        "risposta_corretta": "b. Per permettere a chi riceve sia di accorgersi di eventuali pacchetti duplicati che di pacchetti persi."
    },
    {
        "esame": "Primo Test - d10",
        "testo_domanda": "Si considerino due terminali interconnessi attraverso una catena di 3 nodi intermedi che trasmettono, nella modalità a pacchetto, un file suddiviso in 3 pacchetti. Considerando trascurabili i tempi di propagazione e di accodamento se la trasmissione di un pacchetto su un'interfaccia richiede 2 secondi, quanto tempo si impiega per trasferire tutto il file?\nScegli un'alternativa:",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. 12 secondi"},
            {"testo": "b. 9 secondi"},
            {"testo": "c. 2 secondi"},
            {"testo": "d. 24 secondi"}
        ],
        "risposta_corretta": "a. 12 secondi"
    },
    {
        "esame": "Test 2 - d1",
        "testo_domanda": "Un’entità TCP A apre la procedura di instaurazione di una connessione con un Initial Sequenze Number (ISN)=15028; la controparte B replica con un ISN=274. Quali sono i contenuti dei due campi Sequence Number (SN) e Acknowledgment Number (AN) nel segmento emesso dall’entità A per concludere la procedura (terzo segmento nella procedura di instaurazione della connessione)?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. SN=15028 e AN 275"},
            {"testo": "b. SN=15029 e AN 274"},
            {"testo": "c. SN=15029 e AN 275"}
        ],
        "risposta_corretta": "c. SN=15029 e AN 275"
    },
    {
        "esame": "Test 2 - d2",
        "testo_domanda": "Dato il segnale x(t) con trasformata di Fourier X(f) rappresentata in figura, qual è il massimo intervallo di campionamento (Ts) per avere una perfetta ricostruzione del segnale?",
        "immagine_domanda": path_immagine + "test2/d2.png",
        "opzioni": [
            {"testo": "a. 1 ms"},
            {"testo": "b. 0,1 ms"},
            {"testo": "c. 3 ms"},
            {"testo": "d. 0,2 ms"}
        ],
        "risposta_corretta": "b. 0,1 ms"
    },
    {
        "esame": "Test 2 - d3",
        "testo_domanda": 
"""
Un router, la cui routing table è riportata sotto, riceve un pacchetto il cui indirizzo di destinazione è 10.0.1.171. Indicare su quale interfaccia di uscita viene rilanciato il pacchetto

Prefisso di sottorete Interfaccia di uscita
10.0.0.0/8 1
10.0.1.0/24 2
10.0.1.0/25 3
10.0.1.128/27 4
""",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. 1"},
            {"testo": "b. 3"},
            {"testo": "c. 4"},
            {"testo": "d. 2"}
        ],
        "risposta_corretta": "d. 2"
    },
    {
        "esame": "Test 2 - d4",
        "testo_domanda": "Il Dynamic Host Configuration Protocol (DHCP) è un servizio \"plug and play\", in cui\n\nScegli un'alternativa:",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. il client deve preventivamente scoprire l'indirizzo IP del server DHCP"},
            {"testo": "b. per quanto riguarda i messaggi inviati dalle parti, prevede sempre l'utilizzo dell'indirizzo broadcast come destination address"},
            {"testo": "c. una volta ricevuto un messaggio di \"DHCP offer\" da parte del server, a questo punto il client ne apprende l'indirizzo IP che verrà successivamente utilizzato per inviare il messaggio di \"DHCP request\""}
        ],
        "risposta_corretta": "b. per quanto riguarda i messaggi inviati dalle parti, prevede sempre l'utilizzo dell'indirizzo broadcast come destination address"
    },
    {
        "esame": "Test 2 - d5",
        "testo_domanda": "In una rete caratterizzata dal prefisso 151.168.0.0/23, quanti host possono essere indirizzati al massimo (escludendo indirizzo broadcast e indirizzo tutti \"0\")?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. 254"},
            {"testo": "b. 1022"},
            {"testo": "c. 510"}
        ],
        "risposta_corretta": "c. 510"
    },
    {
        "esame": "Test 2 - d6",
        "testo_domanda": "In uno schema di indirizzamento classless sia dato il seguente indirizzo di rete IP 151.100.64.0/18\nQuale tra i seguenti e' l'indirizzo broadcast di questa sottorete?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. 151.100.64.255"},
            {"testo": "b. 151.100.255.255"},
            {"testo": "c. 151.100.127.255"}
        ],
        "risposta_corretta": "c. 151.100.127.255"
    },
    {
        "esame": "Test 2 - d7",
        "testo_domanda": "Indicare quanti blocchi di classe C sono aggregati dal prefisso 192.168.64.0/21",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. 4"},
            {"testo": "b. 16"},
            {"testo": "c. 2"},
            {"testo": "d. 8"}
        ],
        "risposta_corretta": "d. 8"
    },
    {
        "esame": "Test 2 - d8",
        "testo_domanda": "Due sistemi terminali stanno scambiando messaggi utilizzando una connessione TCP versione Tahoe. Al tempo T=10 secondi, istante in cui si verifica un evento di RTO ( Retransmission Time Out), la congestion window ha una dimensione pari a 36 MSS. Assumendo che l’RTT è costante e pari a 100 millisecondi, indicare la dimensione della congestion window all’istante T1=10,3 secondi",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. 4 MSS"},
            {"testo": "b. 3 MSS"},
            {"testo": "c. 21 MSS"},
            {"testo": "d. 18 MSS"}
        ],
        "risposta_corretta": "a. 4 MSS"
    },
    {
        "esame": "Test 2 - d9",
        "testo_domanda": "L'host A invia tre segmenti TCP all'host B, aventi lunghezza rispettivamente 100 Byte, 134 Byte e 78 Byte. Supponendo che il secondo segmento si perda, indicare il valore assunto dall'ultimo dei messaggi di ACK mostrato nella figura.",
        "immagine_domanda": path_immagine + "test2/d9.png",
        "opzioni": [
            {"testo": "a. 434"},
            {"testo": "b. 200"},
            {"testo": "c. 312"},
            {"testo": "d. 512"},
            {"testo": "e. 300"}
        ],
        "risposta_corretta": "e. 300"
    },
    {
        "esame": "Test 2 - d10",
        "testo_domanda": "Si consideri il grafo mostrato in figura. Con riferimento all'esecuzione dell'algoritmo di Dijkstra con radice nel nodo A, si indichi quale nodo viene visitato all'iterazione numero 4",
        "immagine_domanda": path_immagine + "test2/d10.png",
        "opzioni": [
            {"testo": "a. C"},
            {"testo": "b. D"},
            {"testo": "c. B"},
            {"testo": "d. F"},
            {"testo": "e. E"}
        ],
        "risposta_corretta": "a. C"
    },
    {
        "esame": "GPT - Quiz t_segnali - 1",
        "testo_domanda": "Qual è la trasformata di Fourier di un segnale rappresentato dalla funzione rettangolare rect(t/T)?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. T * sinc(pi*f*T)"},
            {"testo": "b. T * e^{-j2*pi*f*t}"},
            {"testo": "c. (T/2) * sinc(2*pi*f*T)"},
            {"testo": "d. T * cos(pi*f*T)"}
        ],
        "risposta_corretta": "a. T * sinc(pi*f*T)"
    },
    {
        "esame": "GPT - Quiz t_segnali - 2",
        "testo_domanda": "Se un segnale x(t) è reale e pari, come sarà la sua trasformata di Fourier X(f)?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Reale e dispari"},
            {"testo": "b. Immaginaria e pari"},
            {"testo": "c. Reale e pari"},
            {"testo": "d. Immaginaria e dispari"}
        ],
        "risposta_corretta": "c. Reale e pari"
    },
    {
        "esame": "GPT - Quiz t_segnali - 2",
        "testo_domanda": "",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. "},
            {"testo": "b. "},
            {"testo": "c. "},
            {"testo": "d. "}
        ],
        "risposta_corretta": ""
    },
    {
        "esame": "GPT - Quiz t_segnali - 3",
        "testo_domanda": "Considerando la dualità della trasformata di Fourier, se x(t) <-> X(f), quale delle seguenti coppie è corretta?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. x(f) <-> X(t)"},
            {"testo": "b. x(-f) <-> X(-t)"},
            {"testo": "c. x(f) <-> X(-t)"},
            {"testo": "d. x(-t) <-> X(f)"}
        ],
        "risposta_corretta": "a. x(f) <-> X(t)"
    },
    {
        "esame": "GPT - Quiz t_segnali - 4",
        "testo_domanda": "Cosa accade se la frequenza di campionamento è inferiore al doppio della frequenza massima del segnale?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Il segnale può essere ricostruito senza alcuna distorsione."},
            {"testo": "b. Si verifica il fenomeno dell'aliasing."},
            {"testo": "c. La banda del segnale viene espansa."},
            {"testo": "d. Il segnale viene amplificato."}
        ],
        "risposta_corretta": "b. Si verifica il fenomeno dell'aliasing."    
    },
    {
        "esame": "GPT - Quiz t_segnali - 5",
        "testo_domanda": "In un sistema di campionamento, cosa si intende per filtro anti-aliasing?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Un filtro che aumenta la banda del segnale."},
            {"testo": "b. Un filtro che rimuove le frequenze superiori a quella di Nyquist."},
            {"testo": "c. Un filtro che converte il segnale analogico in digitale."},
            {"testo": "d. Un filtro che corregge gli errori introdotti dal campionatore."}
        ],
        "risposta_corretta": "b. Un filtro che rimuove le frequenze superiori a quella di Nyquist."    
    },
    {
        "esame": "GPT - Quiz t_segnali - 6",
        "testo_domanda": "Qual è la condizione necessaria affinché un segnale limitato in banda con frequenza massima fm possa essere perfettamente ricostruito dopo il campionamento?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. La frequenza di campionamento Fs deve essere uguale a fm."},
            {"testo": "b. La frequenza di campionamento Fs deve essere maggiore di 2 * fm."},
            {"testo": "c. La frequenza di campionamento Fs deve essere inferiore a fm."},
            {"testo": "d. La frequenza di campionamento Fs non è rilevante per la ricostruzione del segnale."}
        ],
        "risposta_corretta": "b. La frequenza di campionamento Fs deve essere maggiore di 2 * fm."    
    },
    {
        "esame": "GPT - Quiz t_segnali - 7",
        "testo_domanda": "Nello studio del segnale, il concetto di \"spettro\" si riferisce a:",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. La distribuzione dell'energia del segnale nel tempo."},
            {"testo": "b. La distribuzione dell'ampiezza del segnale in funzione della frequenza."},
            {"testo": "c. Il numero totale di armoniche in un segnale periodico."},
            {"testo": "d. La fase del segnale in funzione del tempo."}
        ],
        "risposta_corretta": "b. La distribuzione dell'ampiezza del segnale in funzione della frequenza."    
    },
    {
        "esame": "GPT - Quiz t_segnali - 8",
        "testo_domanda": "Il teorema di Parseval in teoria dei segnali afferma che:",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. L'energia totale di un segnale nel dominio del tempo è uguale all'energia nel dominio della frequenza."},
            {"testo": "b. La potenza di un segnale nel dominio del tempo è sempre maggiore di quella nel dominio della frequenza."},
            {"testo": "c. L'ampiezza di un segnale è massima nel dominio della frequenza."},
            {"testo": "d. La frequenza di un segnale non può essere determinata dal suo spettro."}
        ],
        "risposta_corretta": "a. L'energia totale di un segnale nel dominio del tempo è uguale all'energia nel dominio della frequenza."    
    },
    {
        "esame": "GPT - Quiz t_segnali - 9",
        "testo_domanda": "In un segnale, la \"correlazione\" viene utilizzata per:",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Misurare il grado di somiglianza tra due segnali diversi."},
            {"testo": "b. Calcolare la frequenza fondamentale del segnale."},
            {"testo": "c. Stabilire la banda di frequenza occupata dal segnale."},
            {"testo": "d. Determinare l'ampiezza massima del segnale."}
        ],
        "risposta_corretta": "a. Misurare il grado di somiglianza tra due segnali diversi."    
    },
    {
        "esame": "GPT - Quiz t_segnali arg6 - 1",
        "testo_domanda": "Qual è la principale applicazione dei filtri in un sistema di comunicazione?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Amplificare il segnale."},
            {"testo": "b. Modulare il segnale."},
            {"testo": "c. Eliminare le frequenze indesiderate dal segnale."},
            {"testo": "d. Convertire il segnale da analogico a digitale."}
        ],
        "risposta_corretta": "c. Eliminare le frequenze indesiderate dal segnale."    
    },
    {
        "esame": "GPT - Quiz t_segnali arg6 - 2",
        "testo_domanda": "Un filtro passa-basso ideale è caratterizzato da:",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Lasciar passare tutte le frequenze superiori a una certa soglia."},
            {"testo": "b. Lasciar passare solo le frequenze inferiori a una certa soglia."},
            {"testo": "c. Lasciar passare solo una specifica banda di frequenze."},
            {"testo": "d. Bloccare tutte le frequenze del segnale."}
        ],
        "risposta_corretta": "b. Lasciar passare solo le frequenze inferiori a una certa soglia."    
    },
    {
        "esame": "GPT - Quiz t_segnali arg6 - 3",
        "testo_domanda": "Qual è l'effetto della convoluzione di un segnale con la risposta impulsiva di un filtro?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Cambiare la fase del segnale."},
            {"testo": "b. Modificare l'ampiezza del segnale."},
            {"testo": "c. Filtrare il segnale secondo la caratteristica del filtro."},
            {"testo": "d. Convertire il segnale da frequenza a tempo."}
        ],
        "risposta_corretta": "c. Filtrare il segnale secondo la caratteristica del filtro."    
    },
    {
        "esame": "GPT - Quiz t_segnali arg45 - 1",
        "testo_domanda": "La convoluzione di due segnali serve a:",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Trovare la somma dei due segnali."},
            {"testo": "b. Trovare il prodotto dei due segnali in un punto specifico."},
            {"testo": "c. Calcolare la risposta di un sistema lineare a un segnale di ingresso."},
            {"testo": "d. Misurare la somiglianza tra i due segnali."}
        ],
        "risposta_corretta": "c. Calcolare la risposta di un sistema lineare a un segnale di ingresso."    
    },
    {
        "esame": "GPT - Quiz t_segnali arg45 - 2",
        "testo_domanda": "In un sistema di comunicazione, il filtro è utilizzato per:",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Modulare il segnale trasmesso."},
            {"testo": "b. Amplificare il segnale ricevuto."},
            {"testo": "c. Eliminare o ridurre le frequenze indesiderate dal segnale."},
            {"testo": "d. Convertire il segnale da analogico a digitale."}
        ],
        "risposta_corretta": "c. Eliminare o ridurre le frequenze indesiderate dal segnale."    
    },
    {
        "esame": "GPT - Quiz t_segnali arg45 - 3",
        "testo_domanda": "Cosa misura la correlazione tra due segnali?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. La potenza combinata dei due segnali."},
            {"testo": "b. Il grado di somiglianza o relazione tra i due segnali."},
            {"testo": "c. La differenza di fase tra i due segnali."},
            {"testo": "d. L'ampiezza massima dei due segnali combinati."}
        ],
        "risposta_corretta": "b. Il grado di somiglianza o relazione tra i due segnali."    
    },
    {
        "esame": "GPT - Quiz t_segnali arg8 - 1",
        "testo_domanda": "Qual è lo scopo principale dell'utilizzo della trasformata di Fourier in analisi dei segnali?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Misurare la potenza del segnale."},
            {"testo": "b. Analizzare le componenti frequenziali del segnale."},
            {"testo": "c. Determinare la durata del segnale."},
            {"testo": "d. Calcolare la velocità di trasmissione del segnale."}
        ],
        "risposta_corretta": "b. Analizzare le componenti frequenziali del segnale."    
    },
    {
        "esame": "GPT - Quiz t_segnali arg9 - 1",
        "testo_domanda": "Un segnale x(t) ha una frequenza massima di 20kHz. Qual è il massimo intervallo di campionamento per avere una perfetta ricostruzione del segnale?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. 25 µs"},
            {"testo": "b. 50 µs"},
            {"testo": "c. 100 µs"},
            {"testo": "d. 200 µs"}
        ],
        "risposta_corretta": "b. 50 µs"   
    },
    {
        "esame": "GPT - Quiz t_segnali arg9 - 2",
        "testo_domanda": "Dato il segnale x(t)=3cos(24)-sin(23), quanti campioni devono essere presi su un intervallo di 5 s per soddisfare il teorema del campionamento?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. 100 campioni"},
            {"testo": "b. 200 campioni"},
            {"testo": "c. 500 campioni"},
            {"testo": "d. 1000 campioni"}
        ],
        "risposta_corretta": "d. 1000 campioni"   
    },
    {
        "esame": "GPT - Quiz t_segnali arg9 - 3",
        "testo_domanda": "Qual è la condizione necessaria affinché un segnale limitato in banda con frequenza massima f_m possa essere perfettamente ricostruito dopo il campionamento?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. La frequenza di campionamento F_s deve essere uguale a f_m."},
            {"testo": "b. La frequenza di campionamento F_s deve essere maggiore di 2f_m."},
            {"testo": "c. La frequenza di campionamento F_s deve essere inferiore a f_m."},
            {"testo": "d. La frequenza di campionamento F_s non è rilevante per la ricostruzione del segnale."}
        ],
        "risposta_corretta": "b. La frequenza di campionamento F_s deve essere maggiore di 2f_m."   
    },
    {
        "esame": "GPT - Quiz t_segnali arg9 - 4",
        "testo_domanda": "Cosa accade se la frequenza di campionamento è inferiore al doppio della frequenza massima del segnale?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Il segnale può essere ricostruito senza alcuna distorsione."},
            {"testo": "b. Si verifica il fenomeno dell'aliasing."},
            {"testo": "c. La banda del segnale viene espansa."},
            {"testo": "d. Il segnale viene amplificato."}
        ],
        "risposta_corretta": "b. Si verifica il fenomeno dell'aliasing."   
    },
    {
        "esame": "GPT - Quiz t_segnali arg9 - 5",
        "testo_domanda": "In un sistema di campionamento, cosa si intende per filtro anti-aliasing?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Un filtro che aumenta la banda del segnale."},
            {"testo": "b. Un filtro che rimuove le frequenze superiori a quella di Nyquist."},
            {"testo": "c. Un filtro che converte il segnale analogico in digitale."},
            {"testo": "d. Un filtro che corregge gli errori introdotti dal campionatore."}
        ],
        "risposta_corretta": "b. Un filtro che rimuove le frequenze superiori a quella di Nyquist."   
    },
    {
        "esame": "GPT - Quiz t_segnali arg10 - 1",
        "testo_domanda": "Il segnale audio ha una banda di circa 40 kHz. Per metterlo su CD, campionato a 441 kHz e codificato con 16 bit, qual è la frequenza di bit?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. 7.056 Mbps"},
            {"testo": "b. 14.112 Mbps"},
            {"testo": "c. 1.764 Mbps"},
            {"testo": "d. 3.528 Mbps"}
        ],
        "risposta_corretta": "a. 7.056 Mbps"   
    },
    {
        "esame": "GPT - Quiz t_segnali arg10 - 2",
        "testo_domanda": "Un segnale audio di 3 minuti, campionato a 441 kHz e quantizzato con 512 intervalli. Qual è la dimensione del segnale in bit?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. 423.36 Mbit"},
            {"testo": "b. 846.72 Mbit"},
            {"testo": "c. 211.68 Mbit"},
            {"testo": "d. 1693.44 Mbit"}
        ],
        "risposta_corretta": "a. 423.36 Mbit"   
    },
    {
        "esame": "GPT - Quiz t_segnali arg10 - 3",
        "testo_domanda": "Con un segnale audio di 40 kHz, campionato a 50 kHz e 1024 intervalli di quantizzazione, qual è la durata massima del segnale che si può salvare su un Hard-Disk di 500 MB?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Circa 20 minuti"},
            {"testo": "b. Circa 40 minuti"},
            {"testo": "c. Circa 10 minuti"},
            {"testo": "d. Circa 30 minuti"}
        ],
        "risposta_corretta": ""   
    },
    {
        "esame": "GPT - Quiz t_segnali arg10 - 4",
        "testo_domanda": "Per un CD audio che contiene segnali stereo campionati a 441 kHz, qual è la durata massima del segnale audio che può contenere 750 MB?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. Circa 80 minuti"},
            {"testo": "b. Circa 120 minuti"},
            {"testo": "c. Circa 60 minuti"},
            {"testo": "d. Circa 100 minuti"}
        ],
        "risposta_corretta": "a. Circa 80 minuti"   
    },
    {
        "esame": "GPT - Quiz t_segnali arg10 - 5",
        "testo_domanda": "Un segnale x(t) ha una frequenza massima di 35 Hz. A quale frequenza deve essere campionato correttamente il segnale?",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. 70 Hz"},
            {"testo": "b. 35 Hz"},
            {"testo": "c. 100 Hz"},
            {"testo": "d. 50 Hz"}
        ],
        "risposta_corretta": "a. 70 Hz"   
    },
    
'''
    {
        "esame": "",
        "testo_domanda": "",
        "immagine_domanda": None,
        "opzioni": [
            {"testo": "a. "},
            {"testo": "b. "},
            {"testo": "c. "},
            {"testo": "d. "}
        ],
        "risposta_corretta": ""
    },
    
'''
]

# ------------- Dati esercizio -------------#
dati_esercizi = [
    {
        "esame": "2021",
        "testo_domanda": "Si consideri una sorgente informativa a ritmo binario variabile (VBR) che trasmette in periodi temporali di durata 10 ms l’uno un numero di byte in accordo a quanto riportato nel seguente grafico (che rappresenta 9 periodi da 10 ms consecutivi, periodo totale 90 ms). Supponendo che questa sorgente dati debba essere trasferita attaverso una linea a velocita’ di 6 Mbit/s si chiede di:\n1. Calcolare il bit rate medio e di picco della sorgente in esame. \n2. Determinare il numero massimo di sorgenti di questo tipo che possono essere multiplate sulla linea se si adottasse un criterio di multiplazione su base banda di picco.\n3. Qual e’ il rendimento di utilizzazione della linea se si multiplano un numero di sorgerti pari a quelle derivate in 2) ma utilizzando un criterio di multiplazione su base banda media?",
        "immagine_domanda": path_immagine + "2021/esercizio.png",
        "soluzione": None,
        "immagine_soluzione": None
    },
    {
        "esame": "Esercizi Go-Back-N",
        "testo_domanda": "Si consideri un canale via satellite della capacità di 1 Mb/s. Considerando che il tempo di propagazione attraverso un satellite geostazionario richiede 250 ms, si chiede di dimensionare la minima finestra di trasmissione di un protocollo Go-BACK-N (con time-out) in modo che sia consentita la massima efficienza temporale del canale quando vengano trasmesse trame di 2000 bit in assenza di errori. Si suppongano gli ACK trascurabili. \nSi calcoli poi la massima efficienza trasmissiva che si avrebbe nel caso in cui il meccanismo ARQ fosse di tipo STOP and WAIT.",
        "immagine_domanda": None,
        "soluzione": """
            - Soluzione -

            # Caso Go-Back-N

            Per massimizzare l'efficienza nel caso Go-Back-N, il numero di pacchetti (N) nella finestra deve coprire il tempo di andata e ritorno del primo pacchetto.

            Indicati con:

            T = 2 ms (tempo di trasmissione di un pacchetto)
            τ = 250 ms (tempo di propagazione)

            La condizione per la massima efficienza è:

            NT ≥ T + 2τ → 1 + 2(τ / T) = 1 + 2 * (250 / 2) = 251

            Quindi, per finestre N ≥ 251, la trasmissione risulta continua e l'efficienza del meccanismo è 1.

            # Caso Stop&Wait

            [Inserimento dell'immagine]

            L’efficienza del meccanismo Stop&Wait è calcolata come:

            η = T / (T + 2τ) = 1 / 251
            """,
        "immagine_soluzione": None
    },
    {
        "esame": "Multiplazione Statica",
        "testo_domanda": """
            Si consideri uno schema di multiplazione statica a divisione di tempo con asse dei tempi suddiviso in Intervalli Temporali (IT) ed organizzazione in trama. Ciascuna trama ha una durata di 125 µs ed è costituita da 24 IT, dei quali uno destinato alla sincronizzazione delle trame. Ogni IT è costituito da 8 bit suddivisi in 7 bit per l'informazione utente ed 1 bit per la segnalazione associata al canale d’utente. Si supponga di dover multipare flussi audio a ritmo binario variabile (VBR) caratterizzati da un ritmo binario di picco Rp=192 kbit/s e da un ritmo binario medio Rm=150 kbit/s.

            Si chiede di calcolare:

            1. la capacità complessiva del canale multiplato;
            2. la capacità complessiva di ciascun sub-canale di base;
            3. la capacità del canale di segnalazione associato a ciascun sub-canale di base;
            4. la capacità complessiva dedicata alla sincronizzazione delle trame;
            5. il numero massimo di flussi audio VBR multiplabili sulla linea e la corrispondente efficienza media di multiplazione.
            """,
        "immagine_domanda": None,
        "soluzione": """
            - Soluzione -
            1. Capacità complessiva del canale multiplato.
            La capacità complessiva del canale multiplato (Cm) è data dal rapporto tra il numero di bit totali emessi in una trama e la durata temporale della trama stessa. Si ha quindi:

            Cm = (#IT in una trama) * (#bit in un IT) / durata trama = 248 bit / 125 µs
            Cm = 1536 kbit/s.

            2. Capacità complessiva di ciascun sub-canale di base.

            Un sub-canale di base è costituito da un IT ripetuto a cadenza di trama. La relativa capacità (Cs) è data dal rapporto tra il numero di bit in un IT e la durata temporale della trama. Si ha quindi:

            3. Capacità del canale di segnalazione associato a ciascun sub-canale di base.

            Ciascun sub-canale di base è in grado di trasferire in ogni trama un bit per l’informazione di segnalazione. Questo bit è inserito nell’IT insieme ai sette bit utili d’utente. La capacità del canale di segnalazione associato ad ogni sub-canale di base è data da:

            4. Capacità complessiva dedicata alla sincronizzazione delle trame.

            La sincronizzazione delle trame è ottenuta impiegando un IT per trama. Di conseguenza la capacità del canale di sincronizzazione è identica a quella di un sub-canale di base:

            5. Numero massimo di flussi audio VBR multiplabili sulla linea e corrispondente efficienza media di multiplazione.

            Ogni sub-canale di base ha una capacità netta per il trasferimento delle informazioni di utente data dal rapporto dai bit impiegabili per l’informazione di utente e la durata della trama. Questa capacità è quindi di:

            Per trasferire il flusso VBR caratterizzato dal ritmo di picco di 192 kbit/s sono richiesti un numero di sub-canali di base pari a:

            Dato che si sta operando con uno schema di multiplazione statica e pre-assegnazione individuale delle risorse questi quattro sub-canali di base sono dedicati interamente al trasferimento di un singolo flusso VBR. In totale quindi il numero di flussi VBR che possono essere multiplati sulla linea sono:

            L’efficienza media di utilizzazione della linea multiplata è data dal rapporto tra il numero di IT occupati (5 * 4) e il numero complessivo di IT disponibili in una trama per l’informazione d’utente (23) moltiplicato per l’efficienza media di utilizzazione di un insieme di quattro sub-canali di base da parte di un flusso VBR. Nel caso in esame quattro sub-canali sono in grado di trasferire ad un ritmo di 564 kbit/s = 224 kbit/s. Il ritmo medio di emissione della sorgente è invece 150 kbit/s. Di conseguenza l’insieme dei quattro sub-canali di base è utilizzato mediamente al 66%.

            Complessivamente l’efficienza di utilizzazione media è:

    
            """,
        "immagine_soluzione": None
    },
    {
        "esame": "TCP",
        "testo_domanda": """
            All’istante 0 viene attivata una connessione TCP tra l’host A e l’host B. Si calcoli l’istante di tempo oltre il quale la trasmissione sul link 1 risulta continua, supponendo:

            - Header trascurabili
            - Link bidirezionali e simmetrici
            - RCWND = 4000 byte e SSTHRESH = 400 byte
            - Dimensione segmenti MSS = 200 byte
            - Dimensione ACK = dimensione segmenti per apertura della connessione = 20 byte
            - Connessione aperta da A

            Quanto tempo occorre per trasferire un file da 2 kbyte sulla connessione TCP sopra specificata (dall'istante di trasmissione del primo segmento all'istante di ricezione dell'ACK dell'ultimo segmento)?
            """,
        "immagine_domanda": path_immagine + "tcp/d1.png",
        "soluzione": """
            - Soluzione -

            Cominciamo calcolando i vari tempi di trasmissione sui vari link:

            T1 = (MSS * 8 [bit]) / (25 kb/s) = 64 ms, Tack1 = (20 * 8 [bit]) / (25 kb/s) = 6.4 ms
            T2 = 1/2 T1 = 32 ms, Tack2 = Tack1 / 2 = 3.2 ms
            T3 = 1/2 T2 = 16 ms, Tack3 = Tack2 / 2 = 1.6 ms

            RTT = T1 + T2 + T3 + 2(τ1 + τ2 + τ3) + (Tack1 + Tack2 + Tack3) = 213.2 ms

            Tsetup = 2(Tack1 + Tack2 + Tack3) + 2(τ1 + τ2 + τ3) = 112.4 ms

            [Inserimento dell'immagine]

            Il link più lento è il link 1, che sarà il collo di bottiglia: il primo a saturarsi. Dunque la trasmissione è continua sul link 1 quando W * T1 < RTT, quindi W > RTT / T1 = 3.3...

            Dunque l’istante in cui la trasmissione diventa continua è quando la finestra vale MSS, cioè l’istante:

            Tc = Tsetup + 3(RTT) = 112.4 ms + 649 ms = 752 ms

            Il file da trasferire è di 2 kbyte, equivalenti a 10 MSS. Il tempo per trasferire 10 MSS è:

            Ttot = Tsetup + 4(RTT) + 3T1 = 1.15 s
        """,
        "immagine_soluzione": path_immagine + "tcp/r1.png"
    },
    {
        "esame": "ESERCIZI CRC E INTERNET CHECKSUM",
        "testo_domanda": 
"""
Si applichi alla stringa P=1110 il meccanismo di generazione di una stringa binaria lato emettitore con CRC ottenuto attraverso un polinomio generatore G(x)= x3+x+1
Si derivi:
1) La stringa binaria T emessa lato emettitore.
2) Una stringa d’errore E1 che sommata a T NON dia errore in ricezione; E1 deve essere diversa da E=0001011.
3) Una stringa d’errore E2 che sommata a T dia errore in ricezione.
""",
        "soluzione": 
"""
1) 
P(x) = 1x^3 + 1x^2 + 1x + 0
G(x) = x^3 + x + 1 --> dato
z = 3 --> grado di G(x)

(x^z * P(x))/G(x) = (x^3 * P(x))/G(x) = Q(x) + R(x)/G(x) 
T = 1110/1011 --> Si esegue la divisione e si ha come Resto della divisione R(x) = 100
Perciò T= 1110100

2)
E(x) = x^4 + x^2 + x = 0010110 --> deve essere di 7 bit
T + E(x) ) 1100010 --> T è ricevuta (cioè la T "alterata" che arriva dall'altra parte)

3)
T = 1110100
E(x) = 1000000
T'(x) = 0110100 / 1011 --> R(x) = 0111 != 0 --> dà errore
""",
        "immagine_soluzione": None
    },
    {
        "esame": "esercizio esame 2021" ,
        "testo_domanda":
"""
Si consideri una sorgente informativa a ritmo binario variabile (VBR) che trasmette in periodi temporali di durata 10 ms l’uno un numero di byte in accordo a quanto riportato nel seguente grafico (che rappresenta 9 periodi da 10 ms consecutivi, periodo totale 90 ms).
Supponendo che questa sorgente dati debba essere trasferita attaverso una linea a velocita’ di 6 Mbit/s si chiede di:
1. Calcolare il bit rate medio e di picco della sorgente in esame.
2. Determinare il numero massimo di sorgenti di questo tipo che possono essere multiplate sulla linea se si adottasse un criterio di multiplazione su base banda di picco.
3. Qual e’ il rendimento di utilizzazione della linea se si multiplano un numero di sorgerti pari a quelle derivate in 2) ma utilizzando un criterio di multiplazione su base banda media?
""",
        "immagine_domanda": path_immagine + "2021/esercizio.png",
        "soluzione": 
"""
1)
Bit rate medio della sorgente: Sommando i bit trasmessi in tutti i periodi (trasformando i byte in bit) e dividendo per il tempo totale (90 ms), otteniamo un bit rate medio di 24,000 bit/s (o 24 kbit/s).

Bit rate di picco della sorgente: Trovando il periodo in cui abbiamo il massimo numero di byte (trasformati in bit) e dividendo per la durata di quel periodo (10 ms), otteniamo un bit rate di picco di 72,000 bit/s (o 72 kbit/s).

2)
Numero massimo di sorgenti su base banda di picco: Dividendo la capacità della linea (6 Mbit/s o 6,000,000 bit/s) per il bit rate di picco (72,000 bit/s), otteniamo che il numero massimo di sorgenti che possono essere multiplicate sulla linea è di circa 83,33. Questo valore è teorico poiché in pratica non si possono avere frazioni di sorgenti, quindi il numero effettivo sarebbe 83.

3)
Rendimento di utilizzazione su base banda media: Moltiplicando il bit rate medio (24 kbit/s) per il numero massimo di sorgenti calcolato sul bit rate di picco (83,33), e dividendo questo prodotto per la capacità totale della linea (6 Mbit/s), otteniamo un rendimento di utilizzazione del 33,33%
""",
        "immagine_soluzione": None
    },
"""
        "esame": "",
        "testo_domanda": "",
        "immagine_domanda": None,
        "soluzione": "",
        "immagine_soluzione": None
"""
    
]

# ------------- Funzioni utili -------------#
def carica_immagine(percorso):
    if percorso is not None and os.path.exists(percorso):
        immagine = Image.open(percorso)
        return ImageTk.PhotoImage(immagine)
    return None

# ------------- Modalità quiz -------------#
def apri_modalita_quiz():
    def mostra_resoconto():
        messagebox.showinfo("Resoconto", f"Hai risposto correttamente a {risposte_corrette} domande su {domande_mostrate}.")
   
    def verifica_risposta(risposta_utente, risposta_corretta):
        global risposte_corrette, domande_mostrate
        risposta_data = risposta_utente.get()

        # Controlla se l'utente ha selezionato una risposta
        if not risposta_data:
            messagebox.showwarning("Attenzione", "Seleziona una risposta prima di procedere.")
            return

        # Crea una nuova finestra per il popup
        popup_window = tk.Toplevel(quiz_window)
        popup_window.title("Risultato")

        if risposta_data == risposta_corretta:
            risultato = "Corretto!"
            risposte_corrette += 1
        else:
            risultato = "Sbagliato! La risposta corretta era: " + risposta_corretta

        domande_mostrate += 1

        # Mostra il risultato nel popup
        risultato_label = tk.Label(popup_window, text=risultato)
        risultato_label.pack()

        # Pulsante per chiudere il popup
        chiudi_button = tk.Button(popup_window, text="Chiudi", command=popup_window.destroy)
        chiudi_button.pack()

        # Controlla se tutte le domande sono state mostrate
        if domande_mostrate >= len(dati_quiz):
            messagebox.showinfo("Fine del Quiz", f"Immagini finite. Il tuo punteggio è {risposte_corrette}/{domande_mostrate}.", parent=quiz_window)
            quiz_window.destroy()  # Chiude la finestra del quiz


    def mostra_prossima_immagine():
        nonlocal indice_quiz_corrente
        indice_quiz_corrente = (indice_quiz_corrente + 1) % len(dati_quiz)
        aggiorna_quiz(dati_quiz[indice_quiz_corrente])

    def aggiorna_quiz(quiz):
        
        label_esame.config(text="Esame: " + quiz["esame"], fg="cyan")
        label_immagine.config(image=None)
        testo_domanda.set(quiz["testo_domanda"])
        immagine_domanda = carica_immagine(quiz["immagine_domanda"])

        if immagine_domanda:
            label_immagine.config(image=immagine_domanda)
            label_immagine.image = immagine_domanda  # Per mantenere il riferimento
            label_immagine.pack(expand=True)
        else:
            label_immagine.pack_forget()

        risposta_utente.set(None)  # Resetta la scelta precedente

        # Riabilita e aggiorna i pulsanti delle opzioni
        for i, pulsante in enumerate(pulsanti_opzioni):
            if i < len(quiz["opzioni"]):
                opzione = quiz["opzioni"][i]
                testo_opzione = opzione["testo"]
                pulsante.config(text=testo_opzione, value=testo_opzione, state=tk.NORMAL)
                pulsante.pack(side=tk.TOP, anchor=tk.W)
            else:
                pulsante.pack_forget()

        # Nascondi i pulsanti in eccesso
        for j in range(len(quiz["opzioni"]), len(pulsanti_opzioni)):
            pulsanti_opzioni[j].pack_forget()
    
    def mostra_soluzioni():
        soluzioni_text = "\n\n".join([quiz["soluzione"] for quiz in dati_quiz])
        soluzioni_window = tk.Toplevel()
        soluzioni_window.title("Soluzioni dei Quiz")
        
        # Creazione di uno scrollbar se il testo è troppo lungo
        scrollbar = tk.Scrollbar(soluzioni_window)
        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        
        text_area = tk.Text(soluzioni_window, wrap=tk.WORD, yscrollcommand=scrollbar.set)
        text_area.insert(tk.END, soluzioni_text)
        text_area.pack(expand=True, fill=tk.BOTH)
        scrollbar.config(command=text_area.yview)

        # Adatta la grandezza del pop-up in base al contenuto
        soluzioni_window.geometry('400x300')  # Dimensioni di base, adattabili
    
    #random.seed()
    #random.shuffle(dati_quiz)
    
    indice_quiz_corrente = 0
    
    quiz_window = tk.Toplevel()
    quiz_window.title("Modalità Quiz")
    
    label_esame = tk.Label(quiz_window)
    label_esame.pack(expand=True)

    testo_domanda = StringVar()
    label_domanda = tk.Label(quiz_window, textvariable=testo_domanda, wraplength=400)
    label_domanda.pack(expand=True)

    label_immagine = tk.Label(quiz_window)
    label_immagine.pack(expand=True)

    frame_scelta = tk.Frame(quiz_window)
    frame_scelta.pack(expand=True)

    risposta_utente = StringVar()
    pulsanti_opzioni = [tk.Radiobutton(frame_scelta, text="", variable=risposta_utente, value="", image=None, compound="top") for _ in range(4)]
    for pulsante in pulsanti_opzioni:
        pulsante.pack(side=tk.LEFT)

    frame_pulsanti = tk.Frame(quiz_window)
    frame_pulsanti.pack(side=tk.BOTTOM, fill=tk.X)

    btn_prossima_domanda = tk.Button(frame_pulsanti, text="Prossima Domanda", command=mostra_prossima_immagine)
    btn_prossima_domanda.pack(side=tk.LEFT, expand=True)

    btn_invia_risposta = tk.Button(frame_pulsanti, text="Invia Risposta", command=lambda: verifica_risposta(risposta_utente, dati_quiz[indice_quiz_corrente]["risposta_corretta"]))
    btn_invia_risposta.pack(side=tk.LEFT, expand=True)

    btn_mostra_soluzioni = tk.Button(frame_pulsanti, text="Mostra Soluzioni", command=mostra_soluzioni)
    btn_mostra_soluzioni.pack(side=tk.LEFT, expand=True)
    
    btn_torna_menu = tk.Button(frame_pulsanti, text="Torna al Menù", command=lambda: quiz_window.destroy())
    btn_torna_menu.pack(side=tk.RIGHT, expand=True)
    
    # Aggiungi un pulsante per visualizzare il resoconto
    btn_resoconto = tk.Button(frame_pulsanti, text="Mostra Resoconto", command=mostra_resoconto)
    btn_resoconto.pack(side=tk.LEFT, expand=True)

    aggiorna_quiz(dati_quiz[indice_quiz_corrente])  # Inizializza il primo quiz

# ------------- modalità esercizio -------------#
def apri_modalita_esercizio():
    def mostra_prossima_domanda():
        global indice_immagine_corrente
        indice_immagine_corrente = (indice_immagine_corrente + 1) % len(dati_esercizi)

        if indice_immagine_corrente == 0:  # Se tutti gli esercizi sono stati visualizzati
            messagebox.showinfo("Fine", "Hai finito gli esercizi.")
            esercizio_window.destroy()  # Chiude la finestra degli esercizi
            return

        esercizio = dati_esercizi[indice_immagine_corrente]
        aggiorna_esercizio(esercizio)
        
    def aggiorna_esercizio(esercizio):
        
        label_testo_esercizio.config(text="Esame: " + esercizio["esame"] + "\n" + esercizio["testo_domanda"])
        # Pulisce il widget Text e l'immagine
        text_widget.delete('1.0', tk.END)
        label_immagine_esercizio.config(image=None)
        # Resetta il testo dell'esercizio e l'immagine
        # Gestione del testo dell'esercizio
        if esercizio["testo_domanda"]:
            label_testo_esercizio.config(text=esercizio["testo_domanda"])
            label_testo_esercizio.pack(side=tk.TOP, expand=True)
        else:
            label_testo_esercizio.pack_forget()

        # Gestione dell'immagine dell'esercizio
        immagine_esercizio = carica_immagine(esercizio["immagine_domanda"])
        if immagine_esercizio:
            label_immagine_esercizio.config(image=immagine_esercizio)
            label_immagine_esercizio.image = immagine_esercizio  # Mantieni il riferimento
            label_immagine_esercizio.pack(side=tk.TOP, expand=True)
        else:
            label_immagine_esercizio.pack_forget()
    
    def mostra_soluzione():
        esercizio_corrente = dati_esercizi[indice_immagine_corrente]
        soluzione_testo = esercizio_corrente["soluzione"]
        soluzione_immagine = carica_immagine(esercizio_corrente["immagine_soluzione"])

        soluzione_window = tk.Toplevel()
        soluzione_window.title("Soluzione dell'Esercizio")

        # Creazione di un Text widget con Scrollbar per la soluzione testuale
        soluzione_text_widget = tk.Text(soluzione_window, wrap=tk.WORD, height=10, width=50)
        soluzione_text_widget.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

        scrollbar = tk.Scrollbar(soluzione_window, command=soluzione_text_widget.yview)
        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

        soluzione_text_widget.config(yscrollcommand=scrollbar.set)
        soluzione_text_widget.insert(tk.END, soluzione_testo)

    # Disabilita l'editing del testo ma permette la navigazione tramite scroll
        soluzione_text_widget.config(state=tk.DISABLED)

        # Visualizza l'immagine della soluzione, se presente
        if soluzione_immagine:
            label_immagine_soluzione = tk.Label(soluzione_window, image=soluzione_immagine)
            label_immagine_soluzione.pack(expand=True)
            label_immagine_soluzione.image = soluzione_immagine  # Mantieni il riferimento
    
    def valuta_similarita(testo_utente, soluzione):
        # Se la soluzione non è definita, non fare nulla
        if soluzione is None:
            return "La soluzione non è disponibile."

        # Calcola la similarità
        similarita = difflib.SequenceMatcher(None, testo_utente, soluzione).ratio()

        # Valuta il livello di similarità (questi valori soglia possono essere adattati)
        if similarita > 0.8:
            return "Alta similarità."
        elif similarita > 0.5:
            return "Similarità media."
        else:
            return "Bassa similarità."
    
    def invia_risposta():
        risposta_utente = text_widget.get("1.0", tk.END).strip()
        soluzione_corretta = dati_esercizi[indice_immagine_corrente].get("soluzione")

        # Valuta la similarità tra la risposta dell'utente e la soluzione
        if soluzione_corretta:
            risultato = valuta_similarita(risposta_utente, soluzione_corretta)
            messagebox.showinfo("Risultato", risultato)
        else:
            messagebox.showinfo("Info", "La soluzione non è disponibile per questo esercizio.")
        # Creazione del pop-up per mostrare il risultato
        risultato_popup = tk.Toplevel(esercizio_window)
        risultato_popup.title("Risultato")
        tk.Label(risultato_popup, text="Risposta inviata!").pack(pady=10, padx=10)
        
        # Imposta il pop-up come una finestra di dialogo modale rispetto alla finestra del quiz
        risultato_popup.transient(esercizio_window)
        risultato_popup.grab_set()

        # Centra il pop-up rispetto alla finestra del quiz
        risultato_popup.geometry("+%d+%d" % (esercizio_window.winfo_rootx()+50, esercizio_window.winfo_rooty()+50))

        # Pulsante per chiudere il pop-up
        tk.Button(risultato_popup, text="Ok", command=risultato_popup.destroy).pack(pady=5)

        # Mantiene il focus sulla finestra del pop-up fino a quando non viene chiuso
        risultato_popup.wait_window()
    
    #random.seed()
    #random.shuffle(dati_esercizi)
    indice_immagine_corrente = 0
    global text_widget, label_immagine_esercizio

    esercizio_window = tk.Toplevel()
    esercizio_window.title("Modalità Esercizio")

    # Testo dell'esercizio
    label_testo_esercizio = tk.Label(esercizio_window, text="", wraplength=500)
    label_testo_esercizio.pack(side=tk.TOP, fill=tk.X)

    # Immagine dell'esercizio
    label_immagine_esercizio = tk.Label(esercizio_window)
    label_immagine_esercizio.pack(side=tk.TOP, fill=tk.X)

    # Area di testo per la risposta dell'utente
    text_widget = tk.Text(esercizio_window, wrap=tk.WORD, height=10)
    text_widget.pack(side=tk.TOP, fill=tk.BOTH, expand=True)

    # Scrollbar per l'area di testo
    scrollbar = tk.Scrollbar(esercizio_window, command=text_widget.yview)
    scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
    text_widget.config(yscrollcommand=scrollbar.set)

    # Pulsanti
    frame_pulsanti = tk.Frame(esercizio_window)
    frame_pulsanti.pack(side=tk.BOTTOM, fill=tk.X)

    btn_prossima_domanda = tk.Button(frame_pulsanti, text="Prossima Domanda", command=mostra_prossima_domanda)
    btn_prossima_domanda.pack(side=tk.LEFT)

    btn_mostra_soluzione = tk.Button(frame_pulsanti, text="Mostra Soluzione", command=mostra_soluzione)
    btn_mostra_soluzione.pack(side=tk.LEFT)

    btn_invia_risposta = tk.Button(frame_pulsanti, text="Invia Risposta", command=invia_risposta)
    btn_invia_risposta.pack(side=tk.LEFT)

    btn_torna_menu = tk.Button(frame_pulsanti, text="Torna al Menù", command=lambda: esercizio_window.destroy())
    btn_torna_menu.pack(side=tk.LEFT)

    aggiorna_esercizio(dati_esercizi[indice_immagine_corrente])  # Mostra il primo esercizio
    mostra_prossima_domanda()  # Mostra la prima immagine

# Finestra principale
root = tk.Tk()
root.title("Applicazione di Studio")

btn_quiz = tk.Button(root, text="Quiz", command=apri_modalita_quiz)
btn_quiz.pack(fill=tk.X, expand=True)

btn_esercizio = tk.Button(root, text="Esercizio", command=apri_modalita_esercizio)
btn_esercizio.pack(fill=tk.X, expand=True)

root.mainloop()