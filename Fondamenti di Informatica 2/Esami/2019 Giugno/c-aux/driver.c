#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "graph.h"

void connectedComponents(graph *g);
void distances(graph *g, graph_node *s);


static void print() {
    printf("Richiesto argomento: {graph, cc, distance}\n");
}

int main(int argc, char **argv) {

    if (argc < 2) {
        print();
        return 0;
    }
    
    if (strcmp(argv[1],"graph") == 0) {

        FILE *f = fopen("graph.in", "r");
        assert(f != NULL);
        graph *g = graph_read_ff(f);
        fclose(f);

        printf("Grafo rappresentato come lista di archi\n");
        printf("La prima riga contiene il numero di nodi e il numero di archi\n");
        printf("Il tuo programma dovrebbe stampare (l'ordine non è importante):\n");
        printf("12 12\n1 2\n1 3\n1 6\n3 4\n3 7\n4 5\n7 6\n8 9\n8 10\n8 11\n10 11\n10 12\n\n");
        printf("Il tuo programma stampa:\n");
        graph_print(g);
    } else if (strcmp(argv[1], "cc") == 0) {
        FILE *f = fopen("graph.in", "r");
        assert(f != NULL);
        graph *g = graph_read_ff(f);
        fclose(f);

        printf("\nComponenti connesse\n");
        printf("Di ogni componente connessa viene stampata la lista dei nodi che ne fanno parte (l'ordine non è importante)\n\n");
        printf("1 2 3 4 5 6 7\n8 9 10 11 12\n\n");
        printf("Il tuo programma stampa:\n");
        connectedComponents(g);
        printf("\n");
    } else if (strcmp(argv[1], "distance") == 0) {
        graph_node *s;
        FILE *f = fopen("graph.in", "r");
        assert(f != NULL);
        graph *g = graph_read_ff(f);
        fclose(f);
        
        linked_list_iterator *it = linked_list_iterator_new(g->nodes);
        linked_list_iterator_next(it);
        s = linked_list_node_getvalue(linked_list_iterator_next(it));
        
        printf("Distanze dal nodo avente etichetta 2 (numero minimo di archi per raggiungere il nodo 2):\n");
        printf("nodo distanza\n");
        printf("2 0\n1 1\n3 2\n6 2\n4 3\n7 3\n5 4\n\n");
        printf("Il tuo programma stampa:\n");
        distances(g, s);
        printf("\n");
        
        linked_list_iterator_next(it);
        linked_list_iterator_next(it);
        linked_list_iterator_next(it);
        linked_list_iterator_next(it);
        linked_list_iterator_next(it);
        s = linked_list_node_getvalue(linked_list_iterator_next(it));
        printf("Distanze dal nodo avente etichetta 8 (numero minimo di archi per raggiungere il nodo 8):\n");
        printf("nodo distanza\n");
        printf("8 0\n9 1\n10 1\n11 1\n12 2\n\n");
        printf("Il tuo programma stampa:\n");
        distances(g, s);
        printf("\n");
        
    }
} //main

