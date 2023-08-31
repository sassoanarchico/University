import java.util.*;

public class Sort {

    /* Disponibile in java */
    public void quickSortDefault(int[] array) {
        Arrays.sort(array);
    }


    
    /** MERGE SORT */
    void betterMerge(int[] a, int left, int midm1, int right, int[] tmp) {
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

    void mergeSort(int[] arr) {
        int n = arr.length;
        int runSize = 1;
        int[] tmp = new int[n];
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
        return;
    }


    private void swap(int[] array, int i, int j){
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }


    /** HEAP SORT */
    /* versione per max heap */
    private void downHeap(int[] a, int n, int i) {
        int p = 2*i+1, q;                   /* indici figli sx e dx di i */
        int t;
        while(p < n) {                      /* deve esistere il figlio sx altrimenti return */
            q = p +1;                       /* figlio dx di i */
            if(q >= n) t = p;               /* se dx non esiste considera sx */
            else t = a[p] > a[q] ? p : q;   /* sceglie fra dx e sx */
            if(a[i] < a[t]) {               /* violazione padre-figlio? */
                swap(a, i, t);
                i = t; p = 2*i+1;
            } else return;
        }
        return;
    }

    private void array2heap(int[] a, int n) {
        if(n < 2) return;
        for(int i = (n-2)/2; i >= 0 ; i--) downHeap(a, n, i);
        return;
    }

    public void heapSort(int[] array) {
        int n = array.length;
        array2heap(array, n);
        for(int i = n-1; i >= 1; i--) {
            swap(array, 0, i);
            downHeap(array, i, 0);
        }
        return;
    }


    /** INSERTION SORT */
    public void insertionSort(int[] array) {
        int n = array.length, j;
        for(int i = 1; i < n; i++) {
            int temp = array[i];
            for(j = i-1; (j >= 0) && (array[j] > temp); j--) array[j+1] = array[j];
            array[j+1] = temp; 
        }
        return;
    }


    /** SELECTION SORT */
    public void selectionSort(int[] array) {
        int n = array.length;
        for(int i = 0; i < n-1; i++) {
            int min = i;
            for(int j = i+1; j < n; j++)
                if(array[j] < array[min]) min = j;
            swap(array, i, min);
        }
        return;
    }


    /** QUICKSORT */
    private int partition(int[] a, int left, int right) {
        Random ran = new Random();
        int l = left+1, r = right;
        int p = left + ran.nextInt(right-left); /* posiz pivot random */
        int pivot = a[p];
        swap(a, left, p);              /* pivot al primo posto */
        while(l < r) { 
            while((l < r) && (a[l] <= pivot)) l++;
            while(a[r] > pivot) r--;
            if(l < r) swap(a, l, r);
        }
        if(a[left] > a[r]) swap(a, left, r);
        return r;
    }
    private void _quickSort(int[] a, int first, int last) {
        if(first >= last) return;
        int p = partition(a, first, last);
        _quickSort(a, first, p-1);
        _quickSort(a, p+1, last);
    }
    public void quickSort(int[] array) {
        _quickSort(array, 0, array.length - 1);
        return;
    }

    /** RADIX SORT */
    
    // The main function to that sorts arr[] of size n using Radix Sort 
    public void radixSort(int[] array) {
        /*
        * assume che gli int NON siano negativi;
        * per int in generale occorre gestire a 
        * parte il caso del MSB
        */
        int[] tmp0 = new int[array.length];
        int[] tmp1 = new int[array.length];
        for(int b = 0; b < 4*8; b++)
            bucketSort2(array, array.length, b, tmp0, tmp1);
        return; 
    }

    private void bucketSort2(int[] a, int n, int bit, int[] tmp0, int[] tmp1) {
        /* 
        * ordina stabilmente l'array rispetto bit-esimo bit 
        * (LSB --> 0) 
        * */
        int i0=0, i1=0;
        int mask = 0x1 << bit; // left-shift di bit posizioni
        for(int i = 0; i < n ; i++){
            if((a[i] & mask) != 0) // estrae bit 1
                tmp1[i1++] = a[i];
            else // bit 0
                tmp0[i0++] = a[i];
        }
        for(int i = 0; i < i0; i++) a[i] = tmp0[i];
        i1 = 0;
        for(int i = i0; i < n; i++) a[i] = tmp1[i1++];
        return;
    }

    /** BUCKET SORT */
    public void bucketSort(int[] array) {
        int max = 0, min = 0, n = array.length;;
        for(int i = 1; i < n; i++)
            if(array[i] > array[max]) max = i;
            else if(array[i] < array[min]) min = i;
        int minv = array[min], size = array[max]-array[min]+1;
        int[] tmp = new int[size];
        for(int i = 0; i < n; i++) tmp[array[i] - minv]++;
        int k = 0;
        for(int i = 0; i < size; i++)
            while((tmp[i])-- != 0) 
                array[k++] = i+minv;
        return;
    }
}
