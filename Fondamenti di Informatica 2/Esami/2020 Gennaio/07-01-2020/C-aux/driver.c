#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "graph_services.h"

	
int main(int argc, char **argv) {
	graph *gra = graph_new();
	
	graph_node *a = graph_add_node(gra, "a");
	graph_node *b = graph_add_node(gra, "b");
	graph_node *c = graph_add_node(gra, "c");
	graph_node *d = graph_add_node(gra, "d");
	graph_node *e = graph_add_node(gra, "e");
	graph_node *f = graph_add_node(gra, "f");
			
	graph_add_edge(gra, a, b, 2);
	graph_add_edge(gra, a, c, 1);
	graph_add_edge(gra, a, d, 5);
	graph_add_edge(gra, b, c, 2);
	graph_add_edge(gra, b, d, 3);
	graph_add_edge(gra, c, d, 3);
	graph_add_edge(gra, c, e, 1);		
	graph_add_edge(gra, e, d, 1);
	graph_add_edge(gra, d, f, 5);		
	graph_add_edge(gra, e, f, 2);
		
	printf("Grafo:\n");
	graph_print(gra);
		
				
		
	// Test per BFS
	printf("BFS da a: \n");
	printf("\n");
	printf("Il tuo programma dovrebbe stampare:\n");
	printf("Livello a: 0\nLivello b: 1\nLivello c: 1\nLivello d: 1\nLivello e: 2\nLivello f: 2\n");
	printf("\n");
	printf("Il tuo programma stampa:\n");
	bfs(gra, a); 
	printf("\n");
	printf("BFS da f: \n");
	printf("\n");
	printf("Il tuo programma dovrebbe stampare:\n");
	printf("Livello f: 0\n");
	printf("\n");
	printf("Il tuo programma stampa:\n");
	bfs(gra, f); 
	printf("\n");
		
	// Test per SSSP
	printf("SSSP dal nodo 'a':\n");
	printf("\n");
	printf("Il tuo programma dovrebbe stampare:\n");
	printf("Distanze dal nodo a [a:0, b:2, d:3, c:1, e:2, f:4]\n");
	printf("\n");
	printf("Il tuo programma stampa:\n");
	sssp(gra, a);
	printf("\n");

	printf("SSSP dal nodo 'c':\n");
	printf("\n");
	printf("Il tuo programma dovrebbe stampare:\n");
	printf("Distanze dal nodo c [a:100000, b:100000, d:2, c:0, e:1, f:3]\n");
	printf("\n");
	printf("Il tuo programma stampa:\n");
	sssp(gra, c);
	printf("\n");
	
	// Test per APSP
	printf("APSP:\n");
	printf("\n");
	printf("Il tuo programma dovrebbe stampare:\n");
	printf("Distanze dal nodo a [a:0, b:2, d:3, c:1, e:2, f:4]\n" 
						"Distanze dal nodo b [a:100000, b:0, d:3, c:2, e:3, f:5]\n" 
						"Distanze dal nodo d [a:100000, b:100000, d:0, c:100000, e:100000, f:5]\n" 
						"Distanze dal nodo c [a:100000, b:100000, d:2, c:0, e:1, f:3]\n" 
						"Distanze dal nodo e [a:100000, b:100000, d:1, c:100000, e:0, f:2]\n" 
						"Distanze dal nodo f [a:100000, b:100000, d:100000, c:100000, e:100000, f:0]\n");
	printf("\n");
	printf("Il tuo programma stampa:\n");
	apsp(gra);
	printf("\n");
	
	return 0;
}
