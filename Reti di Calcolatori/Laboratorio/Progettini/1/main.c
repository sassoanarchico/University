#include <stdio.h>
#include <stdlib.h>

/* Struttura Date */
struct Date {
    int day;
    int month; 
    int year;
};

// Trasforma la stringa data nella forma gg/mm/aaaa in una struct Date
struct Date stringToDate(char* dateString) {
    struct Date date;
    sscanf(dateString, "%d/%d/%d", &date.day, &date.month, &date.year);
    return date;
}

// Controlla se l'anno è bisestile. Se l'anno è bisestile ritorna 1, altrimenti 0
int isLeapYear(int year) {
    if ((year % 4 == 0 && year % 100 != 0)|| (year % 400 == 0)) 
        return 1;
    else
        return 0;
}

// Calcola quanti giori sono presenti nel mese specifico
int daysInMonth(int month, int year) {
    if (month == 2) {
        if (isLeapYear(year)) 
            return 29;
        else 
            return 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    } else {
        return 31;
    }
}

// Controlla se la data inserita è valida 
int validateDate(struct Date date) {
    if (date.month < 1 || date.month > 12) { // Controlla se il mese è valido
        return 0; // Mese non valido
    }

    if (date.day < 1 || date.day > daysInMonth(date.month, date.year)) { // Controlla se il giorno è valido per il mese e l'anno
        return 0; // Giorno non valido
    }

    return 1; // Data valida
}

// Calcola i giorni totali di una data, convertendo anni e mesi in giorni 
int totalDays(struct Date date) {
    int days = 0;

    //trasforma gli anni in giorni e lo aggiunge ai giorni totali
    for (int y = 0; y < date.year; y++) {
        if (isLeapYear(y)) 
            days += 366;
        else 
            days += 365;
    }

    //trasforma i mesi in giorni e li aggiunge ai giorni totali
    for (int m = 0; m < date.month; m++) {
        days += daysInMonth(m, date.year);
    }

    //aggiungo i giorni rimanenti
    days+= date.day;

    return days;
}

struct Date daysInDate(int days) {
    struct Date date;
    date.year = 0; 

    //calcola dai giorni il numero di anni e li aggiunge alla Data
    while (days > 365) {
        if (isLeapYear(date.year) && days > 366) {
            days -= 366;
        } else if (!isLeapYear(date.year)) {
            days -= 365;
        } else {
            break; // Se l'anno è bisestile e i giorni sono <= 366, non sottrarre
        }
        date.year++;
    }

    //calcola dai giorni rimanenti il numero di mesi e li aggiunge alla Data
    date.month = 0;
    while (days > daysInMonth(date.month, date.year)) {
        days -= daysInMonth(date.month, date.year);
        date.month++;
    }

    // aggiunge i gioni alla Data
    date.day = days;

    return date;    
}

//calcola la data intermedia e la restituice in formato Data
struct Date intermediateDate(struct Date d1, struct Date d2) {
    struct Date intermediate;
    int td1, td2, tdi, sum;

    //td = total_day
    td1 = totalDays(d1);
    td2 = totalDays(d2);

    sum = td1+td2;
    tdi = sum/2;

    // Se la somma è dispari, incrementa avg per arrotondare per eccesso
    if (sum % 2 != 0) {
        tdi++;
    }

    intermediate = daysInDate(tdi);

    return intermediate;
}

// Esegue la printf di una struct Date
void printDate(struct Date d) {
    printf("Intermediate: %d/%d/%d\n", d.day, d.month, d.year);
}

// Main
int main() {
    // Inizializzo due stringhe (array di char) per le date di input.
    char i1[11], i2[11];
    struct Date date1, date2, intermediate;
    
    printf("Calcolatore di date intermedie. Premere CTRL+C per uscire dall'applicazione\n");

    // Lettura delle due date
    printf("Inserisci la prima data (gg/mm/aaaa): \n");
    scanf("%s", i1);
    printf("Inserisci la seconda data (gg/mm/aaaa): \n");
    scanf("%s", i2);

    //convesione della stringa in Date
    date1 = stringToDate(i1);
    //controllo se la Data è valida
    if (!validateDate(date1))  {
        printf("La data inserita non è valida.\nExiting...\n");
        return 1;
    }

    date2 = stringToDate(i2);
    if (!validateDate(date2))  {
        printf("La data inserita non è valida.\nExiting...\n");
        return 1;
    }

    //calcolo del giorno intermedio
    intermediate = intermediateDate(date1, date2);
    printDate(intermediate);

    return 0;
}