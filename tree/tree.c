#include <stdio.h>
#include <stdlib.h>
#include <error.h>

#include "tree.h"

#define MAX(l, r) ((l) > (r) ? (l) : (r))

struct TreeNode {
	int Element;
	struct TreeNode *Left;
	struct TreeNode *Right;
};

void MakeEmpty(Tree T)
{
	if (T) {
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
	}
}

Position Find(int x, Tree T)
{
	if (T) {
		if (x > T->Element)
			return Find(x, T->Right);
		else if (x < T->Element)
			return Find(x, T->Left);
		else
			return T;
	}

	return NULL;
}

Position FindMin(Tree T)
{
	if (T && T->Left)
		return FindMin(T->Left);

	return T;
}

Position FindMax(Tree T)
{
	if (T && T->Right)
		return FindMax(T->Right);

	return T;
}

Tree Insert(int x, Tree T)
{
	if (!T) {
		T = malloc(sizeof(*T));
		if (!T)
			return NULL;
		T->Element = x;
		T->Left = T->Right = NULL;
	} else {
		if (x < T->Element)
			T->Left = Insert(x, T->Left);
		else if (x > T->Element)
			T->Right = Insert(x, T->Right);
		/* if x already in tree, no nothing */
	}
	return T;
}

Tree Delete(int x, Tree T)
{
	Position TmpCell;

	if (!T)
		return NULL;
	if (x < T->Element)
		T->Left = Delete(x, T->Left);
	else if (x > T->Element)
		T->Right = Delete(x, T->Right);
	else {
		if (T->Left && T->Right) {
			TmpCell = FindMin(T->Right);
			T->Element = TmpCell->Element;
			T->Right = Delete(x, T->Right);
		} else {
			TmpCell = T;
			if (T->Left == NULL)
				T = T->Right;
			else if (T->Left == NULL)
				T = T->Left;
			/* free node */
			free(TmpCell);
		}
	}

	return T;
}

int Retrive(Position P)
{
	if (P)
		return P->Element;
	error(0, -1, "P is NULL\n");
	return -1;
}

int Height(Tree T)
{
	if (!T)
		return -1;

	return 1 + MAX(Height(T->Left), Height(T->Right));
}

void PrintTree(Tree T)
{
	if (T) {
		PrintTree(T->Left);
		fprintf(stdout, "%d ", T->Element);
		PrintTree(T->Right);
	}
}
