#ifndef MAX_GAP_H
#define	MAX_GAP_H

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Return the maximum gap between subsequent integers
 * stored in array[start] ... array[end -1].
 * If there are less than two intergers in the considered portion
 * of the array, then -1 is returned.
 */
extern int maxGap(int * array, int start, int end);

#ifdef	__cplusplus
}
#endif

#endif	/* MAX_GAP_H */
