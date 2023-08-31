#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "sort.h"

//static void bucketSort2(int *, int, int);
static void bucketSort2(int *a, int n, int bit, int *tmp0, int *tmp1);


void betterMerge(int *a, int left, int midm1, int right, int *tmp) {
    int i = left, j = midm1+1, k = 0;
    while((i <= midm1) && (j <= right))
        if(a[i] < a[j]) tmp[k++] = a[i++];
        else tmp[k++] = a[j++];

    /* se termina prima il subarray di dx */
    for(int h = 0; h <= midm1-i; h++) a[right-h] = a[midm1-h];
        
    /* sovrascrive su a */
    for(int h = 0; h < k; h++) a[left+h] = tmp[h];
    
    return;
}



void mergeSort(array *a) {
    int *arr = a->arr, n = a->size;
    int runSize = 1;
    int *tmp = malloc(sizeof(int)*n);    
    while(runSize < n) {
        int l = 0, mm1 = runSize-1, r;
        while(mm1 < n-1) { /* esiste il secondo da fondere */
            r = mm1 + runSize < n-1 ? mm1 + runSize : n-1;
            betterMerge(arr, l, mm1, r, tmp);
            l = r+1;
            mm1 = l + runSize-1;
        }
        runSize <<= 1;
    }
    free(tmp);
    return;
}

static void downHeap(int *a, int n, int i) {
    /* versione per max heap */
    int p = 2*i+1, q; /* indici figli sx e dx di i */
    int t;
    while(p < n) { /* deve esistere il figlio sx altrimenti return */
        q = p +1; /* figlio dx di i */
        if(q >= n) t = p; /* se dx non esiste considera sx */
        else t = a[p] > a[q] ? p : q; /* sceglie fra dx e sx */
        if(a[i] < a[t]) { /* violazione padre-figlio? */
            swap(&a[i], &a[t]);
            i = t; p = 2*i+1;
        } else return;
    }
    return;
}

static void array2heap(int *a, int n) {
    if(n < 2) return;
    for(int i = (n-2)/2; i >= 0 ; i--) downHeap(a, n, i);
    return;
}

void heapSort(array *a) {
    int *arr = a->arr, n = a->size;
    array2heap(arr, n);
    for(int i = n-1; i >= 1; i--) {
        swap(&arr[0], &arr[i]);
        downHeap(arr, i, 0);
    }
    return;
}

void insertionSort(array *a) {
    int *arr = a->arr, n = a->size, j;
    for(int i = 1; i < n; i++) {
        int temp = arr[i];
        for(j = i-1; (j >= 0) && (arr[j] > temp); j--) arr[j+1] = arr[j];
        arr[j+1] = temp; 
    }
    return;
}

void selectionSort(array *a) {
    int *arr = a->arr, n = a->size;
    for(int i = 0; i < n-1; i++) {
        int min = i;
        for(int j = i+1; j < n; j++)
            if(arr[j] < arr[min]) min = j;
        swap(&arr[i], &arr[min]);
    }
    return;
}

static int partition(int *a, int left, int right) {
    int l = left+1, r = right;
    int p = left + nextInt(right-left); /* posiz pivot random */
    int pivot = a[p];
    swap(&a[left], &a[p]);              /* pivot al primo posto */
    while(l < r) { 
        while((l < r) && (a[l] <= pivot)) l++;
        while(a[r] > pivot) r--;
        if(l < r) swap(&a[l], &a[r]);
    }
    if(a[left] > a[r]) swap(&a[left], &a[r]);
    return r;
}

static void _quickSort(int *a, int first, int last) {
    if(first >= last) return;
    int p = partition(a, first, last);
    _quickSort(a, first, p-1);
    _quickSort(a, p+1, last);
}

void quickSort(array *a) {
//stampaArray(a);
    _quickSort(a->arr, 0, a->size - 1);
    return;
}

void radixSort(array *a) {
	/*
	 * assume che gli int NON siano negativi;
	 * per int in generale occorre gestire a 
	 * parte il caso del MSB
	 */
	int *tmp0 = malloc(a->size*sizeof(int)); // riduz. #malloc 
	int *tmp1 = malloc(a->size*sizeof(int));
	for(int b = 0; b < sizeof(int)*8; b++)
		bucketSort2(a->arr, a->size, b, tmp0, tmp1);
	free(tmp0); free(tmp1);
    return;
}

static void bucketSort2(int *a, int n, int bit, int *tmp0, int *tmp1) {
	/* 
	 * ordina stabilmente l'array rispetto bit-esimo bit 
	 * (LSB --> 0) 
	 * */
//	int *tmp0 = malloc(n*sizeof(int)), i0 = 0; // spostato fuori per ott.
//	int *tmp1 = malloc(n*sizeof(int)), i1 = 0;
	int i0=0, i1=0;
	int mask = 0x1 << bit; // left-shift di bit posizioni
	for(int i = 0; i < n ; i++)
		if(a[i] & mask) // estrae bit 1
			tmp1[i1++] = a[i];
		else // bit 0
			tmp0[i0++] = a[i];
	for(int i = 0; i < i0; i++) a[i] = tmp0[i];
	i1 = 0;
	for(int i = i0; i < n; i++) a[i] = tmp1[i1++];
//	free(tmp0); free(tmp1);
	return;
}

void bucketSort(array *a) {
    int *arr = a->arr, n = a->size;
    int max = 0, min = 0;
    for(int i = 1; i < n; i++)
        if(arr[i] > arr[max]) max = i;
        else if(arr[i] < arr[min]) min = i;
    int minv = arr[min], size = arr[max]-arr[min]+1;
    int *tmp = malloc(sizeof(int)*size);
    for(int i = 0; i < n; i++) tmp[arr[i] - minv]++;
    int k = 0;
    for(int i = 0; i < size; i++)
        while((tmp[i])--) arr[k++] = i+minv;
    free(tmp);
    return;
}

