#include "RedBlackTreeMedian.h"
#include <stdlib.h>
#include <stdio.h>

RBTMed* RedBlackTreeMedianConstruct() {

	RBTMed *rbtmed = malloc(sizeof(RBTMed));
	rbtmed->tree = RedBlackTreeConstruct();

	rbtmed->parity = 0;
	rbtmed->median = NULL;

	rbtmed->insert = RBTMed_insert;
	rbtmed->print_median = RBTMed_print_median;

	rbtmed->get_successor = get_successor_;
	rbtmed->get_predecessor = get_predecessor_;
	rbtmed->print = print_;
	return rbtmed;
}

void RedBlackTreeMedianDestruct(RBTMed* rbtmed) {
	RedBlackTreeDestruct(rbtmed->tree);
	free(rbtmed);
}

RBTNode* RBTMed_insert(RBTMed *self, int value) {
	RBTNode* node = self->tree->insert(self->tree, value);

	// TODO: think about <= or >= ...
	// testing prove it's fine :) 
	self->parity ^= 1;
	if (self->median == NULL)
		self->median = node;

	if (self->parity)
	{
		if (value > self->median->value)
			self->median = self->get_successor(self, self->median);
	} else {
		if (value < self->median->value)
			self->median = self->get_predecessor(self, self->median);
	}	
	return node;
}

int RBTMed_print_median(RBTMed* self) {
	printf("The median is: %d\n", self->median->value);
	return self->median->value;
}

RBTNode* get_successor_(RBTMed *self, RBTNode *node) {
	return self->tree->get_successor(self->tree, node);
}
RBTNode* get_predecessor_(RBTMed *self, RBTNode *node) {
	return self->tree->get_predecessor(self->tree, node);
}

void print_(RBTMed *self) {
	self->tree->print(self->tree);
}