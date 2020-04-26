#include <stdint.h>
#include <stdio.h>
#include "stack.h"

static void test()
{
	uint32_t i;
	Stack S;
	int nums[] = {100, 23, 32, 123, 89, 25, 78, 54, 9, 88, 102, 43, 232, 90, 1234, 876, 2342, 189, 452, 990, 876, 0, 12};

	S = CreateStack(100);
	for (i = 0; i < sizeof(nums)/sizeof(int); i++)
		Push(nums[i], S);

	while (!IsEmpty(S))
		fprintf(stdout, "%d ", TopAndPop(S));
	putchar('\n');

	return;
}

int main(void)
{
	test();

	return 0;
}
