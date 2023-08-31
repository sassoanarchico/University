#include <stdio.h>

#include "graph.h"
#include "linked_list.h"
#include "graph_services.h"

static int sweep_aux(graph_node * source, int time, char * format_string) {
	if (source->status != UNEXPLORED)
		return 0;
	int loctime = 1;
	source->status = EXPLORING;
	source->timestamp = time;

	linked_list_iterator * lli = linked_list_iterator_new(source->out_edges);
	graph_node * u = (graph_node *)linked_list_iterator_getvalue(lli);
	while (linked_list_iterator_hasnext(lli)) {
		printf("\t");
		printf(format_string, source->value);
		printf("(%d)->", source->timestamp);
		printf(format_string, u->value);
		printf("(%d) ", u->timestamp);

		if (u->status == EXPLORED) {
			if (source->timestamp < u->timestamp)
				printf("FORWARD\n");
			else
				printf("CROSS\n");
		}
		else if (u->status == EXPLORING) {
			printf("BACK\n");
		}
		else {
			printf("TREE\n");
			loctime += sweep_aux(u, time + 1, format_string);
		}
		u = (graph_node*)linked_list_iterator_next(lli);
	}
	linked_list_iterator_delete(lli);
	source->status = EXPLORED;
	return loctime;
}

void sweep(graph * g, char * format_string) {
	linked_list_iterator * lli = linked_list_iterator_new(g->nodes);
	graph_node * n = (graph_node *)linked_list_iterator_getvalue(lli);
	while (linked_list_iterator_hasnext(lli)) {
		n->status = UNEXPLORED;
		n->timestamp = 0;
		n = (graph_node*)linked_list_iterator_next(lli);
	}
	linked_list_iterator_delete(lli);
	int loctime = 0;
	lli = linked_list_iterator_new(g->nodes);
	graph_node * node = (graph_node *)linked_list_iterator_getvalue(lli);
	while (linked_list_iterator_hasnext(lli)) {
		printf("Root ");
		printf(format_string, node->value);
		printf("\n");

		loctime += sweep_aux(node, loctime, format_string);
		node = (graph_node*)linked_list_iterator_next(lli);
	}
	linked_list_iterator_delete(lli);
}

static int DDFS(graph_node* node, linked_list* list) {
	if (node->status == EXPLORING)
		return 1;
	if (node->status == EXPLORED) {
		return 0;
	}
	node->status = EXPLORING;
	int ret = 0;
	linked_list_iterator* lli = linked_list_iterator_new(node->out_edges);
	graph_node* n = (graph_node*)linked_list_iterator_getvalue(lli);
	for (; linked_list_iterator_hasnext(lli); n = (graph_node*)linked_list_iterator_next(lli)) {
		ret += DDFS(n, list);
	}
	linked_list_iterator_delete(lli);
	node->status = EXPLORED;
	linked_list_add(list, 0 ,node);
	return ret;
}

void topological_sort(graph * g){
	linked_list_iterator * lli = linked_list_iterator_new(g->nodes);
	graph_node * n = (graph_node *)linked_list_iterator_getvalue(lli);
	while (linked_list_iterator_hasnext(lli)) {
		n->status = UNEXPLORED;
		n->timestamp = 0;
		n = (graph_node*)linked_list_iterator_next(lli);
	}
	linked_list_iterator_delete(lli);
	linked_list* list = linked_list_new();
	lli = linked_list_iterator_new(g->nodes);
	n = (graph_node*)linked_list_iterator_getvalue(lli);
	for (; linked_list_iterator_hasnext(lli); n = (graph_node*)linked_list_iterator_next(lli)) {
		if (n->status == UNEXPLORED) {
			if (DDFS(n, list)) {
				printf("Impossibile ottenere ordine topologico, il grafo non e' un DAG\n");
				linked_list_delete(list);
				linked_list_iterator_delete(lli);
				return;
			}
		}
	}
	linked_list_iterator_delete(lli);
	lli = linked_list_iterator_new(list);
	n = (graph_node*)linked_list_iterator_getvalue(lli);
	for (; linked_list_iterator_hasnext(lli); n = (graph_node*)linked_list_iterator_next(lli)) {
		printf("%s ", (char*)(n->value));
	}
	printf("\n");
	linked_list_delete(list);
	linked_list_iterator_delete(lli);
}

