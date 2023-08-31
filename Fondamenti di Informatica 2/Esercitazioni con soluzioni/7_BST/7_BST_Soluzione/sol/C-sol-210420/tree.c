#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

struct tree {
	int key;
    void * value;
    struct tree * left;
    struct tree * right;
};

tree * build_tree_1() {

	tree * n6 = calloc(sizeof(tree), 1);
	n6->key = 6;

	tree * n3 = calloc(sizeof(tree), 1);
	n3->key = 3;

	tree * n12 = calloc(sizeof(tree), 1);
	n12->key = 12;

	tree * n1 = calloc(sizeof(tree), 1);
	n1->key = 1;

	tree * n5 = calloc(sizeof(tree), 1);
	n5->key = 5;

	tree * n7 = calloc(sizeof(tree), 1);
	n7->key = 7;

	tree * n15 = calloc(sizeof(tree), 1);
	n15->key = 15;

	n6->left = n3;
	n6->right = n12;

	n3->left = n1;
	n3->right = n5;

	n12->left = n7;
	n12->right = n15;

	return n6;
}

tree * build_tree_2() {

	tree * n6 = calloc(sizeof(tree), 1);
	n6->key = 6;

	tree * n3 = calloc(sizeof(tree), 1);
	n3->key = 3;

	tree * n12 = calloc(sizeof(tree), 1);
	n12->key = 12;

	tree * n1 = calloc(sizeof(tree), 1);
	n1->key = 1;

	tree * n5 = calloc(sizeof(tree), 1);
	n5->key = 5;

	tree * n7 = calloc(sizeof(tree), 1);
	n7->key = 7;

	tree * n15 = calloc(sizeof(tree), 1);
	n15->key = 15;

	n6->right = n3;
	n6->left = n12;

	n3->left = n1;
	n3->right = n5;

	n12->left = n7;
	n12->right = n15;

	return n6;
}

tree * build_tree_3() {

	tree * n6 = calloc(sizeof(tree), 1);
	n6->key = 6;

	tree * n3 = calloc(sizeof(tree), 1);
	n3->key = 3;

	tree * n12 = calloc(sizeof(tree), 1);
	n12->key = 12;

	tree * n1 = calloc(sizeof(tree), 1);
	n1->key = 1;

	tree * n5 = calloc(sizeof(tree), 1);
	n5->key = 5;

	n6->left = n3;
	
	n3->left = n1;
	n3->right = n5;

	n5->right = n12;

	return n6;
}

void tree_delete(tree * tt) {

	tree * t = tt;
	if (t == NULL)
		return;

	tree_delete(t->left);
	tree_delete(t->right);
	free(t);
}

static int tree_is_bst_aux(tree * v, int last_max) {
  
  if(v == NULL) 
  	return last_max;
  
  int max = tree_is_bst_aux(v->left, last_max);
  if(max == -1 || max > v->key)
  	return -1;
  
  return tree_is_bst_aux(v->right, v->key);
}

int tree_is_bst(tree * tt) {

	tree * t = tt;
	int res = tree_is_bst_aux(t, 0); // tutte le chiavi sono interi positivi
	if (res < 0)
		return 0;

	return 1;
}

static int tree_is_balanced_aux(tree * v) {

  if(v == NULL) 
  	return 0;

  int l = tree_is_balanced_aux(v->left);
  int r = tree_is_balanced_aux(v->right);

  if(l < 0 || r < 0) 
  	return -1;
  
  int diff = l >= r ? l - r : r - l;
  if(diff <= 1) 
  	return (l >= r ? l : r) + 1;
  
  return -1;
}

int tree_is_balanced(tree * tt) {

	tree * t = tt;
	int res = tree_is_balanced_aux(t);
	if (res < 0)
		return 0;

	return 1;
}

static int tree_is_avl_aux(tree * v, int last_max, int * height) {
  
  if(v == NULL) {
  	*height = 0;
  	return last_max;
  }

  int hl, hr;

  int max = tree_is_avl_aux(v->left, last_max, &hl);
  
  if(max == -1 || max > v->key)
  	return -1;
  
  max = tree_is_avl_aux(v->right, v->key, &hr);

  if(hl < 0 || hr < 0) 
  	return -1;
  
  int diff = hl >= hr ? hl - hr : hr - hl;
  if(diff <= 1) {
  	*height = (hl >= hr ? hl : hr) + 1;
  } else {
  	return -1;
  }

  return max;
}

int tree_is_avl(tree * tt) {

	tree * t = tt;
	int height;
	int res = tree_is_avl_aux(t, 0, &height);
	if (res < 0 || height < 0)
		return 0;

	return 1;
}