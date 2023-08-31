import java.io.File;
import java.util.Random;
import java.util.LinkedList;

public class Driver {

    public static void print() {
        System.out.println("Richiesto argomento: {graph, cc, distance}");
    }

    public static void main(String[] argv) {

        if (argv.length < 1) {
            print();
            return;
        }
        
        if (argv[0].equals("graph")) {

        	File f = new File("graph.in");
        	Graph<String> graph = Graph.readFF(f);

            System.out.println("Grafo rappresentato come lista di archi");
            System.out.println("La prima riga contiene il numero di nodi e il numero di archi");
            System.out.println("Il tuo programma dovrebbe stampare (l'ordine non è importante):");
            System.out.println("12 12\n1 2\n1 3\n1 6\n3 4\n3 7\n4 5\n7 6\n8 9\n8 10\n8 11\n10 11\n10 12\n");
            System.out.println("Il tuo programma stampa:");
            System.out.println(graph);
        }
        else if (argv[0].equals("cc")) {
        	File f = new File("graph.in");
        	Graph<String> graph = Graph.readFF(f);
            
            System.out.println("\n Componenti connesse");
            System.out.println("Di ogni componente connessa viene stampata la lista dei nodi che ne fanno parte (l'ordine non è importante)\n");
            System.out.println("1 2 3 4 5 6 7\n8 9 10 11 12\n");
            System.out.println("Il tuo programma stampa:");
            GraphServices.connectedComponents(graph);
        }
        else if (argv[0].equals("distance")) {
			GraphNode s;
        	File f = new File("graph.in");
        	Graph<String> graph = Graph.readFF(f);
        	
			int n = 1;
			s = (GraphNode)((LinkedList) graph.getNodes()).get(n); // Nodo sorgente
            System.out.println("Distanze dal nodo avente etichetta 2 (numero minimo di archi per raggiungere il nodo 2):");
            System.out.println("nodo distanza");
            System.out.println("2 0\n1 1\n3 2\n6 2\n4 3\n7 3\n5 4\n");
            System.out.println("Il tuo programma stampa:");
            GraphServices.distances(graph, s);
            System.out.println("\n\n");
            
			n = 7;
			s = (GraphNode)((LinkedList) graph.getNodes()).get(n); // Nodo sorgente
            System.out.println("Distanze dal nodo avente etichetta 8 (numero minimo di archi per raggiungere il nodo 8):");
            System.out.println("nodo distanza");
            System.out.println("8 0\n9 1\n10 1\n11 1\n12 2\n");
            System.out.println("Il tuo programma stampa:");
            GraphServices.distances(graph, s);
            System.out.println("\n\n");
            
        }
    } //main
} // class
