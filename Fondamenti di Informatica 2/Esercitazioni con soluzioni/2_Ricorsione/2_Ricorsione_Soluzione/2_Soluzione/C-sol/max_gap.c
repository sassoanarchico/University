#include <assert.h>
#include <stdio.h>

#include "max_gap.h"

int maxGap(int * array, int start, int end) {
	assert(array != NULL);
	assert(start >= 0);
	assert(start < end);

	int size = end - start;
	if (size < 2)
		return -1;
	if (size == 2) {
		return array[start + 1] - array[start];
	}

    int pivot = start + (size / 2);
    int max_gap_left = maxGap(array, start, pivot+1);
    int max_gap_right = maxGap(array, pivot, end);

    return max_gap_left > max_gap_right ? max_gap_left : max_gap_right;
}
