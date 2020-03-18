#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "priority_queue.h"

#define HEAP_SIZE 0x100

void HeapTest()
{
	int counter = 0;
	PriorityQueue H;

	H = Initialize(HEAP_SIZE);
	if (!H)
		return;
	while (counter++ < 20)
		Insert(random() % 100, H);
	while (!IsEmpty(H))
		fprintf(stdout, "%d ", DeleteMin(H));
	putchar('\n');
}

int main(void)
{
	HeapTest();
	return 0;
}
