#ifndef __PRIORITY_QUEUE_H
#define __PRIORITY_QUEUE_H

struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;

void MakeEmpty(PriorityQueue H);
PriorityQueue Initialize(int MaxSize);
PriorityQueue BuildHeap(int *arr, int size);
int Insert(int x, PriorityQueue H);
int DeleteMin(PriorityQueue H);
int IsFull(PriorityQueue H);
int IsEmpty(PriorityQueue H);
void Destroy(PriorityQueue H);

#endif
