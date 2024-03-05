#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "float_linked_list.h"

#define TARGET_LIST_SIZE 10

int main(int argc, char** argv) {
  printf("float_linked_list|start\n");

  //ia simple float list
  ListHead float_list;
  List_init(&float_list);
  for (u_int16_t i = 0; i < TARGET_LIST_SIZE; ++i) {
    FloatListItem* f_item = (FloatListItem*)(malloc(sizeof(FloatListItem)));
    f_item->value = i + 0.5f;
    assert(f_item && "ERROR, cannot instanciate item");
    List_insert(&float_list, float_list.last, (ListItem*)f_item);
  }
  FloatList_print(&float_list);

  //ia list of lists (float)
  ListHead float_matrix;
  List_init(&float_matrix);
  FloatListList_init(3, 3, &float_matrix);

  FloatListItem* m_item = FloatListList_at(&float_matrix, 0 , 0);
  m_item->value = 5.0;
  m_item = FloatListList_at(&float_matrix, 0 , 2);
  m_item->value = 2.0;
  m_item = FloatListList_at(&float_matrix, 1 , 1);
  m_item->value = 3.0;
  m_item = FloatListList_at(&float_matrix, 1 , 0);
  m_item->value = 2.6;
  m_item = FloatListList_at(&float_matrix, 2 , 0);
  m_item->value = 4.0;
  m_item = FloatListList_at(&float_matrix, 2 , 2);
  m_item->value = 0.6;
  FloatListList_print(&float_matrix);

  //ia sum rows
  ListHead sum_list;
  List_init(&sum_list);
  FloatListList_sumRows(&float_matrix, &sum_list);
  FloatList_print(&sum_list);

  //ia checkout
  FloatList_destroy(&float_list);
  FloatListList_destroy(&float_matrix);
  FloatList_destroy(&sum_list);

  printf("float_linked_list|end\n");
  return 0;
}
