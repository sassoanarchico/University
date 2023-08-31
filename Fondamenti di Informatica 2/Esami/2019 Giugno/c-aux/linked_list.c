#include "linked_list.h"
#include "stdlib.h"
#include "stdio.h"

struct linked_list_iterator {
    linked_list *ll;
    linked_list_node *current;
    linked_list_node *previous;
    linked_list_node *next;
    int just_removed;
};

linked_list * linked_list_new() {
    linked_list * ptr = (linked_list *) malloc(sizeof(linked_list));
    ptr->head = NULL;
    ptr->tail = NULL;
    ptr->size = 0;
    return ptr;
}

void linked_list_insert_head(linked_list * ll, void * value){
    linked_list_node *to_put = malloc(sizeof(linked_list_node));
    to_put->value = value;
    to_put->next = ll->head;
    to_put->pred = NULL;
    if(ll->head != NULL) ll->head->pred = to_put; // lista non vuota
    else ll->tail = to_put; // lista vuota
    ll->head = to_put;
    (ll->size)++;
}

void linked_list_insert_tail(linked_list * ll, void * value) {
    linked_list_node * added = (linked_list_node *)malloc(sizeof(linked_list_node));
    added->next = NULL;
    added->value = value;

    if (ll->tail != NULL) {
        ll->tail->next = added;
        added->pred = ll->tail;
    } else { // lista vuota
        added->pred = NULL;
        ll->head = added;       
    }

    ll->tail = added;
    (ll->size)++;
}

void linked_list_add(linked_list * ll, void * value) {
    return linked_list_insert_tail(ll, value);
}

void linked_list_insert_after(linked_list * ll, linked_list_node *predec, void * value) {
    if(predec == NULL) // as first
        return linked_list_insert_head(ll, value);
    else if(predec == ll->tail) return linked_list_insert_tail(ll, value);
    
    linked_list_node * added = (linked_list_node *)malloc(sizeof(linked_list_node));
    added->next = predec->next;
    added->pred = predec;
    added->value = value;
    predec->next = added;
    added->next->pred = added;

    (ll->size)++;
}

static void *linked_list_remove_given_element(linked_list * ll, linked_list_node *node) {
    if (node == NULL) return NULL;
    if(node->pred != NULL)
        node->pred->next = node->next;
    if(node->next != NULL)
        node->next->pred = node ->pred;
    if(node == ll->head) ll->head = node->next;
    if(node == ll->tail) ll->tail = node->pred;
    void *to_ret = node->value;
    free(node);
    (ll->size)--;
    return to_ret;
}

void* linked_list_remove_head(linked_list * ll){
    if(ll == NULL) return NULL;
    return linked_list_remove_given_element(ll, ll->head);
/*
    if (ll->size <= 0)
        return NULL;
    linked_list_node *to_rem = ll->head;
    ll->head = ll->head->next;
    if (ll->size == 1)
        ll->tail = NULL;
    else ll->head->next->pred = NULL;
    (ll->size)--;
    void* to_ret = to_rem->value;
    free(to_rem);
    return to_ret;
*/
}

void* linked_list_remove_tail(linked_list * ll){
    if(ll == NULL) return NULL;
    return linked_list_remove_given_element(ll, ll->tail);
/*
    if (ll->size <= 0)
        return NULL;
    linked_list_node *to_rem = ll->head;
    ll->head = ll->head->next;
    if (ll->size == 1)
        ll->tail = NULL;
    else ll->head->next->pred = NULL;
    (ll->size)--;
    void* to_ret = to_rem->value;
    free(to_rem);
    return to_ret;
*/
}

void *linked_list_node_getvalue(linked_list_node* node) {
    if (node)
        return node->value;
    return NULL;
}

int linked_list_size(linked_list *ll) {
    if (ll) {
        return ll->size;
    }
    else {
        printf("NullPointerException in linked_list_size, returning 0\n");
        return 0;
    }
}

int linked_list_contains(linked_list *ll, void *value) {
    if(ll == NULL) return 0;
    int ret = 0;
    linked_list_iterator *i = linked_list_iterator_new(ll);
    while(linked_list_iterator_hasnext(i)) 
        if(linked_list_node_getvalue(linked_list_iterator_next(i)) == value) {
            ret = 1;
            break;
        }
    linked_list_iterator_delete(i);
    return ret;
}

void linked_list_print(linked_list * ll){
    if(ll == NULL)
        printf("NullPointerException in linked_list_print\n");
    linked_list_node *cur = ll->head;
    printf("[ ");
    while (cur) {
        (cur->next) ? printf("%p, ", (cur->value)) : printf("%p", (cur->value));
        cur = cur->next;
    }
    printf(" ]\n");
    printf("size: %d - head: %p - tail: %p\n", ll->size,
        ll->head != NULL ? ll->head->value : NULL,
        ll->tail != NULL ? ll->tail->value : NULL);
    /*if (ll->head != NULL && ll->head->next != NULL)
        printf("nxtHead: %p \n", ll->head->next->value);
    if (ll->tail != NULL && ll->tail->next != NULL)
        printf("nxtTail: %p \n", ll->tail->next->value);*/
}

void linked_list_delete(linked_list *l) {
    if (l == NULL) {
        return;
    }
    linked_list_node * it = l->head;

    while (it) {
        linked_list_node * rem = it;
        it = it->next;
        free(rem);
    }
    free(l);
    return;
}

/*
static void *linked_list_remove(linked_list * ll, int pos) {
    if (pos<0 || pos >(ll->size) - 1) {
        printf("linked_list indexOutOfBound Exception in linked_list_remove for pos:%d\n", pos);
        return NULL;
    }
    if (pos == 0)
        return linked_list_remove_head(ll);
    else {
        linked_list_node *cur = ll->head;
        int i;
        for (i = 0; i < pos; i++) cur = cur->next;
        return linked_list_remove_given_element(ll, cur);
    }
}
*/

linked_list_iterator * linked_list_iterator_new(linked_list *ll) {
    if (ll == NULL) {
        printf("ERROR - NullPointerException in linked_list_iterator_new\n");
        exit(1);
    }
/*  if (ll->size == 0)
        return NULL;*/ // in java lista vuota non dà iter. null
    linked_list_iterator * to_ret = malloc(sizeof(linked_list_iterator));
    to_ret->ll = ll;
    to_ret->just_removed = 0;
    to_ret->next = ll->head;
    to_ret->previous = to_ret->current = NULL;
    return to_ret;
}

int linked_list_iterator_hasnext(linked_list_iterator * iter){
    if(iter == NULL) return 0;
    return iter->next != NULL;
}

//void * linked_list_iterator_next(linked_list_iterator * iter) {
linked_list_node * linked_list_iterator_next(linked_list_iterator * iter) {
    if(iter == NULL) return NULL;
    if(!iter->just_removed) iter->previous = iter->current;
    else iter->just_removed = 0;
    iter->current = iter->next;
    if(iter->next != NULL) iter->next = iter->next->next; // else non necessario
    return iter->current; 
}



void *linked_list_iterator_remove(linked_list_iterator * iter){
    if (iter->just_removed)
        return NULL;    
    void *to_ret = linked_list_remove_given_element(iter->ll, iter->current);
    iter->just_removed = 1;
    return to_ret;
}

/*
 * void * linked_list_iterator_getvalue(linked_list_iterator *iter) {
    if(iter == NULL) return NULL;
    if(iter->just_removed) return NULL;
    return iter->current->value;
}
*/

void linked_list_iterator_delete(linked_list_iterator * iter){
    free(iter);
}
