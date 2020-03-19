#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include "priority_queue.h"

struct HeapStruct {
	int Size;
	int Capacity;
	int *Heap;
};

#define MIN 10

PriorityQueue Initialize(int Capacity)
{
	PriorityQueue H;

	if (Capacity < MIN)
		error(-1, -1, "Capacity must largger than %d\n", MIN);
	H = malloc(sizeof(*H));
	if (!H)
		error(-1, -1, "malloc failed\n");
	H->Size = 0;
	H->Capacity = Capacity;
	H->Heap = malloc(sizeof(int) * (Capacity + 1));
	if (!H->Heap)
		error(-1, -1, "malloc failed\n");
	H->Heap[0] = -1;
	return H;
}

void Up(int index, PriorityQueue H)
{
	int Parent, Temp;

	for (; index/2 > 0; index = Parent) {
		Parent = index >> 1;
		if (H->Heap[index] < H->Heap[Parent]) {
			Temp = H->Heap[index];
			H->Heap[index] = H->Heap[Parent];
			H->Heap[Parent] = Temp;
		} else {
			break;
		}
	}
}

void Down(int index, PriorityQueue H)
{
	int Child, Temp;

	for (; index * 2 <= H->Size; index = Child) {
		Child = index * 2;
		if (Child != H->Size && H->Heap[Child] > H->Heap[Child + 1])
			Child += 1;
		if (H->Heap[index] > H->Heap[Child]) {
			Temp = H->Heap[index];
			H->Heap[index] = H->Heap[Child];
			H->Heap[Child] = Temp;
		} else {
			break;
		}
	}
}

PriorityQueue BuildHeap(int *arr, int size)
{
	int i;
	PriorityQueue H;

	H = malloc(sizeof(*H));
	if (!H)
		error(-1, -1, "malloc failed\n");
	if (size < MIN)
		size = MIN;

	H->Heap = malloc(sizeof(int) * (2 * size + 1));
	if (!H->Heap)
		error(-1, -1, "malloc failed\n");

	H->Heap[0] = -1;
	memcpy(H->Heap + 1, arr, sizeof(int) * size);
	H->Size = size;
	H->Capacity = 2 * size;
	for (i = size/2; i > 0; i--)
		Down(i, H);

	return H;
}

void MakeEmpty(PriorityQueue H)
{
	if (H)
		H->Size = 0;
}

int Insert(int x, PriorityQueue H)
{
	int i;

	if (IsFull(H)) {
		error(0, -1, "PriorityQueue is full\n");
		return -1;
	}
	for (i = ++H->Size;	(i > 1) && H->Heap[i/2] > x; i /= 2)
		H->Heap[i] = H->Heap[i/2];
	H->Heap[i] = x;

	return 0;
}

int DeleteMin(PriorityQueue H)
{
	int i, index, last, min;

	if (!H || IsEmpty(H)) {
		error(0, -1, "PriorityQueue is NULL or empty\n");
		return -1;
	}
	min = H->Heap[1];
	last = H->Heap[H->Size--];

	for (i = 1; 2 * i <= H->Size; i = index) {
		index = 2 * i;
		if (index != H->Size && H->Heap[index] > H->Heap[index + 1])
			index += 1;
		if (last > H->Heap[index])
			H->Heap[index/2] = H->Heap[index];
		else
			break;
	}
	H->Heap[i] = last;

	return min;
}

int IsFull(PriorityQueue H)
{
	if (H)
		return H->Size == H->Capacity;

	return 0;
}

int IsEmpty(PriorityQueue H)
{
	if (H)
		return H->Size == 0;

	return 0;
}

void Destroy(PriorityQueue H)
{
	if (H) {
		free(H->Heap);
		free(H);
	}
}
