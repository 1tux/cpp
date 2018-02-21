#include "RedBlackTreeNode.h"
#include "RedBlackTree.h"
#include <stdlib.h>
#include <stdio.h>

RBTNode *min_value(RBT *self, RBTNode *node) {
	RBTNode *current = node;
	while (current->left != self->nil)
		current = current->left;
	return current;
}

RBTNode *max_value(RBT *self, RBTNode *node) {
	RBTNode *current = node;
	while (current->right != self->nil)
		current = current->right;
	return current;
}

RBTNode *get_successor(RBT *self, RBTNode *node) {
	if (node->right != self->nil)
		return min_value(self, node->right);

	RBTNode *current = node->parent;
	while (current != NULL && node == current->right)
	{
		node = current;
		current = current->parent;
	}
	return current;
}

RBTNode *get_predecessor(RBT *self, RBTNode *node) {
	if (node->left != self->nil)
		return max_value(self, node->left);

	RBTNode *current = node->parent;
	while (current != NULL && node == current->left)
	{
		node = current;
		current = current->parent;
	}
	return current;
}

void in_order_traversal(RBT *self, RBTNode *node, void(*callback_function)(RBTNode *node)) {
	// scans the tree in O(n)
	// execute callback function on each node
	if (node == self->nil || node == NULL)
		return;

	in_order_traversal(self, node->left, callback_function);
	callback_function(node);
	in_order_traversal(self, node->right, callback_function);
}

void post_order_traversal(RBT *self, RBTNode *node, void(*callback_function)(RBTNode *node)) {
	// scans the tree in O(n)
	// execute callback function on each node
	if (node == self->nil || node == NULL)
		return;

	post_order_traversal(self, node->left, callback_function);
	post_order_traversal(self, node->right, callback_function);
	callback_function(node);
}

void RBT_print(RBT *self) {
	printf("RBT: ");
	in_order_traversal(self, self->root, print_node);
	printf("\n");
}

RBTNode *RBT_recursion_insert(RBT *self, RBTNode *root, RBTNode *node) {
	if (root == self->nil)
		return node;

	if (root->value > node->value) {
		root->left = RBT_recursion_insert(self, root->left, node);
		root->left->parent = root;
	}
	else {
		root->right = RBT_recursion_insert(self, root->right, node);
		root->right->parent = root;
	}
	return root;
}

/*
void RBT_insert(RBT *self, RBTNode *node) {
	node->left = node->right = self->nil;

	if (self->root != NULL) {
		node->color = RED;
		RBT_recursion_insert(self, self->root, node);
		RBT_reorder(self, node);

	} else
		self->root = node;
}
*/

RBTNode* RBT_insert_(RBT *self, int value) {
	RBTNode *node = new_node(value);
	node->left = node->right = self->nil;

	if (self->root != NULL) {
		node->color = RED;
		RBT_recursion_insert(self, self->root, node);
		RBT_reorder(self, node);
	}
	else
		self->root = node;
	return node;
}

void rotateRight(RBT *self, RBTNode *node) {
	RBTNode *left = node->left;
	node->left = left->right;

	if (left->right != self->nil)
		left->right->parent = node;

	left->parent = node->parent;

	if (node->parent == NULL)
		self->root = left;

	if (node->parent != NULL) {

		if (node == node->parent->left)
			node->parent->left = left;
		else
			node->parent->right = left;
	}

	left->right = node;
	node->parent = left;
}

void rotateLeft(RBT *self, RBTNode *node) {
	RBTNode *right = node->right;
	node->right = right->left;

	if (right->left != self->nil)
		right->left->parent = node;

	if (right != self->nil)
		right->parent = node->parent;

	if (node->parent == NULL)
		self->root = right;

	if (node->parent != NULL) {
		if (node == node->parent->left)
			node->parent->left = right;
		else
			node->parent->right = right;
	}

	right->left = node;
	node->parent = right;
}

void RBT_reorder(RBT *self, RBTNode *node) {
	RBTNode *uncle;

	while (node != self->root && node->parent->color == RED) {
		if (node->parent == node->parent->parent->left) {
			uncle = node->parent->parent->right;

			// Case1
			if (uncle->color == RED) {
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;

			} else { // Case 2
				if (node == node->parent->right) {
					node = node->parent;
					rotateLeft(self, node);
				}
				// Case 3
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				rotateRight(self, node->parent->parent);
			}
		}
		else {
			uncle = node->parent->parent->left;
			// Case1
			if (uncle->color == RED) {
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else {
				if (node == node->parent->left) {
					node = node->parent;
					rotateRight(self, node);
				}
				// Case 3
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				rotateLeft(self, node->parent->parent);
			}
		}
	} // end of while
	self->root->color = BLACK;
}

RBT* RedBlackTreeConstruct() {
	// creates a tree and initiallize the struct's function
	// should be freed after_usage

	RBT *rbt = (RBT *)malloc(sizeof(RBT));
	rbt->root = NULL;
	rbt->nil = new_node(0xDEADBABE);
	rbt->nil->parent = NULL;
	rbt->nil->left = rbt->nil->right = rbt->nil;

	rbt->insert = RBT_insert_;
	rbt->print = RBT_print;

	rbt->get_successor = get_successor;
	rbt->get_predecessor = get_predecessor;
	return rbt;
}

void RedBlackTreeDestruct(RBT* tree) {
	// frees all elements
	post_order_traversal(tree, tree->root, free_node);
	free_node(tree->nil);
	free(tree);
	tree = NULL;
}

