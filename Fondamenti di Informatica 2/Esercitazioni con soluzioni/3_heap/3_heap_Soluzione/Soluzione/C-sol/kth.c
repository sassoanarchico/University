#include <stdlib.h>
#include <stdio.h>

#include "heap.h"
#include "kth.h"

kth * kth_new(int k) {
	kth * d = malloc(sizeof(kth));
	d->min_heap = heap_new(MIN_HEAP, k);
	d->max_heap = heap_new(MAX_HEAP, k);
	d->k = k;

	return d;
}

void kth_print(kth * d) {
	heap_print(d->max_heap);
	heap_print(d->min_heap);
}


void kth_insert(kth * d, int key) {	
	if (heap_size(d->max_heap) < d->k) {
		heap_add(d->max_heap, key);
	} else if (key >= heap_peek(d->max_heap)) {
		heap_add(d->min_heap, key);
	} else {
		int old = heap_poll(d->max_heap);
		heap_add(d->max_heap, key);
		heap_add(d->min_heap, old);
	}
}

int kth_get(kth * d) {
	if (heap_size(d->max_heap) >= d->k)
		return heap_peek(d->max_heap);
	else{
		printf("L'Array contiene un numero inferiore a k elementi\n");
		return -1;
	}
}

void kth_remove(kth * d) {
	if (heap_size(d->max_heap) >= d->k){
		if (heap_size(d->min_heap) == 0) {
			heap_poll(d->max_heap);
		} else {
			int key = heap_poll(d->min_heap);
			heap_poll(d->max_heap);
			heap_add(d->max_heap, key);
		}
	}
}

void kth_delete(kth * d) {
	heap_delete(d->max_heap);
	heap_delete(d->min_heap);
	free(d);
}