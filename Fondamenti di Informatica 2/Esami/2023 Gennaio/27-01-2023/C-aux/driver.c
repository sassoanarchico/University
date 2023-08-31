#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "graph_services.h"

void print_help() {
	printf("Richiesto argomento: {maxdist}\n");
}

int main(int argc, char** argv) {
	if (argc != 2) {
		print_help();
		return EXIT_FAILURE;
	}
	else if (strcmp(argv[1], "maxdist") == 0) {
		graph *gra = graph_new();

		graph_node *a = graph_add_node(gra, "A");
		graph_node *b = graph_add_node(gra, "B");
		graph_node *c = graph_add_node(gra, "C");
		graph_node *d = graph_add_node(gra, "D");
		graph_node *e = graph_add_node(gra, "E");
		graph_node *f = graph_add_node(gra, "F");

		graph_add_edge(gra, a, b);
		graph_add_edge(gra, b, c);
		graph_add_edge(gra, c, e);
		graph_add_edge(gra, e, d);
		graph_add_edge(gra, e, f);
		graph_add_edge(gra, d, b);

		printf("Grafo:\n\n");
		graph_print(gra);
		printf("\n");
		printf("Nodo sorgente A: \n");
		printf("Il tuo programma dovrebbe stampare: 4\n");
		printf("Il tuo programma stampa: %d\n", max_dist(gra, a));
		printf("\n");
		printf("Nodo sorgente E: \n");		
		printf("Il tuo programma dovrebbe stampare: 3\n");
		printf("Il tuo programma stampa: %d\n", max_dist(gra, a));
		printf("\n");
		graph_delete(gra);
	}
}

