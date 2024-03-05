#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "polimorphic_list.h"

// -------------------------------------------------------------------- //
// -------------------------------------------------------------------- //
// -------------------------------------------------------------------- //
void List_init(ListHead* head) {
  head->first=0;
  head->last=0;
  head->size=0;
}

ListItem* List_find(ListHead* head, ListItem* item) {
  // linear scanning of list
  ListItem* aux=head->first;
  while(aux){
    if (aux==item)
      return item;
    aux=aux->next;
  }
  return 0;
}

ListItem* List_insert(ListHead* head, ListItem* prev, ListItem* item) {
  if (item->next || item->prev)
    return 0;
  
#ifdef _LIST_DEBUG_
  // we check that the element is not in the list
  ListItem* instance=List_find(head, item);
  assert(!instance);

  // we check that the previous is inthe list

  if (prev) {
    ListItem* prev_instance=List_find(head, prev);
    assert(prev_instance);
  }
  // we check that the previous is inthe list
#endif

  ListItem* next= prev ? prev->next : head->first;
  if (prev) {
    item->prev=prev;
    prev->next=item;
  }
  if (next) {
    item->next=next;
    next->prev=item;
  }
  if (!prev)
    head->first=item;
  if(!next)
    head->last=item;
  ++head->size;
  return item;
}

ListItem* List_detach(ListHead* head, ListItem* item) {

#ifdef _LIST_DEBUG_
  // we check that the element is in the list
  ListItem* instance=List_find(head, item);
  assert(instance);
#endif

  ListItem* prev=item->prev;
  ListItem* next=item->next;
  if (prev){
    prev->next=next;
  }
  if(next){
    next->prev=prev;
  }
  if (item==head->first)
    head->first=next;
  if (item==head->last)
    head->last=prev;
  head->size--;
  item->next=item->prev=0;
  return item;
}


// -------------------------------------------------------------------- //
// -------------------------------------------------------------------- //
// -------------------------------------------------------------------- //
void ListItem_construct(ListItem* item, ListItemOps* ops) {
  assert(item && "ListItem_construct|ERROR, invalid item");
  assert(ops && "ListItem_construct|ERROR, invalid ops");

  //ia it's still unconnected
  item->prev = 0;
  item->next = 0;
  
  //ia assign the ops to the VMT
  item->ops = ops;
}

void ListItem_destroy(ListItem* item) {
  assert(item && "ListItem_destroy|ERROR, invalid item");

  //ia check that there is a dtor function
  if (item->ops && item->ops->dtor_fn) {
    (*item->ops->dtor_fn)(item);
  }
}
void ListItem_print(ListItem* item) {
  assert(item && "ListItem_print|ERROR, invalid item");

  //ia check that there is a print function
  if (item->ops && item->ops->print_fn) {
    (*item->ops->print_fn)(item);
  }
}

void List_print(ListHead* head) {
  assert(head && "List_print|ERROR, invalid list");
  if (!head->size || !head->first) {
    return;
  }

  printf("List_print|printing list [ %p ]\n", head);
  ListItem* aux = head->first;
  int item_num = 0;
  while (aux) {
    printf("[ %d ] - ", item_num++);
    ListItem_print(aux);
    printf("\n");
    aux = aux->next;
  }
}

void List_destroy(ListHead* head) {
  assert(head && "List_destroy|ERROR, invalid list");
  printf("List_destroy|destroying\n");
  if (!head->size || !head->first) {
    return;
  }

  while (head->first) {
    ListItem* item = List_detach(head, head->first);
    ListItem_destroy(item);
    free(item);
  }
}

