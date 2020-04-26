#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include "queue.h"

#define MIN (10)

struct QueueRecord {
	int Capacity;
	int Size;
	int Font;
	int Rear;
	int *Array;
};

void MakeEmpty(Queue Q)
{
	Q->Size = 0;
}

int IsEmpty(Queue Q)
{
	return Q->Size == 0;
}

int IsFull(Queue Q)
{
	return Q->Size == Q->Capacity;
}

Queue CreateQueue(int Size)
{
	Queue Q;

	if (Size < MIN)
		return NULL;

	Q = malloc(sizeof(*Q));
	if (!Q)
		error(-1, errno, "malloc failed\n");
	Q->Capacity = Size;
	Q->Size = 0;
	Q->Font = Q->Rear = 0;
	Q->Array = malloc(sizeof(int) * Size);
	if (!Q->Array)
		error(-1, errno, "malloc failed\n");

	return Q;
}

void Enqueue(int x, Queue Q)
{
	if (IsFull(Q)) {
		error(0, 0, "queue is full\n");
		return;
	}
	Q->Array[Q->Font++] = x;
	Q->Size++;
}

void Dequeue(Queue Q)
{
	if (IsEmpty(Q)) {
		error(0, 0, "queue is empty\n");
		return;
	}
	Q->Rear++;
	Q->Size--;
}

int Font(Queue Q)
{
	if (IsEmpty(Q)) {
		error(0, 0, "queue is empty\n");
		return -1;
	}

	return Q->Array[Q->Rear];
}

int FontAndDequeue(Queue Q)
{
	if (IsEmpty(Q)) {
		error(0, 0, "queue is empty\n");
		return -1;
	}
	Q->Size--;
	return Q->Array[Q->Rear++];
}
