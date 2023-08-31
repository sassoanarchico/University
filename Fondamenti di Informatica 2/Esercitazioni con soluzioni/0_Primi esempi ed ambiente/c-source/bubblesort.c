// prototipi
void bubbleSort(int *, int);
static void swap(int *, int);
// fine prototipi


void bubbleSort(int *a, int n) {
    if(n <= 1) return; // nulla da ordinare
    int ordinato = 0;
    while(!ordinato) {
        ordinato = 1;
        for(int i = 0; i < n-1; i++)
            if(a[i] > a[i+1]) {
                swap (a, i);
                ordinato = 0;
            }
        n--;
    }
}

static void swap(int *a, int i) {
    // assume che gli indici i e i+1 non sforino l'array
    int tmp = a[i];
    a[i] = a[i+1];
    a[i+1] = tmp;
}
