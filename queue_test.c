#include <stdio.h>
#include <unistd.h>

#include "queue.h"

static void test()
{
	Queue Q;
	unsigned int i;
	int nums[] = {90, 21, 89, 786, 23, 45, 34, 890, 100, 123, 145, 178, 321, 346, 754, 908, 1024, 2434};

	Q = CreateQueue(0x100);
	for (i = 0; i < sizeof(nums)/sizeof(int); i++)
		Enqueue(nums[i], Q);
	while (!IsEmpty(Q))
		fprintf(stdout, "%d ", FontAndDequeue(Q));
	putchar('\n');
}

int main(void)
{
	test();

	return 0;
}