/* SOLUTION WITH ONLY OUT EDGES
static void transposed_DDFS(graph* g, graph_node * node, linked_list* list) {
	if (node->status != UNEXPLORED)
		return;
	node->status = EXPLORING;
	linked_list_iterator* it = linked_list_iterator_new(g->nodes);
	graph_node* to = (graph_node*)linked_list_iterator_getvalue(it);
	for (; linked_list_iterator_hasnext(it); to = linked_list_iterator_next(it)) {
		linked_list_iterator* it2 = linked_list_iterator_new(to->out_edges);
		graph_node* frm = (graph_node*)linked_list_iterator_getvalue(it2);
		for (; linked_list_iterator_hasnext(it2); frm = linked_list_iterator_next(it2)) {
			if (frm == node)
				transposed_DDFS(g, to, list);
		}
		linked_list_iterator_delete(it2);
	}
	linked_list_iterator_delete(it);
	linked_list_enqueue(list, node);
	node->status = EXPLORED;
}
*/

static void transposed_DDFS(graph_node* node, linked_list* list) {
	if (node->status != UNEXPLORED)
		return;
	node->status = EXPLORING;
	linked_list_iterator* lli = linked_list_iterator_new(node->in_edges);
	graph_node* n = (graph_node*)linked_list_iterator_getvalue(lli);
	for (; linked_list_iterator_hasnext(lli); n = (graph_node*)linked_list_iterator_next(lli)) {
		transposed_DDFS(n, list);
	}
	linked_list_iterator_delete(lli);
	node->status = EXPLORED;
	linked_list_enqueue(list, node);
}

void strong_connected_components(graph  *g) {
	// Reset status of nodes
	linked_list_iterator * lli = linked_list_iterator_new(g->nodes);
	graph_node * n = (graph_node *)linked_list_iterator_getvalue(lli);
	while (linked_list_iterator_hasnext(lli)) {
		n->status = UNEXPLORED;
		n->timestamp = 0;
		n = (graph_node*)linked_list_iterator_next(lli);
	}
	// Create the stack, first DFS
	linked_list* stack = linked_list_new();
	linked_list_iterator_delete(lli);
	lli = linked_list_iterator_new(g->nodes);
	n = (graph_node*)linked_list_iterator_getvalue(lli);
	for (; linked_list_iterator_hasnext(lli); n = (graph_node*)linked_list_iterator_next(lli)) {
		if (n->status == UNEXPLORED) {
			DDFS(n, stack);
		}
	}
	linked_list_iterator_delete(lli);
	// Reset status of nodes
	lli = linked_list_iterator_new(g->nodes);
	n = (graph_node *)linked_list_iterator_getvalue(lli);
	while (linked_list_iterator_hasnext(lli)) {
		n->status = UNEXPLORED;
		n->timestamp = 0;
		n = (graph_node*)linked_list_iterator_next(lli);
	}
	linked_list_iterator_delete(lli);
	// Second DFS on the transposed graph
	lli = linked_list_iterator_new(stack);
	n = (graph_node*)linked_list_iterator_getvalue(lli);
	for (; linked_list_iterator_hasnext(lli); n = (graph_node*)linked_list_iterator_next(lli)) {
		if (n->status == UNEXPLORED) {
			linked_list* ret = linked_list_new();
			transposed_DDFS(n, ret);
			linked_list_iterator *it2 = linked_list_iterator_new(ret);
			graph_node* cur = (graph_node*)linked_list_iterator_getvalue(it2);
			printf("Strong connected component:\n");
			for (; linked_list_iterator_hasnext(it2); cur = (graph_node*)linked_list_iterator_next(it2)) {
				printf("%s ", (char*)(cur->value));
			}
			printf("\n");
			linked_list_iterator_delete(it2);
			linked_list_delete(ret);
		}
	}
	linked_list_iterator_delete(lli);
	linked_list_delete(stack);
}
