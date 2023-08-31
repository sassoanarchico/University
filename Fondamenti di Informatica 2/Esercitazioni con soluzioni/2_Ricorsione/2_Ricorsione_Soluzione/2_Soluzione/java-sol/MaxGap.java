public class MaxGap {

    public static int maxGap(int[] array, int start, int end) {

        if (start < 0 || start > end || array == null)
            throw new RuntimeException("Invalid start, end, or array.");

        int size = end - start;

        if (size < 2)
            return -1;

        if (size == 2) {
            return array[start + 1] - array[start];
        }

        int pivot = start + (size / 2);

        int max_gap_left = maxGap(array, start, pivot+1);
        int max_gap_right = maxGap(array, pivot, end);


        return max_gap_right > max_gap_left ? max_gap_right : max_gap_left;

    }

}
