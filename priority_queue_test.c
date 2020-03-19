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
	Destroy(H);

	int numbers[] = {-10, 12, -25, 20, 45, -1, 33, 100, 78, -24, 120, 98, -21};
	H = BuildHeap(numbers, sizeof(numbers)/sizeof(int));
	while (!IsEmpty(H))
		fprintf(stdout, "%d ", DeleteMin(H));
	putchar('\n');
	Destroy(H);
}

int main(void)
{
	HeapTest();
	return 0;
}
