#pragma once
#ifndef NULL
#define NULL 0
#endif

#ifndef RBTNODE_H
#define RBTNODE_H


typedef enum COLOR_ { BLACK, RED } COLOR;

typedef struct RedBlackTreeNode {
	COLOR color;
	int value;
	struct RedBlackTreeNode *parent, *left, *right;

} RBTNode;

RBTNode* new_node(int value);
void print_node(RBTNode *node);
void free_node(RBTNode *node);
#endif
