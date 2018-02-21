#include "RedBlackTreeNode.h"
#include <stdlib.h>
#include <stdio.h>

#define KRED  "\x1B[31m"
#define KBLACK  "\x1B[30m"
#define KRESET "\x1B[0m"

RBTNode* new_node(int value) {
	// should be freed after usage

	RBTNode* node = (RBTNode *)malloc(sizeof(RBTNode));
	node->value = value;
	node->color = BLACK;
	node->parent = node->left = node->right = NULL;
	return node;
}

void free_node(RBTNode *node) {
	free(node);
	node = NULL;
}

#ifndef _WIN32
void print_node(RBTNode *node) {
	char *color_prefix = node->color == RED ? KRED : KBLACK;
	printf("{%s%d%s} ", color_prefix, node->value, KRESET);
}
#else
#include <Windows.h>
void print_node(RBTNode *node) {
	CONSOLE_SCREEN_BUFFER_INFO buf_info;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &buf_info);
	if (node->color == RED)
		SetConsoleTextAttribute(console, 12); // LightRed
	else
		SetConsoleTextAttribute(console, 15); // White, instead of Black since shell background is black
	printf("{%d}", node->value);
	SetConsoleTextAttribute(console, buf_info.wAttributes);
}
#endif
