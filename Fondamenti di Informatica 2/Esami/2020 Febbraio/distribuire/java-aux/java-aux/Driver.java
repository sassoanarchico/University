import java.util.*;

public class Driver {

    public static void print() {
        System.out.println("Richiesto argomento: {ordina, outer_range, altezza}");
    }

    public static void main(String[] argv) {
		
		//int a[] = {1, 2, 3};
		//System.out.println(Arrays.toString(a));

		if (argv.length > 0) {
			BST<String> b = new BST<String>(6, "Pisa");

			b.insert(3, "Roma");
			b.insert(12, "Milano");
			b.insert(7, "Bologna");
			b.insert(5, "Firenze");
			b.insert(1, "Torino");
			b.insert(15, "Siracusa");
			b.insert(8, "Bari");
			b.insert(2, "Napoli");
			b.insert(25, "Radicofani");
			b.insert(20, "Milano");
			b.insert(26, "Piacenza");
			
			BSTServices bstserv = new BSTServices();
			
			// Test ordinamento
			if (argv[0].equals("ordina")) {
				System.out.println("Albero di partenza:");
				b.print();
				System.out.println();

				System.out.println("Test ordinamento: il programma dovrebbe stampare [26, 25, 20, 15, 12, 8, 7, 6, 5, 3, 2, 1]");
				System.out.println("Il tuo programma stampa " + bstserv.ordina(b));
			}

			
			// Test outer range
			else if (argv[0].equals("outer_range")) {
				System.out.println("Albero di partenza:");
				b.print();
				System.out.println();

				System.out.println("Le chiavi non appartenenti all'intervallo [5, 12] sono: [1, 2, 3, 15, 20, 25, 26]");
				System.out.println("Le chiavi non appartenenti all'intervallo [5, 12] calcolate dal tuo programma sono: " + bstserv.outer_range(b, 5, 12));
				System.out.println();
			}

			// Test altezza
			else if (argv[0].equals("altezza")) {
				System.out.println("Albero di partenza:");
				b.print();
				System.out.println();

				System.out.println("L'altezza dell'albero è 4");
				System.out.println("L'altezza dell'albero calcolata dal tuo programma è: " + bstserv.altezza(b));
				System.out.println();
			}

			else
				print();
		}
		else
			print();
	}
	
}
