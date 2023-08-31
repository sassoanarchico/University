#include "mat_sparsa_lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

matrice_sparsa* read_mat_ff(const char* file_name);

int main() {
	matrice_sparsa* mat1 = read_mat_ff("mat.dat");

	printf("Original Matrix:\n");
	mat_print(mat1);
	printf("\n");
	printf("################################################################################\n");
	printf("TEST MAT_SET\n");
	printf("################################################################################\n\n");
	printf("\n");
	printf("\n");
	printf("Added -> 0,0,5\n");
	mat_set(mat1, 0, 0, 5);
	mat_print(mat1);
	printf("\n");
	printf("Added -> 1,1,70\n");
	mat_set(mat1, 1, 1, 70);
	mat_print(mat1);
	printf("\n");
	printf("Added -> 6,7,45\n");
	mat_set(mat1, 6, 7, 45);
	mat_print(mat1);
	printf("\n");
	printf("Added -> 9,9,45\n");
	mat_set(mat1, 9, 9, 45);
	mat_print(mat1);
	printf("\n");
	printf("Added -> 9,9,50\n");
	mat_set(mat1, 9, 9, 50);
	mat_print(mat1);
	printf("\n");
	printf("Added -> 10,10,45\n");
	mat_set(mat1, 10, 10, 45);
	mat_print(mat1);
	printf("\n");

	printf("################################################################################\n");
	printf("TEST MAT_REMOVE\n");
	printf("################################################################################\n\n");
	printf("Removed -> 0,0,5\n");
	mat_set(mat1, 0, 0, 0);
	mat_print(mat1);
	printf("\n");
	printf("Removed -> 1,1,70\n");
	mat_set(mat1, 1, 1, 0);
	mat_print(mat1);
	printf("\n");
	printf("Removed -> 6,7,45\n");
	mat_set(mat1, 6, 7, 0);
	mat_print(mat1);
	printf("\n");
	printf("Removed -> 5,5,45\n");
	mat_set(mat1, 5, 5, 0);
	mat_print(mat1);
	printf("\n");
	printf("Removed -> 10,10,45\n");
	mat_set(mat1, 10, 10, 0);
	mat_print(mat1);
	printf("\n");

	printf("################################################################################\n");
	printf("TEST MATRICE SOMMA\n");
	printf("################################################################################\n\n");
	printf("Matrix 1:\n");
	mat_print(mat1);
	printf("\n");
	printf("Matrix 2:\n");
	matrice_sparsa* mat2 = read_mat_ff("mat1.dat");
	mat_print(mat2);
	printf("\n");
	printf("Matrix 1 + Matrix 2:\n");
	matrice_sparsa* mat3 = mat_add(mat1, mat2);
	mat_print(mat3);
	printf("\n");

	printf("################################################################################\n");
	printf("TEST MATRICE TRASPOSTA\n");
	printf("################################################################################\n\n");
	printf("(Matrix 1)^T:\n");
	matrice_sparsa* mat4 = mat_tra(mat1);
	mat_print(mat4);
	printf("\n");

	printf("################################################################################\n");
	printf("TEST MOLTIPLICAZIONE\n");
	printf("################################################################################\n\n");
	printf("Matrix 1 * (Matrix 1)^T:\n");
	matrice_sparsa* mat5 = mat_mul(mat1, mat4);
	mat_print(mat5);
	printf("\n");

	matrice_sparsa_delete(mat1);
	matrice_sparsa_delete(mat2);
	matrice_sparsa_delete(mat3);
	matrice_sparsa_delete(mat4);
	matrice_sparsa_delete(mat5);
	printf("Finito\n");
}

matrice_sparsa* read_mat_ff(const char* file_name){
	FILE* file = fopen(file_name, "r");
	int val = 0;
	int m, n;
	fscanf(file, "%d", &val);
	m = val;
	fscanf(file, "%d", &val);
	n = val;
	matrice_sparsa* ret = matrice_sparsa_new(m, n);
	int i, j;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			//printf("%d ", i);
			fscanf(file, "%d", &val);
			mat_set(ret, i, j, val);
		}
	}
	fclose(file);
	return ret;
}
