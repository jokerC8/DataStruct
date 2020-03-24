#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include "stack.h"

#define MIN (10)

struct StackStruct {
    int Capacity;
    int Size;
    int *Array;
};

Stack CreateStack(int Size)
{
	Stack S;

	if (Size < MIN)
		return NULL;

	S = malloc(sizeof(*S));
	if (!S)
		error(-1, errno, "malloc failed\n");
	S->Capacity = Size;
	S->Size = 0;
	S->Array = malloc(sizeof(int) * (Size + 1));
	if (!S->Array)
		error(-1, errno, "malloc failed\n");

	return S;
}

int IsEmpty(Stack S)
{
    return S->Size == 0;
}

int IsFull(Stack S)
{
    return S->Size == S->Capacity;
}

void MakeEmpty(Stack S)
{
    S->Size = 0;
}

void Push(int x, Stack S)
{
	if (IsFull(S)) {
		error(0, 0, "stack is full\n");
		return;
	}

	S->Array[++S->Size] = x;
}

void Pop(Stack S)
{
	if (IsEmpty(S)) {
		error(0 , 0, "stack is empty\n");
		return;
	}

	S->Size--;
}

int Top(Stack S)
{
	if (IsEmpty(S)) {
		error(0, 0, "queue is empty\n");
		return -1;
	}
	return S->Array[S->Size];
}

int TopAndPop(Stack S)
{
	if (IsEmpty(S)) {
		error(0, 0, "stack is empty\n");
		return -1;
	}

	return S->Array[S->Size--];
}
