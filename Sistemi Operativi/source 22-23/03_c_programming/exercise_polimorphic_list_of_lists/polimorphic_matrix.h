#pragma once
#include "polimorphic_list.h"
#include <stdint.h>

//! @brief specialization of the ListItem (typed)
typedef struct IntListItem {
  ListItem item;
  int value;
} IntListItem;

typedef struct FloatListItem {
  ListItem item;
  float value;
} FloatListItem;

typedef struct ListListItem {
  ListItem item;
  ListHead value;
} ListListItem;

//! @brief global ops (typed)
extern ListItemOps int_ops;
extern ListItemOps float_ops;
extern ListItemOps list_ops;
