#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "graph_services.h"

void print_help() {
	printf("Richiesto argomento: {bfs}\n");
}

int main(int argc, char** argv) {
	if (argc != 2) {
		print_help();
		return EXIT_FAILURE;
	}
	else if (strcmp(argv[1], "bfs") == 0) {
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
		printf("BFS da A: \n");
		printf("Il tuo programma dovrebbe stampare: \n");
		printf("Livello A: 0\nLivello B: 1\nLivello C: 2\nLivello D: 4\nLivello E: 3\nLivello F: 4 \n\n");
		printf("Il tuo programma stampa: \n");
		bfs(gra, a);
		printf("\n");
		printf("BFS da F: \n");		
		printf("Il tuo programma dovrebbe stampare: \n");
		printf("Livello F: 0 \n");
		printf("Il tuo programma stampa: \n");
		bfs(gra, f);
		
		graph_delete(gra);
	}
}

