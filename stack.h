#ifndef __STACK_H
#define __STACK_H

struct StackStruct;
typedef struct StackStruct *Stack;

int IsEmpty(Stack S);
int ImFull(Stack S);
void MakeEmpty(Stack S);
void Push(int x, Stack S);
void Pop(Stack S);
int Top(Stack S);
int TopAndPop(Stack S);
Stack CreateStack(int Size);

#endif
