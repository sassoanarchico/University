
// Implementazione del Bubble Sort in Java 
class BubbleSort { 
	
    void bubbleSort(int a[]) 
    { 
        int n = a.length; 
        for (int i = 0; i < n-1; i++) 
            for (int j = 0; j < n-i-1; j++) 
				// Se a[j] > a[j+1] allora scambia
                if (a[j] > a[j+1]) { 
                    int temp = a[j]; 
                    a[j] = a[j+1]; 
                    a[j+1] = temp; 
                } 
    } 
  
    /* Stampa array */
    void printArray(int arr[]) { 
        int n = arr.length; 
        for (int i=0; i<n; ++i) 
            System.out.print(arr[i] + " "); 
        System.out.println(); 
    } 
  
    // Driver per provare la classe 
    public static void main(String args[]) { 
        BubbleSort ob = new BubbleSort(); 
        int arr[] = {64, 34, 25, 12, 22, 11, 90}; 
        ob.bubbleSort(arr); 
        System.out.println("Sorted array"); 
        ob.printArray(arr); 
    } 
} 

