#include <stdio.h>
#include "rbtree.h"

void test()
{
	int c;
	RBTree T = NULL;

	for (; ;) {
		fprintf(stdout, "Please input a num:");
		scanf("%d", &c);
		T = Insert(c, T);
		InOrder(T);
	}
}

int main(void)
{
	test();

	return 0;
}
