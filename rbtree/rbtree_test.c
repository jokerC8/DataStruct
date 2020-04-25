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

	for (i = 0; i < 1000000; i++) {
		node = malloc(sizeof(*node));
		if (node) {
			node->element = random() % 0xffffff;
			rbtree_insert(&root, &sentinel, node);
		}
	}

	i = 0;
	while (root != &sentinel) {
		fprintf(stdout, "delete %d\n", root->element);
		rbtree_delete(&root, &sentinel, root);
	}

	inorder(root, &sentinel);
	return 0;
}
