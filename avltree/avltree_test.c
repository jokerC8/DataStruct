#include <stdio.h>

#include "avltree.h"

static void AVLTree_test()
{
	int score;
	AVLTree T = NULL;

	while (1) {
		fprintf(stdout, "please input Insert score:");
		scanf("%d", &score);
		T = Insert(score, T);
		PrintTree(T);
		fprintf(stdout, "please input delete score:");
		scanf("%d", &score);
		T = Delete(score, T);
		PrintTree(T);
	}
}

int main(void)
{
	AVLTree_test();

	return 0;
}
