#include <stdio.h>
#include <stdlib.h>
#include <error.h>

#include "rbtree.h"

typedef enum {RED, BLACK} NodeColor;

struct RBTreeNode {
	NodeColor Color;	
	ElementType Element;
	RBTree Left, Right, Parent;
};

Position Find(ElementType x, RBTree T)
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

Position FindMin(RBTree T)
{
#if defined(RECURSIVE)
	if (T && T->Left)
		return FindMin(T->Left);

	return T;
#else
	while (T) {
		if (T->Left)
			T = T->Left;
	}

	return T;
#endif
}

Position FindMax(RBTree T)
{
#if defined(RECURSIVE)
	if (T && T->Right)
		return FindMin(T->Right);

	return T;
#else
	while (T) {
		if (T->Right)
			T = T->Right;
	}

	return T;
#endif
}

static Position NewNode(ElementType X)
{
	Position P;

	P = malloc(sizeof(*P));
	if (P) {
		P->Color = RED;
		P->Element = X;
		P->Left = P->Right = P->Parent = NULL;
	}

	return P;
}

RBTree __BSTInsert(Position P, RBTree T)
{
	if (!T)
		return P;
	if (P->Element < T->Element) {
		T->Left = __BSTInsert(P, T->Left);
		T->Left->Parent = T;
	} else if (P->Element > T->Element) {
		T->Right = __BSTInsert(P, T->Right);
		T->Right->Parent = T;
	}
	/* no thing if P alreay in tree */

	return T;
}

void LeftRotate(Position Node, RBTree *Root)
{
	Position R;

	R = Node->Right;
	Node->Right = R->Left;
	if (Node->Right)
		Node->Right->Parent = Node;
	R->Parent = Node->Parent;
	if (!Node->Parent)
		*Root = R;
	else if (Node == Node->Parent->Left)
		Node->Parent->Left = R;
	else
		Node->Parent->Right = R;
	Node->Parent = R;
	R->Left = Node;
}

void RightRotate(Position Node, RBTree *Root)
{
	Position L;

	L = Node->Left;
	Node->Left = L->Right;
	if (Node->Left)
		Node->Left->Parent = Node;
	L->Parent = Node->Parent;
	if (!Node->Parent)
		*Root = L;
	else if (Node == Node->Parent->Left)
		Node->Parent->Left = L;
	else
		Node->Parent->Right = L;
	Node->Parent = L;
	L->Right = Node;
}

static void Rebalance(Position Node, RBTree *T)
{
	Position P, G, U;

	while (Node != *T && Node->Parent && Node->Parent->Color == RED && Node->Color == RED) {

		P = Node->Parent;
		G = P->Parent;
		/* find uncle */
		U = (P == G->Left) ? G->Right : G->Left;
		/* uncle is red, recolor */
		if (U && U->Color == RED) {
			P->Color = BLACK;
			U->Color = BLACK;
			G->Color = RED;
			Node = G;
			continue;
		}
		if (P == G->Left) {
			/* LR case */
			if (Node == P->Right) {
				LeftRotate(P, T);	
				P = Node;
			}
			RightRotate(G, T);
			P->Color = BLACK;
			G->Color = RED;
			/* LL case */
		} else {
			/* RL case */
			if (Node == P->Left) {
				RightRotate(P, T);
				P = Node;
			}
			LeftRotate(G, T);
			P->Color = BLACK;
			G->Color = RED;
			/* RR case */
		}
	}

	(*T)->Color = BLACK;
}

RBTree Insert(ElementType X, RBTree T)
{
	Position P;

	P = NewNode(X);
	if (!P)
		error(-1, 0, "no memory\n");

	T = __BSTInsert(P, T);
	Rebalance(P, &T);

	return T;
}

RBTree Delete(ElementType x, RBTree T)
{
	return 0;
}

ElementType Retrive(Position P)
{
	if (!P) {
		error(0, 0, "P is not valid\n");
		return -1;
	}

	return P->Element;
}

void InOrder(RBTree T)
{
	if (T) {
		InOrder(T->Left);
		fprintf(stdout, "\tValue:%d Color:%s\n", T->Element, T->Color ? "BLACK" : "RED");
		InOrder(T->Right);
	}
}
