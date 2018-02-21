#pragma once
#include "RedBlackTreeNode.h"
typedef int bool;

typedef struct RedBlackTree {
	RBTNode *root;
	RBTNode *nil;

	// functions pointers
	RBTNode* (*insert)(struct RedBlackTree *self, int value);
	RBTNode* (*get_successor)(struct RedBlackTree *self, RBTNode *node);
	RBTNode* (*get_predecessor)(struct RedBlackTree *self, RBTNode *node);
	void (*print)(struct RedBlackTree *self);
} RBT;

RBTNode* RBT_insert_(RBT *self, int value);
void RBT_reorder(RBT *self, RBTNode *node);
void in_order_traversal(RBT *self, RBTNode *node, void(*callback_function)(RBTNode *node));
void post_order_traversal(RBT *self, RBTNode *node, void(*callback_function)(RBTNode *node));
RBT* RedBlackTreeConstruct();
void RedBlackTreeDestruct(RBT* tree);
RBTNode *min_value(RBT *self, RBTNode *node);
RBTNode *max_value(RBT *self, RBTNode *node);
RBTNode *get_successor(RBT *self, RBTNode *node);
RBTNode *max_value(RBT *self, RBTNode *node);