#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum {UNEXPLORED, EXPLORED, EXPLORING} STATUS;

struct graph_node{
    void * value;
    linked_list * out_edges;

    // keep track status
    STATUS state;
    int timestamp;
};

struct graph_prop {
	int n_vertices;
	int n_edges;
}graph_prop;

struct graph{
    linked_list * nodes;
	struct graph_prop* properties;
};

static void DFS(graph_node*);
static void DFS_fill_cc(graph_node*, linked_list*);
static void DFS_print_edges(graph_node*);

graph * graph_new() {
	graph * g = (graph *) malloc(sizeof(graph));
    g->nodes = linked_list_new();
	g->properties = (struct graph_prop*)malloc(sizeof(graph_prop));
	g->properties->n_edges = 0;
	g->properties->n_vertices = 0;
    return g;
}

linked_list * graph_get_nodes(graph * g) {
	return g->nodes;
}

linked_list * graph_get_neighbors(graph * g, graph_node * n) {
    return n->out_edges;
}

graph_node * graph_add_node(graph * g, void * value) {
	linked_list_iterator *it = linked_list_iterator_new(g->nodes);
	for (; it;) {
		linked_list_iterator *itera = linked_list_iterator_next(it);
		if (*((char*)graph_get_node_value(((graph_node*)linked_list_iterator_getvalue(it)))) == *((char*)value)) {
			return (graph_node*)linked_list_iterator_getvalue(it);
		}
		it = itera;
	}
	graph_node * n = (graph_node *) malloc(sizeof(graph_node));
	n->value = value;
    n->out_edges = linked_list_new();
	n->state = UNEXPLORED;
    linked_list_add(g->nodes, (void *) n);
	(g->properties->n_vertices)++;
    return n;
}

void graph_add_edge(graph * g, graph_node * v1, graph_node * v2) {
    linked_list_add(v1->out_edges, (void *) v2);
    linked_list_add(v2->out_edges, (void *) v1);
	(g->properties->n_edges)++;
}

void * graph_get_node_value(graph_node * n) {
	return n->value;
}

static void graph_remove_edge_aux(graph* g, graph_node* v1, graph_node* v2) {
	linked_list_iterator* it = linked_list_iterator_new(g->nodes);
	while (it != NULL) {
		graph_node* n = (graph_node*)linked_list_iterator_getvalue(it);
		if (graph_get_node_value(n) == graph_get_node_value(v1)) {
			linked_list_node *it2_head = (n->out_edges->head);
			linked_list_node *it2_tail = (n->out_edges->tail);
			if (((graph_node*)(it2_head->value)) == v2) {
				linked_list_node* to_remove = it2_head;
				if (to_remove == it2_tail) {
					free(to_remove);
					free(n->out_edges);
					n->out_edges = linked_list_new();
					return;
				}
				else {
					n->out_edges->head = it2_head->next;
					free(to_remove);
					(g->nodes->size)--;
					return;
				}
			}
			while (it2_head != NULL) {
				if (it2_head->next != NULL) {
					if (((graph_node*) (it2_head->next->value)) == v2) {
						linked_list_node* to_remove = it2_head->next;
						if (to_remove == it2_tail)
							n->out_edges->tail = it2_head;
						it2_head->next = it2_head->next->next;
						free(to_remove);
						(g->nodes->size)--;
						return;
					}
				}
				it2_head = it2_head->next;
			}
		}
		it = (linked_list_iterator*)linked_list_iterator_next(it);
	}
}

void graph_remove_edge(graph* g, graph_node* v1, graph_node* v2) {
	graph_remove_edge_aux(g, v1, v2);
	graph_remove_edge_aux(g, v2, v1);
	(g->properties->n_edges)--;
}

