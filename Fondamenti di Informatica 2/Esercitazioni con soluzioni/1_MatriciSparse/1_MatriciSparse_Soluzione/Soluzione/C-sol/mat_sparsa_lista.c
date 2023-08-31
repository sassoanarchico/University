#include "mat_sparsa_lista.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct elem {
	int i;
	int j;
	int x;
	struct elem *next;
} elem;

struct matrice_sparsa {
	int m;
	int n;
	elem* head;
};

matrice_sparsa* matrice_sparsa_new(int m, int n) {
	matrice_sparsa* ret = (matrice_sparsa*)malloc(sizeof(matrice_sparsa));
	ret->m = m;
	ret->n = n;
	ret->head = NULL;
	return ret;
}

void del_lista_ric(elem* e) {
	if (e == NULL)
		return;
	else {
		del_lista_ric(e->next);
		free(e);
	}
}

void matrice_sparsa_delete(matrice_sparsa* mat) {
	elem* ptr = mat->head;
	del_lista_ric(ptr);
	free(mat);
}

int get_num_row(matrice_sparsa* mat) {
	return mat->m;
}

int get_num_col(matrice_sparsa* mat) {
	return mat->n;
}

void mat_remove(matrice_sparsa* mat, int i, int j){
	elem* it = mat->head;
	elem* aux = it;

	while(it != NULL){
		if (it->i == i && it->j == j) {
			if(it == mat->head){																
				mat->head = it->next;
				free(it);
				return;
			}
			aux->next = it->next;
			free(it);
			return;
		}
		aux = it;
		it = it->next;
	}
}

void mat_set(matrice_sparsa* mat, int i, int j, int x) {
	if(i >= mat->m || j >= mat->n){
		printf("Gli indici inseriti superano i limiti della matrice!\n");
		return;
	}

	if (x == 0) {																				// Se set a 0 su un elemento in lista, questo va rimosso.
		mat_remove(mat, i, j);
		return;
	}

	elem* it = mat->head;
	elem* to_put = (elem*)malloc(sizeof(elem));
	to_put->i = i;
	to_put->j = j;
	to_put->x = x;
	to_put->next = NULL;

	if (it == NULL || it->i > i || (it->i == i && it->j > j)) {									// IN TESTA - Aggiunge
		to_put->next = mat->head;
		mat->head = to_put;
		return;
	}
	if (it->i == i && it->j == j) {																// IN TESTA - Modifica se già presente
		it->x = x;
		free(to_put);
		return;
	}
	while (it->next != NULL) {
		if (it->i == i && it->j == j) {															// IN MEZZO - Modifica se già presente
			it->x = x;
			free(to_put);
			return;
		}
		if (it->next->i > i || (it->next->i == i && it->next->j > j)) {							// IN MEZZO - Aggiunge
			to_put->next = it->next;
			it->next = to_put;
			return;
		}
		it = it->next;
	}
	if (it->i == i && it->j == j) {																// IN CODA - Modifica se già presente
		it->x = x;
		free(to_put);
		return;
	}
	it->next = to_put;																			// IN CODA - Aggiunge
}

int mat_get(matrice_sparsa* mat, int i, int j) {
	elem* it = (elem*)mat->head;
	while (it != NULL) {
		if (it->i == i && it->j == j) {
			return it->x;
		}
		it = it->next;
	}
	return 0;
}

void mat_print(matrice_sparsa* mat) {
	int i, j;
	elem* it = mat->head;
	for (i = 0; i < mat->m; i++) {
		for (j = 0; j < mat->n; j++) {
			if (it == NULL || (it->i > i && it->j > j)) {
				printf("%d ", 0);
			}
			else if (it->i == i && it->j == j) {
				printf("%d ", it->x);
				it = it->next;
			}
			else {
				printf("%d ", 0);
			}
		}
		printf("\n");
	}
}

matrice_sparsa* mat_add(matrice_sparsa* mat1, matrice_sparsa* mat2) {
	int row1, row2, col1, col2;
	row1 = get_num_row(mat1);
	row2 = get_num_row(mat2);
	col1 = get_num_col(mat1);
	col2 = get_num_col(mat2);
	if (row1 != row2 || col1 != col2) {
		printf("Impossibile sommare le due matrici, dimensioni differenti\n");
		exit(1);
	}
	matrice_sparsa* ret = matrice_sparsa_new(row1, col1);
	elem* it1 = mat1->head;
	elem* it2 = mat2->head;
	while (it1 != NULL || it2 != NULL) {
		if (it1 != NULL && it2!= NULL) {
			if (it1->i < it2->i ||(it1->i == it2->i && it1->j < it2->j)) {
				mat_set(ret, it1->i, it1->j, it1->x);
				it1 = it1->next;
			}
			else if (it1->i == it2->i && it1->j == it2->j) {
				mat_set(ret, it1->i, it1->j, (it1->x + it2->x));
				it1 = it1->next;
				it2 = it2->next;
			}
			else {
				mat_set(ret, it2->i, it2->j, it2->x);
				it2 = it2->next;
			}
		}
		else if(it2 != NULL) {
			mat_set(ret, it2->i, it2->j, it2->x);
			it2 = it2->next;
		}
		else if (it1 != NULL) {
			mat_set(ret, it1->i, it1->j, it1->x);
			it1 = it1->next;
		}
	}
	return ret;
}

matrice_sparsa* mat_tra(matrice_sparsa* mat) {
	matrice_sparsa* ret = matrice_sparsa_new(get_num_col(mat), get_num_row(mat));
	elem* it = mat->head;
	while (it != NULL) {
		mat_set(ret, it->j, it->i, it->x);
		it = it->next;
	}
	return ret;
}

matrice_sparsa* mat_mul(matrice_sparsa* mat1, matrice_sparsa* mat2) {
	int row1, row2, col1, col2;
	row1 = get_num_row(mat1);
	row2 = get_num_row(mat2);
	col1 = get_num_col(mat1);
	col2 = get_num_col(mat2);
	if (col1 != row2) {
		printf("Impossibile moltiplicare le due matrici\n");
		exit(1);
	}
	matrice_sparsa* ret = matrice_sparsa_new(row1, col2);
	int i, j, k, val;
	for (i = 0; i < row1; i++) {
		for (j = 0; j < col2; j++) {
			val = 0;
			for (k = 0; k < col1; k++) {
				val += (mat_get(mat1, i, k) * mat_get(mat2, k, j));
			}
			if (val != 0) {
				mat_set(ret, i, j, val);
			}
		}
	}
	return ret;
}
