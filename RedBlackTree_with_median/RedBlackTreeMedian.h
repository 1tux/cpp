#pragma once
#include "RedBlackTree.h"

typedef struct RedBlackTreeMedian {
	RBT *tree;

	RBTNode *median;
	bool parity; 

	// functions pointers
	RBTNode* (*insert)(struct RedBlackTreeMedian *self, int value);
	void (*print_median)(struct RedBlackTreeMedian *self);

	// inherited API
	RBTNode* (*get_successor)(struct RedBlackTreeMedian *self, RBTNode *node);
	RBTNode* (*get_predecessor)(struct RedBlackTreeMedian *self, RBTNode *node);
	void (*print)(struct RedBlackTreeMedian *self);
	
} RBTMed;

int RBTMed_print_median(RBTMed* self);
RBTMed* RedBlackTreeMedianConstruct();
void RedBlackTreeMedianDestruct(RBTMed* tree);
RBTNode* RBTMed_insert(RBTMed *self, int value);
RBTNode* get_successor_(RBTMed *self, RBTNode *node);
RBTNode* get_predecessor_(RBTMed *self, RBTNode *node);
void print_(RBTMed* self);