#include <stdlib.h>

#include "rbtree.h"

static void test()
{
	int i;
	rbtree root = 0, temp;

	for (i = 0; i < 100000; i++) {
		temp = malloc(sizeof(*temp));
		if (temp) {
			temp->color = 0;
			temp->key = random()%0xffffff;
			temp->left = NULL;
			temp->right = NULL;
			temp->parent = NULL;
			rbtree_insert(&root, temp);
		}
	}

	rbtree_inorder(root);
}

int main(void)
{
	test();

	return 0;
}
