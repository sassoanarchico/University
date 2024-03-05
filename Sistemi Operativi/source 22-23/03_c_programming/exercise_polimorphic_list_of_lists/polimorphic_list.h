#pragma once

//! @brief forward declarations of stuff
struct ListItem;

//! @brief declare the type for the function that prints a generic list item
typedef void (*ListItem_PrintFnPtr)(struct ListItem*);

//! @brief declare the type for the function that destroys a generic list item
typedef void (*ListItem_DestroyFnPtr)(struct ListItem*);

//! @brief declare the generic VMT for the list
typedef struct ListItemOps {
  ListItem_DestroyFnPtr dtor_fn;
  ListItem_PrintFnPtr print_fn;
} ListItemOps;

//! @brief now we define the novel ListItem struct
typedef struct ListItem {
  //ia standard list bookkeeping
  struct ListItem* prev;
  struct ListItem* next;
  //ia pointer to the VMT
  ListItemOps* ops;
} ListItem;

//! @brief usual list struct
typedef struct ListHead {
  ListItem* first;
  ListItem* last;
  int size;
} ListHead;

//! @brief usual list management
void List_init(ListHead* head);
ListItem* List_find(ListHead* head, ListItem* item);
ListItem* List_insert(ListHead* head, ListItem* previous, ListItem* item);
ListItem* List_detach(ListHead* head, ListItem* item);

//! @brief generic implementation of the "per item" functions (exposed - NO OVERRIDE)
//!        this goes in the VMT and actually calls the proper function
void ListItem_construct(ListItem* item, ListItemOps* ops);
void ListItem_destroy(ListItem* item);
void ListItem_print(ListItem* item);

//! @brief generic function that operates on polimorphic lists (exposed - NO OVERRIDE)
void List_print(ListHead* head);
void List_destroy(ListHead* head);
