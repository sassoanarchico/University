#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "linked_list.h"
#include <stdio.h>

typedef enum {UNEXPLORED, EXPLORED, EXPLORING} STATUS;


/**
* Grafo semplice non diretto rappresentato mediante lista delle adiacenze.
*/

typedef struct graph {
    linked_list* nodes;     // lista di graph_node
    int n_nodes;
    int n_edges;
} graph;

typedef struct graph_node {
    int key; // progressivo creazione, a partire da zero
    int timestamp;
    STATUS state;
    int value; // naturale letto da file 
    linked_list* out_edges;  // lista di adiacenza
} graph_node;


/**
* Crea un nuovo grafo vuoto.
*/
graph * graph_new();

/**
* Ritorna la lista dei nodi del grafo g. Notare che � possibile ottenere questa lista anche attraverso g->nodes.
*/
linked_list * graph_get_nodes(graph * g);

/**
* Ritorna la prossima chiave da assegnare al nodo di un qualsiasi grafo.
*/
int graph_get_next_node_key();


/**
* Aggiunge un nodo al grafo con la label specificata.
*/
graph_node * graph_add_node(graph * g, int val);

/**
* Aggiunge al grafo g un arco che collega i nodi n1 ed n2.
*/
void graph_add_edge(graph * g, graph_node * n1, graph_node * n2);

/**
* Ritorna la chiave del nodo n. Notare che e' possibile ottenere tale chiave anche attraverso n->key.
*/
int graph_get_node_key(graph_node * n);


/**
* Ritorna la label del nodo n. Notare che e' possibile ottenere tale label anche attraverso n->label.
*/
char* graph_get_node_label(graph_node* n);


/**
* Rimuove dal grafo g l'arco che collega i nodi v1 e v2. Libera solo la memoria assegnata all'arco.
*/
void graph_remove_edge(graph* g, graph_node* v1, graph_node* v2);

/**
* Rimuove il nodo v e tutti gli archi incidenti a v dal grafo g. Libera la memoria di entrambi il nodo e gli archi, ma non dei vertici
* opposti agli archi liberati.
*/
void graph_remove_node(graph* g, graph_node* v);

/**
* Cancella il grafo g e libera la memoria allocata per tutti i suoi nodi ed archi.
*/
void graph_delete(graph * g);

/**
* Stampa a video una rappresentazione del grafo g.
*/
void graph_print(graph* g);

/**
* legge da file (già aperto) un grafo e ne restituisce puntatore.
*/
graph* graph_read_ff(FILE* input);


#endif  /* __GRAPH_H__ */