void graph_remove_node(graph* g, graph_node* v) {
	linked_list_iterator* it = linked_list_iterator_new(g->nodes);
	linked_list_node* head = (linked_list_node*)it;
	graph_node* head_node = ((graph_node*)(head->value));
	// Case remove head
	if (head_node == v) {
		linked_list_iterator* it2 = linked_list_iterator_new(head_node->out_edges);
		for (; it2 != NULL; ) {
			linked_list_iterator * itera = linked_list_iterator_next(it2);
			graph_node* v2 = (graph_node*)(((linked_list_node*)it2)->value);
			graph_remove_edge(g, head_node, v2);
			it2 = itera;
		}
		if (g->nodes->head == g->nodes->tail) {
			linked_list_delete(head_node->out_edges);
			free(head_node);
			free(head->next);
			linked_list_delete(g->nodes);
			g->nodes = linked_list_new();
			(g->properties->n_vertices)--;
			return;
		}
		g->nodes->head = head->next;
		linked_list_delete(head_node->out_edges);
		free(head_node);
		free(head);
		(g->properties->n_vertices)--;
		return;
	}
	else {
		for (; it != NULL; it = linked_list_iterator_next(it)) {
			linked_list_node* nxt = (linked_list_node*)linked_list_iterator_next(it);
			if (nxt == NULL)
				return;
			graph_node* nxt_node = (graph_node*)(nxt->value);
			int found = 0;
			if (nxt_node == v) {
				found = 1;
				linked_list_iterator* it2 = linked_list_iterator_new(nxt_node->out_edges);
				for (; it2 != NULL; ) {
					linked_list_iterator* itera = linked_list_iterator_next(it2);
					graph_node* v2 = (graph_node*)(((linked_list_node*)it2)->value);
					graph_remove_edge(g, nxt_node, v2);
					it2 = itera;
				}
			}
			if (found) {
				linked_list_node* cur_node = (linked_list_node*)it;
				cur_node->next = nxt->next;
				linked_list_delete(nxt_node->out_edges);
				if (g->nodes->tail == nxt)
					g->nodes->tail = (linked_list_node*)it;
				free(nxt_node);
				free(nxt);
				(g->properties->n_vertices)--;
				return;
			}
		}
	}
}

void graph_delete(graph * g) {
	if (g == NULL)
		return;
	linked_list_iterator * i = linked_list_iterator_new(g->nodes);
	while (i != NULL) {
		graph_node * n = (graph_node*)linked_list_iterator_getvalue(i);
		free(n->value);
		linked_list_delete(n->out_edges);
		i = linked_list_iterator_next(i);
	}
    linked_list_delete(g->nodes);
	free(g->properties);
    free(g);
}

graph* graph_read_ff(FILE* input) {
	graph* ret = graph_new();
	if (input == NULL)
		return ret;
	int v, e;
	fscanf(input, "%d", &v);
	fscanf(input, "%d", &e);

	int i;
	for (i = 0; i < e; i++) {
		void *v1 = malloc(sizeof(int));
		void *v2 = malloc(sizeof(int));
		fscanf(input, " %c", (char*)v1);
		fscanf(input, "	%c", (char*)v2);
		graph_node* gv1 = graph_add_node(ret, v1);
		graph_node* gv2 = graph_add_node(ret, v2);
		graph_add_edge(ret, gv1, gv2);
	}
	if ((ret->properties->n_vertices) < v) {
		int rem = v - (ret->properties->n_vertices);
		int name = (v + 1);
		for (int i = 0; i < rem; i++, name++) {
			void *v1 = malloc(sizeof(int));
			printf("Indicare un carattere per rappresentare il nodo %d senza archi: ", i+1);
			scanf(" %c", (char*)v1);
			graph_add_node(ret, v1);
		}
	}
	return ret;
}

void graph_print(graph* g) {
	printf("%d %d\n", g->properties->n_vertices, g->properties->n_edges);
	linked_list_iterator* it = linked_list_iterator_new(g->nodes);
	while (it) {
		linked_list_iterator* itera = linked_list_iterator_next(it);
		graph_node* current = (graph_node*)linked_list_iterator_getvalue(it);
		if (current->state == UNEXPLORED) {
			DFS_print_edges(current);
		}
		it = itera;
	}
}

