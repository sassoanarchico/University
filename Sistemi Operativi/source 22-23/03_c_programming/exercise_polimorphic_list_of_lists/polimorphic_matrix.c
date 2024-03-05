#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "polimorphic_matrix.h"

//! @brief typed implementation of the print method
void IntListItem_print_impl(ListItem* item) {
  IntListItem* i_item = (IntListItem*)(item);
  assert(i_item && "IntListItem_print_impl|ERROR, invalid cast");
  printf("%d", i_item->value);
}

//! @brief typed implementation of the print method
void FloatListItem_print_impl(ListItem* item) {
  FloatListItem* f_item = (FloatListItem*)(item);
  assert(f_item && "FloatListItem_print_impl|ERROR, invalid cast");
  printf("%.4f", f_item->value);
}

//! @brief typed implementation of the print method
void ListListItem_destroy_impl(ListItem* item) {
  ListListItem* l_item = (ListListItem*)(item);
  assert(l_item && "ListListItem_print_impl|ERROR, invalid cast");
  List_destroy(&l_item->value);
}

void ListListItem_print_impl(ListItem* item) {
  ListListItem* l_item = (ListListItem*)(item);
  assert(l_item && "ListListItem_print_impl|ERROR, invalid cast");
  List_print(&l_item->value);
}

//! @brief construct the VMT (typed)
ListItemOps int_ops = {.dtor_fn=0, .print_fn=IntListItem_print_impl};
ListItemOps float_ops = {.dtor_fn=0, .print_fn=FloatListItem_print_impl};
ListItemOps list_ops = {.dtor_fn=ListListItem_destroy_impl, .print_fn=ListListItem_print_impl};


