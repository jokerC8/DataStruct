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
	pthread_mutex_t *lock;
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

Queue CreateQueue(int Size, pthread_mutex_t *lock)
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
	Q->lock = lock;
	Q->Array = malloc(sizeof(int) * Size);
	if (!Q->Array)
		error(-1, errno, "malloc failed\n");
	return Q;
}

void Enqueue(int x, Queue Q)
{
	pthread_mutex_lock(Q->lock);
	if (IsFull(Q)) {
		pthread_mutex_unlock(Q->lock);
		error(0, 0, "queue is full\n");
		return;
	}
	Q->Array[Q->Font++] = x;
	Q->Size++;
	pthread_mutex_unlock(Q->lock);
}

void Dequeue(Queue Q)
{
	pthread_mutex_lock(Q->lock);
	if (IsEmpty(Q)) {
		pthread_mutex_unlock(Q->lock);
		return;
	}
	Q->Rear++;
	Q->Size--;
	pthread_mutex_unlock(Q->lock);
}

int Font(Queue Q)
{
	int ret;

	pthread_mutex_lock(Q->lock);
	ret = Q->Array[Q->Rear];
	pthread_mutex_unlock(Q->lock);

	return ret;
}

int FontAndDequeue(Queue Q)
{
	int ret;
	pthread_mutex_lock(Q->lock);
	if (IsEmpty(Q)) {
		pthread_mutex_unlock(Q->lock);
		error(0, 0, "queue is empty\n");
		return -1;
	}
	ret = Q->Array[Q->Rear++];
	Q->Size--;
	pthread_mutex_unlock(Q->lock);

	return ret;
}
