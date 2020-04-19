#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "rbtree.h"

struct rbtree_node sentinel;

int main()
{
	int i;
	rbtree root, node;

	root = &sentinel;

	for (i = 0; i < 100000; i++) {
		node = malloc(sizeof(*node));
		if (node) {
			node->element = random() % 0xffffff;
			rbtree_insert(&root, &sentinel, node);
		}
	}

	//inorder(root, &sentinel);

	rbtree left, right;

	for (; ;) {
		left = root->left;
		if (left != &sentinel)
			rbtree_delete(&root, &sentinel, left);
		right = root->right;

		if (right != &sentinel)
			rbtree_delete(&root, &sentinel, right);

		if (root->left == &sentinel && root->right == &sentinel)
			break;
	}

	inorder(root, &sentinel);

	return 0;
}
