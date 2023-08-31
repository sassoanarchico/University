#include "labirinto.h"

#include <stdlib.h>
#include <assert.h>

typedef struct {
    int n;
    int **matrix;
    int **marcata;
} labirinto_struct ;

labirinto * labirinto_new(int n) {
    labirinto_struct * new_labirinto = (labirinto_struct *) malloc (sizeof(labirinto_struct));
    new_labirinto->n = n;
    new_labirinto->matrix = (int **) calloc(n, sizeof(int*));
    new_labirinto->marcata = (int **) calloc(n, sizeof(int*));
    int i,j;
	for (i = 0; i < n; i++) {
		new_labirinto->matrix[i] = (int *)calloc(n, sizeof(int));
		new_labirinto->marcata[i] = (int *)calloc(n, sizeof(int));
	}
    for (i = 0; i < n; i++) {
		for(j = 0; j<n; j++){
			new_labirinto->matrix[i][j] = LABIRINTO_VUOTA;
			new_labirinto->marcata[i][j] = LABIRINTO_FALSE;
		}
    }
    return (labirinto *) new_labirinto;
}

void labirinto_delete(labirinto * lab) {
    labirinto_struct * ptr = (labirinto_struct *) lab;
	int i;
	for(i = 0; i<ptr->n; i++){
		free(ptr->matrix[i]);
		free(ptr->marcata[i]);
	}
    free(ptr->matrix);
    free(ptr->marcata);
    free(ptr);
}

void labirinto_setpiena(labirinto * lab, int r, int c) {
    labirinto_struct * ptr = (labirinto_struct *) lab;
    ptr->matrix[r][c] = LABIRINTO_PIENA;
}

int labirinto_uscita(labirinto * lab, int r, int c) {
    labirinto_struct * ptr = (labirinto_struct *) lab;
    if (r == ptr->n - 1 && c == ptr->n - 1)
        return LABIRINTO_TRUE;
    return LABIRINTO_FALSE;
}

int labirinto_percorribile(labirinto * lab, int r, int c) {
    labirinto_struct * ptr = (labirinto_struct *) lab;
    if (r < 0 || r >= ptr->n || c < 0 || c >= ptr->n)
        return LABIRINTO_FALSE;
    if(ptr->matrix[r][c] == LABIRINTO_VUOTA && ptr->marcata[r][c] == LABIRINTO_FALSE)
        return LABIRINTO_TRUE;
    return LABIRINTO_FALSE;
}

int labirinto_uscitaraggiungibileda(labirinto * lab, int r, int c) {
    labirinto_struct * ptr = (labirinto_struct *) lab;
    
    if (labirinto_percorribile(lab, r, c) == LABIRINTO_FALSE)
        return LABIRINTO_FALSE;
    
    ptr->marcata[r][c] = LABIRINTO_TRUE;
    
    if (labirinto_uscita(lab, r, c) == LABIRINTO_TRUE)
        return LABIRINTO_TRUE;
    
    int i;
    for (i = r - 1; i <= r + 1; i++) {
        int j;
        for (j = c - 1; j <= c + 1; j++) {
            if (i != r && j != c)
                continue;
            if (i == r && j == c)
                continue;
            if (labirinto_uscitaraggiungibileda(lab, i, j) == LABIRINTO_TRUE)
                return LABIRINTO_TRUE;
        }
    }
    
    ptr->marcata[r][c] = LABIRINTO_FALSE;
    return LABIRINTO_FALSE;
}

int labirinto_risolvibile(labirinto * lab) {
    return labirinto_uscitaraggiungibileda(lab, 0, 0);
}

void labirinto_tostring(labirinto * lab, char * buffer, int buffer_size) {

	labirinto_struct * ptr = (labirinto_struct *) lab;
        assert(buffer_size >= (ptr->n + 1) * ptr->n);
    buffer[0] = '\0';
    char *buffer_ptr = buffer;
    int i;
    for (i = 0; i < ptr->n; i++) {
        int j;
        for (j = 0; j < ptr->n; j++) {
            char c;
            if(ptr->matrix[i][j] == LABIRINTO_PIENA)
                c = '#';
            if(ptr->matrix[i][j] == LABIRINTO_VUOTA && ptr->marcata[i][j] == LABIRINTO_FALSE)
                c = '.'; 
            if(ptr->matrix[i][j] == LABIRINTO_VUOTA && ptr->marcata[i][j] == LABIRINTO_TRUE)
                c = '+'; 
            buffer_ptr[0] = c;
            buffer_ptr++;
        }
        buffer_ptr[0] = '\n';
        buffer_ptr++;
    }
    buffer_ptr[0] = '\0';
}