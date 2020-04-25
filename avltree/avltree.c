#include <stdio.h>
#include <stdlib.h>
#include <error.h>

#include "avltree.h"

#define MAX(L, R) ((L) > (R) ? (L) : (R))

struct AVLTreeNode {
	int Height;
	int Element;
	AVLTree Left;
	AVLTree Right;
};

AVLTree MakeEmpty(AVLTree T)
{
	if (T) {
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

Position Find(int x, AVLTree T)
{
	if (T) {
		if (x < T->Element)
			return Find(x, T->Left);
		else if (x > T->Element)
			return Find(x, T->Right);
		else
			return T;
	}

	return NULL;
}

Position FindMin(AVLTree T)
{
	if (T && T->Left)
		return FindMin(T->Left);

	return T;
}

Position FindMax(AVLTree T)
{
	if (T && T->Right)
		return FindMax(T->Right);

	return T;
}

int Height(AVLTree T)
{
	if (!T)
		return -1;

	return T->Height;
}

AVLTree SingleRotationWithLeft(AVLTree K1)
{
	Position K2;

	K2 = K1->Left;
	K1->Left = K2->Right;
	K2->Right = K1;

	K1->Height = MAX(Height(K1->Left), Height(K1->Right)) + 1;
	K2->Height = MAX(Height(K2->Left), Height(K2->Right)) + 1;

	return K2;
}

AVLTree SingleRotationWithRight(AVLTree K1)
{
	Position K2;

	K2 = K1->Right;
	K1->Right = K2->Left;
	K2->Left = K1;

	K1->Height = MAX(Height(K1->Left), Height(K1->Right)) + 1;
	K2->Height = MAX(Height(K2->Left), Height(K2->Right)) + 1;

	return K2;
}

AVLTree DoubleRotationWithLeft(AVLTree K1)
{
	K1->Left = SingleRotationWithRight(K1->Left);
	return SingleRotationWithLeft(K1);
}

AVLTree DoubleRotationWithRight(AVLTree K2)
{
	K2->Right = SingleRotationWithLeft(K2->Right);
	return SingleRotationWithRight(K2);
}

AVLTree Insert(int x, AVLTree T)
{
	if (!T) {
		T = malloc(sizeof(*T));
		if (!T)
			return NULL;
		T->Element = x;
		T->Height = 0;
		T->Left = T->Right = 0;
	} else {
		if (x < T->Element) {
			T->Left = Insert(x, T->Left);
			if (Height(T->Left) - Height(T->Right) == 2) {
				if (x < T->Left->Element)
					T = SingleRotationWithLeft(T);
				else
					T = DoubleRotationWithLeft(T);
			}
		} else if (x > T->Element) {
			T->Right = Insert(x, T->Right);
			if (Height(T->Right) - Height(T->Left) == 2) {
				if (x > T->Right->Element)
					T = SingleRotationWithRight(T);
				else
					T = DoubleRotationWithRight(T);
			}
		}
		/* already in AVLTree, do nothing */
	}

	T->Height = MAX(Height(T->Left), Height(T->Right)) + 1;
	return T;
}

AVLTree Delete(int x, AVLTree T)
{
	Position TmpCell;

    if (T) {
        if (x < T->Element)
            T->Left = Delete(x, T->Left);
        else if (x > T->Element)
            T->Right = Delete(x, T->Right);
		else {
			if (T->Left && T->Right) {
				TmpCell = FindMin(T->Right);
				T->Element = TmpCell->Element;
				T->Right = Delete(TmpCell->Element, T->Right);
			} else {
				TmpCell = T;
				if (T->Left == NULL)
					T = T->Right;
				else if (T->Right == NULL)
					T = T->Left;
				free(TmpCell);
				TmpCell = NULL;
			}
		}
		if (T) {
			if (Height(T->Left) - Height(T->Right) == 2) {
				TmpCell = T->Left;
				if (TmpCell->Left)
					T = SingleRotationWithLeft(T);
				else
					T = DoubleRotationWithLeft(T);
			} else if (Height(T->Right) - Height(T->Left) == 2) {
				TmpCell = T->Right;
				if (TmpCell->Right)
					T = SingleRotationWithRight(T);
				else
					T = DoubleRotationWithRight(T);
			}
			T->Height = MAX(Height(T->Left), Height(T->Right)) + 1;
		}
	}

	return T;
}

int Retrive(Position P)
{
	if (P)
		return P->Element;
	error(0, -1, "Position is NULL\n");
	return -1;
}

void PrintTree(AVLTree T)
{
	if (T) {
		PrintTree(T->Left);
		fprintf(stdout, "\tElement=%d Height=%d\n", T->Element, T->Height);
		PrintTree(T->Right);
	}
}
