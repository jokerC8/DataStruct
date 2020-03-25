#ifndef __QUEUE_H
#define __QUEUE_H

struct QueueRecord;
typedef struct QueueRecord *Queue;

int IsEmpty(Queue Q);
int IsFull(Queue Q);
void MakeEmpty(Queue Q);
void Enqueue(int x, Queue Q);
void Dequeue(Queue Q);
int Font(Queue Q);
int FontAndDequeue(Queue Q);
Queue CreateQueue(int Size);

#endif
