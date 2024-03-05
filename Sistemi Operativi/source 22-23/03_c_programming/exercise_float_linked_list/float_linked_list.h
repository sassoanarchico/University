#pragma once
#include <assert.h>
#include <stdint.h>
#include "linked_list.h"

//! @brief derived list item, stores a float value
typedef struct FloatListItem {
  ListItem item;
  float value;
} FloatListItem;

//! @brief prints a float list
void FloatList_print(ListHead* head);

//! @brief de-allocates memory and deletes the list
void FloatList_destroy(ListHead* head);


//! @brief derived list item, stores a FloatList
typedef struct FloatListListItem {
  ListItem item;
  ListHead value;
} FloatListListItem;

//! @brief initialize a float matrix and puts everything to 0
void FloatListList_init(uint64_t target_rows,
                        uint64_t target_cols,
                        ListHead* head);

//ia de-allocates memory and deletes the list
void FloatListList_destroy(ListHead* head);

//! @brief prints a float matrix
void FloatListList_print(ListHead* head);

//! @brief access a block in a matrix fashion
FloatListItem* FloatListList_at(ListHead* head,
                                uint64_t row,
                                uint64_t col);

//! @brief computes the sum of each row and puts in a new list
void FloatListList_sumRows(ListHead* src_head, ListHead* dest_head);
