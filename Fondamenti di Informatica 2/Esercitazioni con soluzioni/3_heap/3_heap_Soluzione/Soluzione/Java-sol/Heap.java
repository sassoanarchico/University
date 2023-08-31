public class Heap {

    public enum HEAP_TYPE {MAX_HEAP, MIN_HEAP};

    private HeapEntry[] array;
    private HEAP_TYPE type;
    private int used;

    static class HeapEntry {
        private int key;
        private int position;
    }

    public Heap(HEAP_TYPE type, int capacity) {

        this.used = 0;
        this.array = new HeapEntry[capacity];
        this.type = type;
    }

    public HEAP_TYPE getType() {
        return this.type;
    }

    public int peek() {
        return this.array[0].key;
    }

    private void grow() {
        HeapEntry[] old = this.array;
        this.array = new HeapEntry[this.array.length * 2];
        for (int i = 0; i < old.length; i++)
            this.array[i] = old[i];
    }

    private int getParentIndex(int i) {
        return (i - 1) / 2;
    }

    private boolean isRootIndex(int i) {
        return i == 0 ? true : false;
    }

    private int getLeftIndex(int i) {
        return 2 * i + 1;
    }

    private int getRightIndex(int i) {
        return getLeftIndex(i) + 1;
    }

    private boolean isLeaf(int i) {
        return getLeftIndex(i) >= this.used;
    }

    private boolean compare(int i, int j) {

        if (this.type == HEAP_TYPE.MIN_HEAP)
            return this.array[i].key < this.array[j].key;
        else
            return this.array[i].key > this.array[j].key;
    }

    private void exchange(int i, int j) {

        HeapEntry temp = this.array[i];
        this.array[i] = this.array[j];
        this.array[j] = temp;

        this.array[i].position = i;
        this.array[j].position = j;
    }

    public HeapEntry add(int key) {

        if(this.used >= this.array.length)
            grow();

        HeapEntry e = new HeapEntry();
        e.key = key;
        e.position = this.used;
        this.array[this.used] = e;

        int i = this.used;
        int j = getParentIndex(i);
        while(!isRootIndex(i) && compare(i, j)) {
            exchange(i, j);
            i = j;
            j = getParentIndex(i);
        }

        this.used += 1;
        return e;
    }

    public int getEntryKey(HeapEntry e) {
        return e.key;
    }

    public int size() {
        return this.used;
    }

    private int getMaxChildIndex(int k) {

        if(isLeaf(k))
            return -1;

        else {

            int l = getLeftIndex(k);
            int r = getRightIndex(k);
            int max = l;
            if(r < this.used && compare(r, l))
                max = r;

            return max;
        }
    }

    private void heapify(int i) {

        if(isLeaf(i))
            return;

        else {

            int j = getMaxChildIndex(i);
            if (j < 0)
                return;

            if(!compare(i, j)) {
                exchange(i, j);
                heapify(j);
            }
        }
    }

    public int poll() {

        int key = -1;
        if(this.used > 0) {
            HeapEntry e = this.array[0];
            this.array[0] = this.array[this.used - 1];
            this.used -= 1;
            heapify(0);
            key = e.key;
        }

        return key;
    }

    public static Heap array2heap(int[] array, HEAP_TYPE type) {

        Heap h = new Heap(type, array.length);

        int k;
        for (k = 0; k < array.length; k++) {

            HeapEntry e = new HeapEntry();
            e.key = array[k];
            e.position = k;
            h.array[k] = e;

        }

        h.used = array.length;

        for(k = h.getParentIndex(array.length - 1); k >= 0; k--) {
            h.heapify(k);
        }

        return h;
    }

    public void print() {

        for (int k = 0; k < this.used; k++)
            System.out.print(" " + this.array[k].key);
        System.out.println("\n");
    }

    public static void heapSort(int[] array) {

        Heap h = array2heap(array, HEAP_TYPE.MAX_HEAP);
        for(int i = array.length - 1; i > 0; i--) {

            h.exchange(0, i);
            array[i] = h.array[i].key;
            h.used -= 1;
            h.heapify(0);

        }

        array[0] = h.array[0].key;
    }

    private void siftUp(int i){

        while (i > 0) {

            int p = getParentIndex(i);
            if (compare(i, p)) {

                exchange(i, p);
                i = p;

            } else
                return;
        }
    }

    public void updateEntryKey(HeapEntry e, int key) {

        int oldKey = e.key;
        e.key = key;

        boolean keyDecrease = key < oldKey;

        if (this.getType() == HEAP_TYPE.MIN_HEAP) {

            if (keyDecrease)
                siftUp(e.position);
            else
                heapify(e.position);

        } else {

            if (!keyDecrease)
                siftUp(e.position);
            else
                heapify(e.position);

        }

    }

}
