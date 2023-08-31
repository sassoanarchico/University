#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "graph_services.h"

void print_help() {
	printf("Richiesto argomento: {maxdist}\n");
}

int main(int argc, char** argv) {
	graph *gra = graph_new();

	graph_node *a = graph_add_node(gra, "a");
	graph_node *b = graph_add_node(gra, "b");
	graph_node *c = graph_add_node(gra, "c");
	graph_node *d = graph_add_node(gra, "d");
	graph_node *e = graph_add_node(gra, "e");
	graph_node *f = graph_add_node(gra, "f");
	graph_node *g = graph_add_node(gra, "g");

	graph_add_edge(gra, a, b);
	graph_add_edge(gra, a, c);
	graph_add_edge(gra, a, e);
	graph_add_edge(gra, b, c);
	graph_add_edge(gra, b, d);
	graph_add_edge(gra, c, e);
	graph_add_edge(gra, c, d);
	graph_add_edge(gra, d, f);
	graph_add_edge(gra, d, g);
	graph_add_edge(gra, e, d);
	graph_add_edge(gra, e, f);
	graph_add_edge(gra, f, g);


	printf("Grafo:\n\n");
	graph_print(gra);
	printf("\n");
	printf("Nodo sorgente a: k = 2\n");
	printf("Il tuo programma dovrebbe stampare: a b c d e f\n");
	printf("il tuo programma stampa: ");
	kdist(gra, a, 2);
	printf("\n");
	printf("\n");
	printf("Nodo sorgente e: k = 1\n");		
	printf("Il tuo programma dovrebbe stampare: e d f\n");
	printf("il tuo programma stampa: ");
	kdist(gra, e, 1);
	printf("\n");
	printf("\n");
	printf("Nodo sorgente g: k = 3\n");		
	printf("Il tuo programma dovrebbe stampare: g\n");
	printf("il tuo programma stampa: ");
	kdist(gra, g, 3);
	printf("\n");
	graph_delete(gra);
}


