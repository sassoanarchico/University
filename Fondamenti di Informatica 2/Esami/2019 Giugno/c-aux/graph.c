#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

//#define DEBUG

static int progress = 0;


static void DFS_print_edges(graph_node*);

graph * graph_new() {
    graph * g = (graph *) malloc(sizeof(graph));
    g->nodes = linked_list_new();
    g->n_edges = 0;
    g->n_nodes = 0;
    return g;
}

int get_no_nodes(graph *g) {
    return g->n_nodes;
}

int get_no_edges(graph *g) {
    return g->n_edges;
}

linked_list * graph_get_nodes(graph * g) {
    linked_list *graph_nodes = linked_list_new();
    linked_list_iterator *i = linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(i))
        linked_list_insert_tail(graph_nodes, linked_list_node_getvalue(linked_list_iterator_next(i)));
    return graph_nodes; // ritorna nuova lista con stessi nodi (non clonati)
}

linked_list * graph_get_neighbors(graph * g, graph_node * n) {
    linked_list *neighbors = linked_list_new();
    linked_list_iterator *i = linked_list_iterator_new(n->out_edges);
    while(linked_list_iterator_hasnext(i))
        linked_list_insert_tail(neighbors, linked_list_node_getvalue(linked_list_iterator_next(i)));
    return neighbors; // ritorna nuova lista con stessi adiacenti (non clonati)
}

graph_node * graph_add_node(graph * g, int value) {
#ifdef DEBUG
printf("entro graph_add_node\n");
#endif    
    linked_list_iterator *it = linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(it)) {
#ifdef DEBUG
printf("dentro while per cercare se nodo esiste già\n");
#endif    
        graph_node *n = (graph_node*)linked_list_node_getvalue(linked_list_iterator_next(it));
#ifdef DEBUG
printf("estratto il graph_node\n");
assert(n != NULL);
#endif    
        if(n->value == value) return n;
    }
#ifdef DEBUG
printf("non c'è\n");
#endif    
    
    graph_node * n = (graph_node *) malloc(sizeof(graph_node));
    n->value = value;
    n->key = progress++;
    n->out_edges = linked_list_new();
    n->state = UNEXPLORED;
    linked_list_insert_tail(g->nodes, n);
    g->n_nodes++;
#ifdef DEBUG
 printf("esco graph_add_node\n");
 linked_list_print(g->nodes);
#endif    
   return n;
}

void graph_add_edge(graph * g, graph_node * v1, graph_node * v2) {
        /* DA IMPLEMENTARE */     
}

int graph_get_node_value(graph_node * n) {
    return n->value;
}

int graph_get_node_key(graph_node * n) {
    return n->key;
}

static void graph_remove_edge_aux(graph* g, graph_node* v1, graph_node* v2) {
    linked_list_iterator* it = linked_list_iterator_new(v1->out_edges);
    while (linked_list_iterator_hasnext(it))
        if(linked_list_node_getvalue(linked_list_iterator_next(it)) == v2) {
            linked_list_iterator_remove(it);
            linked_list_iterator_delete(it);
            return;
        }
    printf("tentativo cancellazione adiacenza inesistente\n");
    linked_list_iterator_delete(it);
    return;
}
        
        

void graph_remove_edge(graph* g, graph_node* v1, graph_node* v2) {
    if(!linked_list_contains(g->nodes, v1)) return;
    if(!linked_list_contains(g->nodes, v2)) return;
    graph_remove_edge_aux(g, v1, v2);
    graph_remove_edge_aux(g, v2, v1);
    (g->n_edges)--;
}

void graph_remove_node(graph* g, graph_node* v) {
    if(!linked_list_contains(g->nodes, v)) return;
    linked_list *neighb = graph_get_neighbors(g, v);
    linked_list_iterator *it = linked_list_iterator_new(neighb);
    while(linked_list_iterator_hasnext(it)) 
        graph_remove_edge(g, v, linked_list_node_getvalue(linked_list_iterator_next(it)));
    linked_list_delete(neighb);
    
    it = linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(it)) 
        if(linked_list_node_getvalue(linked_list_iterator_next(it)) == v) {
            linked_list_iterator_remove(it);
            break;
        }
    linked_list_delete(v->out_edges);
    free(v);
    (g->n_nodes)--;
    return;
 }

/*
 * non serve - e non funziona, a causa del cambio su iteratori
 * 
void graph_delete(graph * g) {
    if (g == NULL)
        return;
    linked_list_iterator * i = linked_list_iterator_new(g->nodes);
    while (i != NULL) {
        graph_node * n = linked_list_node_getvalue(i);
        free(n->value);
        linked_list_delete(n->out_edges);
        i = linked_list_iterator_next(i);
    }
    linked_list_delete(g->nodes);
    free(g->properties);
    free(g);
}
*/

// assume non ci siano nodi isolati
graph* graph_read_ff(FILE* input) {
#ifdef DEBUG
printf("entro graph_read_ff\n");
#endif    
    graph* ret = graph_new();
#ifdef DEBUG
printf("creato grafo vuoto\n");
#endif    
    if (input == NULL)
        return ret;
    int v, e;
    fscanf(input, "%d", &v);
    fscanf(input, "%d", &e);
    int i;
    for (i = 0; i < e; i++) {
        int v1, v2;
        fscanf(input, "%d%d", &v1, &v2);
#ifdef DEBUG
printf("letto arco %d %d\n", v1, v2);
#endif    

        graph_node* gv1 = graph_add_node(ret, v1);
        graph_node* gv2 = graph_add_node(ret, v2);
        graph_add_edge(ret, gv1, gv2);
    }
#ifdef DEBUG
printf("esco da graph_read_ff\n");
#endif    

    return ret;
}

void graph_reset_node_status(graph *g) {
    linked_list_iterator *it = linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(it)) 
        ((graph_node*)(linked_list_node_getvalue(linked_list_iterator_next(it))))->state = UNEXPLORED;
    return;
}

void graph_print(graph* g) {
    STATUS *temp = malloc(g->n_nodes*sizeof(STATUS));  // salva stati
    linked_list_iterator *it = linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(it)) {
        graph_node *curr = (graph_node*)linked_list_node_getvalue(linked_list_iterator_next(it));
        temp[curr->key] = curr->state;
        curr->state = UNEXPLORED;
    }
        
    printf("%d %d\n", g->n_nodes, g->n_edges);
    it = linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(it)) {
        graph_node* current = (graph_node*)linked_list_node_getvalue(linked_list_iterator_next(it));
        if (current->state == UNEXPLORED) {
            DFS_print_edges(current);
        }
    }
    
    it = linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(it)) {
        graph_node *curr = (graph_node*)linked_list_node_getvalue(linked_list_iterator_next(it));
        curr->state = temp[curr->key];
    }
    
    free(temp);
    
}



static void DFS_print_edges(graph_node* node) {
    node->state = EXPLORING;
    linked_list_iterator* it = linked_list_iterator_new(node->out_edges);
    while (linked_list_iterator_hasnext(it)) {
        graph_node* cur_edg = linked_list_node_getvalue(linked_list_iterator_next(it));
        if (cur_edg->state == UNEXPLORED) {
			if (node->key < cur_edg->key) printf("%d %d\n", node->value, cur_edg->value);
            DFS_print_edges(cur_edg);
        } else
			if (node->key < cur_edg->key) printf("%d %d (back edge)\n", node->value, cur_edg->value);
    }
    node->state = EXPLORED;
}
