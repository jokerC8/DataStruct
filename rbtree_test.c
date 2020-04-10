#include <stdio.h>
#include "rbtree.h"

void test()
{
	int c, i;
	RBTree T = 0; 
	int nums[] = {
		7, 19, 81, 6, 10, 100, 20, 129, 145, 89, 76, 129, 234, 65, 22, 43, 1024, 782, 1231, 321
	};
	for (i = 0; (unsigned int)i < sizeof(nums)/sizeof(int); i++) {
		fprintf(stdout, "Insert:%d\n", nums[i]);
		T = Insert(nums[i], T);
		InOrder(T);
	}

	while (1) {
		fprintf(stdout, "Delete a num:");
		scanf("%d", &c);
		if (T == NULL)
			break;
		Delete(c, &T);
		InOrder(T);
	}
}

int main(void)
{
	test();

	return 0;
}
