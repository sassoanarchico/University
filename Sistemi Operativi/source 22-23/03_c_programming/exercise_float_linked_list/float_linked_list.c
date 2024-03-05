#include <stdio.h>
#include <stdlib.h>
#include "float_linked_list.h"

void FloatListItem_print(ListItem* item) {
  FloatListItem* f_item = (FloatListItem*)(item);
  assert(f_item && "FloatListItem_print|ERROR, invalid cast");
  printf("%.4f", f_item->value);
}

void FloatList_print(ListHead* head) {
  uint16_t num = 0;
  ListItem* aux = head->first;
  while (aux) {
    printf("[%d] - ",num++);
    FloatListItem_print(aux);
    printf("\n");
    aux = aux->next;
  }
}

void FloatList_destroy(ListHead* head) {
  printf("FloatList_destroy|destroying\n");

  //ia if list is already empty, just return
  if (!head->size || !head->first) {
    return;
  }

  ListItem* aux = head->first;
  while (aux) {
    FloatListItem* f_item = (FloatListItem*)(aux);
    assert(f_item && "FloatList_destroy|ERROR, invalid cast");

    //save next item before deleting
    aux = aux->next;

    free(f_item);
    
  }

  //ia release connections
  List_init(head);
}

void FloatListList_init(uint64_t target_rows,
                        uint64_t target_cols,
                        ListHead* head) {
  if (head->first || head->last) {
    printf("FloatListList_init|ERROR, already initialized\n");
    exit(EXIT_FAILURE);
  }

  for (uint64_t r = 0; r < target_rows; ++r) {
    FloatListListItem* r_item = (FloatListListItem*)(malloc(sizeof(FloatListListItem)));
    ListHead* r_list = &r_item->value;
    for (uint64_t c = 0; c < target_cols; ++c) {
      FloatListItem* c_item = (FloatListItem*)(malloc(sizeof(FloatListItem)));
      c_item->value = 0.f;
      List_insert(r_list, r_list->last, (ListItem*)c_item);
    }
    List_insert(head, head->last, (ListItem*)r_item);
  }
}

void FloatListList_destroy(ListHead* head) {
  printf("FloatListList_destroy|destroying\n");

  //ia check if we can skip working today :)
  if (!head->size || !head->first) {
    return;
  }

  ListItem* aux = head->first;
  while (aux) {
    FloatListListItem* r_item = (FloatListListItem*)(aux);
    assert(r_item && "FloatListList_destroy|ERROR, invalid cast");

    //ia destroy the colums
    FloatList_destroy(&r_item->value);

    //save next item before deleting
    aux = aux->next;

    //ia destroy the row
    free(r_item);

  }

  //ia release connections
  List_init(head);
}


void FloatListList_print(ListHead* head) {  
  ListItem* r_aux = head->first;

  //ia for each row
  uint64_t r = 0;
  while (r_aux) {
    
    FloatListListItem* row = (FloatListListItem*)(r_aux);
    assert(row && "FloatListList_print|ERROR, invalid cast");

    ListItem* c_aux = row->value.first;

    uint64_t c = 0;
    //ia for each col
    while (c_aux) {
      //ia actual print
      printf("[%ld, %ld] = ", r, c);
      FloatListItem_print(c_aux);
      printf("\n");
      
      //ia go forward
      c_aux = c_aux->next;
      ++c;
    }
    
    //ia go forward
    r_aux = r_aux->next;
    ++r;
  }
}


FloatListItem* FloatListList_at(ListHead* head,
                                uint64_t target_row,
                                uint64_t target_col) {
  assert(head && "FloatListList_at|ERROR, invalid list");
  assert(head->first && "FloatListList_at|ERROR, invalid list");
  assert(head->size && "FloatListList_at|ERROR, invalid list");
  FloatListItem* retval = 0;

  if (target_row < 0 || target_row >= head->size) {
    printf("FloatListList_at|ERROR, exceeded matrix rows\n");
    exit(EXIT_FAILURE);
  }

  uint64_t current_r = 0;
  ListItem* r_aux = head->first;
  while (r_aux) {
    FloatListListItem* row = (FloatListListItem*)(r_aux);
    assert(row && "FloatListList_at|ERROR, invalid cast");

    if (current_r++ != target_row) {
      r_aux = r_aux->next;
      continue;
    }

    uint64_t current_c = 0;
    ListHead* c_aux = &row->value;
    if (target_col < 0 || target_col >= c_aux->size) {
      printf("FloatListList_at|ERROR, exceeded matrix cols\n");
      exit(EXIT_FAILURE);
    }

    ListItem* c_item = c_aux->first;
    while (c_item) {
      FloatListItem* col = (FloatListItem*)c_item;
      assert(col && "FloatListList_at|ERROR, invalid cast");

      if (current_c++ != target_col) {
        c_item = c_item->next;
        continue;
      }
      retval = col;
    }
  }
  return retval;
}


void FloatListList_sumRows(ListHead* src_head, ListHead* dest_head) {
  assert(src_head && "FloatListList_sumRows|ERROR, invalid src");
  assert(dest_head && "FloatListList_sumRows|ERROR, invalid dest");

  ListItem* src_item = src_head->first;
  assert(src_item && "FloatListList_sumRows|ERROR, empty src");

  if (dest_head->size || dest_head->first) {
    printf("FloatListList_sumRows|WARNING, dest is already initialized, memory leaks will happen\n");
  }

  //ia initialize dest
  List_init(dest_head);

  //ia scan each row
  uint64_t num_row = 0;
  while (src_item) {
    //ia accumulator
    float accumulator = 0.f;

    FloatListListItem* src_f_item = (FloatListListItem*)(src_item);
    assert(src_f_item && "FloatListList_sumRows|ERROR, invalid external cast");

    //ia skip useless computation (if this is not a proper matrix you might end-up here)
    ListItem* aux = src_f_item->value.first;
    if (!aux) {
      printf("FloatListList_sumRows|WARNING, empty row [%ld]\n", num_row);
      src_item = src_item->next;
      ++num_row;
      continue;
    }

    //ia accumulate
    while (aux) {
      FloatListItem* value_item = (FloatListItem*)(aux);
      assert(src_f_item && "FloatListList_sumRows|ERROR, invalid internal cast");
      accumulator += value_item->value;      
      aux = aux->next;
    }

    //ia populate new list
    FloatListItem* accumulator_item = (FloatListItem*)(malloc(sizeof(FloatListItem)));
    assert(accumulator_item && "FloatListList_sumRows|ERROR, bad allocation");
    accumulator_item->value = accumulator;
    List_insert(dest_head, dest_head->last, (ListItem*)accumulator_item);
    
    src_item = src_item->next;
    ++num_row;
  }
}
