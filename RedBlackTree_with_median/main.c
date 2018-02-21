#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "RedBlackTreeMedian.h"

void fill_array_with_random(int *arr, int length) {
	for (int i = 0; i < length; i++)
		arr[i] = rand() % 1024;
}

void sort_array(int *arr, int length) {
	for (int i = 0; i < length; i++)
		for (int j = i+1; j < length; j++)
			if (arr[i] > arr[j])
			{
				arr[i] += arr[j];
				arr[j] = arr[i] - arr[j];
				arr[i] = arr[i] - arr[j];
			}
}

void the_algorithm(int *arr, int n1, int n2, int n3) {
	RBTMed *rbtmed = RedBlackTreeMedianConstruct();

	for (int i = 0; i < n1; i++)
		rbtmed->insert(rbtmed, arr[i]);
	rbtmed->print_median(rbtmed);

	for (int i = n1; i < n2; i++)
		rbtmed->insert(rbtmed, arr[i]);
	rbtmed->print_median(rbtmed);

	for (int i = n2; i < n3; i++)
		rbtmed->insert(rbtmed, arr[i]);
	rbtmed->print_median(rbtmed);

	RedBlackTreeMedianDestruct(rbtmed);
}


void the_algorithm_DBG(int *arr, int n1, int n2, int n3) {
	RBTMed *rbtmed = RedBlackTreeMedianConstruct();
	int *arr2 = calloc(n1, sizeof(int));

	for (int i = 0; i < n1; i++)
	{
		rbtmed->insert(rbtmed, arr[i]);
		arr2[i] = arr[i];
	}
	rbtmed->print_median(rbtmed);

	sort_array(arr2, n1);
	for(int i = 0; i < n1; i++)
	printf("%d ", arr2[i]);
	printf("\n");

	printf("TESTING: MEDIAN is: %d\n", arr2[n1 / 2 - (1 - n1 % 2)]);
	rbtmed->print(rbtmed);
	

	for (int i = n1; i < n2; i++)
		rbtmed->insert(rbtmed, arr[i]);
	rbtmed->print_median(rbtmed);

	for (int i = n2; i < n3; i++)
		rbtmed->insert(rbtmed, arr[i]);
	rbtmed->print_median(rbtmed);

	RedBlackTreeMedianDestruct(rbtmed);
	free(arr2);
}

void tests() {
	RBTMed *rbtmed = RedBlackTreeMedianConstruct();
	for (int i = 0; i < 4; i++)
		rbtmed->insert(rbtmed, i*2);
	rbtmed->insert(rbtmed, 5);
	RBTNode *node = rbtmed->insert(rbtmed, 10);
	RBTNode *node2 = rbtmed->insert(rbtmed, 3);
	print_node(rbtmed->get_predecessor(rbtmed, node2));
	print_node(rbtmed->get_successor(rbtmed, node2));
	rbtmed->tree->print(rbtmed->tree);
	rbtmed->print_median(rbtmed);
	RedBlackTreeMedianDestruct(rbtmed);
}

int main() {

	srand((unsigned int)time(NULL));

	int A[200], B[400], C[800];
	int a_n1, a_n2, a_n3;
	int b_n1, b_n2, b_n3;
	int c_n1, c_n2, c_n3;

	a_n1 = (sizeof(A) / sizeof(*A)) / 4;
	a_n2 = a_n1 * 2;
	a_n3 = a_n1 * 3;

	b_n1 = (sizeof(B) / sizeof(*B)) / 4;
	b_n2 = b_n1 * 2;
	b_n3 = b_n1 * 3;

	c_n1 = (sizeof(C) / sizeof(*C)) / 4;
	c_n2 = c_n1 * 2;
	c_n3 = c_n2 * 3;

	fill_array_with_random(A, sizeof(A) / sizeof(*A));
	fill_array_with_random(B, sizeof(B) / sizeof(*B));
	fill_array_with_random(C, sizeof(C) / sizeof(*C));
	
	the_algorithm(A, a_n1, a_n2, a_n3);
	the_algorithm(B, b_n1, b_n2, b_n3);
	the_algorithm(C, c_n1, c_n2, c_n3);
	
	system("pause");
	return 0;
}
