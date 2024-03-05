#include <stdio.h>
#include <stdlib.h>

#include "polimorphic_matrix.h"

#define LIST_ELEMENTS 3
#define NUM_ROWS 5
#define NUM_COLS 4

int main(int argc, char** argv) {
  printf("test_list_of_lists|start\n");

  printf("test_list_of_lists|simple float list\n");
  ListHead float_list;
  List_init(&float_list);
  for (uint32_t i = 0; i < LIST_ELEMENTS; ++i) {
    FloatListItem* f_item = (FloatListItem*)(malloc(sizeof(FloatListItem)));
    f_item->value = i + 0.5;
    ListItem_construct((ListItem*)f_item, &float_ops);
    printf("instance [%p] - vmt pointer [%p]\n", f_item, &float_ops);
    List_insert(&float_list, float_list.last, (ListItem*)f_item);
  }

  List_print(&float_list);
  List_destroy(&float_list);

  printf("test_list_of_lists|float matrix\n");

  ListHead list_of_lists;
  List_init(&list_of_lists);

  for (int r = 0; r < NUM_ROWS; ++r) {
    ListListItem* l_item = (ListListItem*)malloc(sizeof(ListListItem));
    ListItem_construct((ListItem*)l_item, &list_ops);
    printf("ListListItem| instance [%p] - vmt pointer [%p]\n", l_item, &list_ops);
    List_insert(&list_of_lists, list_of_lists.last, (ListItem*)l_item);
    
    for (int c = 0; c < NUM_COLS; ++c) {
      FloatListItem* f_item = (FloatListItem*)malloc(sizeof(FloatListItem));
      ListItem_construct((ListItem*)f_item, &float_ops);
      printf("FloatListItem|instance [%p] - vmt pointer [%p]\n", f_item, &float_ops);

      f_item->value = r*c*0.5;
      List_insert(&l_item->value, l_item->value.last, (ListItem*)f_item);
    }
  }

  List_print(&list_of_lists);
  List_destroy(&list_of_lists);

  
  printf("test_list_of_lists|end\n");
  return 0;
}