void graph_print_adj(graph* g) {
	linked_list * nodes = graph_get_nodes(g);
	linked_list_iterator * lli = linked_list_iterator_new(nodes);
	//printf("Head: %s, Tail:%s\n", (char*)(((graph_node*)(nodes->head->value))->value), (char*)(((graph_node*)(nodes->tail->value))->value));
	while (lli != NULL) {
		graph_node * node = (graph_node *)linked_list_iterator_getvalue(lli);
		printf("%s : ", (char *)graph_get_node_value(node));

		linked_list * neighbors = graph_get_neighbors(g, node);
		/*if (neighbors == NULL)
		printf("STRANO\n");
		else if ((neighbors->head == neighbors->tail) && neighbors->head == NULL)
		printf("VUOTO");
		else
		printf("Head %s, Tail %s ->", (char*)graph_get_node_value((graph_node*)neighbors->head->value), (char*)graph_get_node_value((graph_node*)neighbors->tail->value));
		*/
		linked_list_iterator * inner_lli = linked_list_iterator_new(neighbors);
		while (inner_lli != NULL) {
			graph_node * n = (graph_node *)linked_list_iterator_getvalue(inner_lli);
			printf("%s ", (char *)graph_get_node_value(n));
			inner_lli = linked_list_iterator_next(inner_lli);
		}
		printf("\n");

		lli = linked_list_iterator_next(lli);
	}
}

static void DFS(graph_node* node) {
	node->state = EXPLORING;
	linked_list_iterator* it = linked_list_iterator_new(node->out_edges);
	for (; it;) {
		linked_list_iterator* itera = linked_list_iterator_next(it);
		graph_node* nxt = (graph_node*)linked_list_iterator_getvalue(it);
		if (nxt->state == UNEXPLORED)
			DFS(nxt);
		it = itera;
	}
	node->state = EXPLORED;
}

static void DFS_fill_cc(graph_node* node, linked_list* list) {
	node->state = EXPLORING;
	linked_list_add(list, node);
	linked_list_iterator* it = linked_list_iterator_new(node->out_edges);
	for (; it;) {
		linked_list_iterator* itera = linked_list_iterator_next(it);
		graph_node* nxt = (graph_node*)linked_list_iterator_getvalue(it);
		if (nxt->state == UNEXPLORED)
			DFS_fill_cc(nxt, list);
		it = itera;
	}
	node->state = EXPLORED;
}

static void DFS_print_edges(graph_node* node) {
	if (node->state != UNEXPLORED)
		return;
	node->state = EXPLORING;
	linked_list_iterator* it = linked_list_iterator_new(node->out_edges);
	while (it) {
		linked_list_iterator* itera = linked_list_iterator_next(it);
		graph_node* cur_edg = (graph_node*)linked_list_iterator_getvalue(it);
		if (cur_edg->state == UNEXPLORED)
			printf("%s %s\n", (char*)(node->value), (char*)(cur_edg->value));
		it = itera;
	}
	it = linked_list_iterator_new(node->out_edges);
	while (it) {
		linked_list_iterator* itera = linked_list_iterator_next(it);
		graph_node* cur_edg = (graph_node*)linked_list_iterator_getvalue(it);
		if (cur_edg->state == UNEXPLORED)
			DFS_print_edges(cur_edg);
		it = itera;
	}
	node->state = EXPLORED;
}

int graph_n_con_comp(graph * g) {
	int ret = 0;
	linked_list_iterator* it = linked_list_iterator_new(g->nodes);
	for (; it;) {
		linked_list_iterator* itera = linked_list_iterator_next(it);
		graph_node* current = (graph_node*)linked_list_iterator_getvalue(it);
		if (current->state == UNEXPLORED) {
			ret++;
			DFS(current);
		}
		it = itera;
	}
	return ret;
}

linked_list* graph_get_con_comp(graph* g) {
	linked_list* ret = linked_list_new();
	linked_list_iterator* it = linked_list_iterator_new(g->nodes);
	for (; it;) {
		linked_list_iterator* itera = linked_list_iterator_next(it);
		graph_node* current = (graph_node*)linked_list_iterator_getvalue(it);
		if (current->state == UNEXPLORED) {
			graph* to_add = graph_new();
			linked_list_add(ret, to_add);
			DFS_fill_cc(current, to_add->nodes);
		}
		it = itera;
	}
	return ret;
}