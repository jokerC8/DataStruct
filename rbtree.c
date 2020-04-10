#include <stdio.h>
#include <stdlib.h>
#include <error.h>

#include "rbtree.h"

#define Logd(format, args...) fprintf(stdout, "[%s:%d]\n"format, __FUNCTION__,__LINE__,##args);

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
	while (T && T->Left)
		T = T->Left;

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
	while (T && T->Right)
		T = T->Right;

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

/*
 * find the Node we want to delete, if Node is leaf or
 * have only one child, then return Node, or find minimal
 * Node on its right tree
 */
RBTree Successor(ElementType x, RBTree T)
{
	Position TmpCell;

	while (T) {
		if (x < T->Element)
			T = T->Left;
		else if (x > T->Element)
			T = T->Right;
		else
			break;
	}
	if (T) {
		TmpCell = T;
		if (T->Left && T->Right) {
			TmpCell = FindMin(T->Right);
			T->Element = TmpCell->Element;
		}
		return TmpCell;
	}

	return NULL;
}

int OnLeft(Position Node)
{
	Position P;

	if (Node) {
		P = Node->Parent;
		return (P && (P->Left == Node));
	}

	return 0;
}

int OnRight(Position Node)
{
	Position P;

	if (Node) {
		P = Node->Parent;
		return (P && (P->Right == Node));
	}

	return 0;
}

int HaveRedChild(Position Node)
{
	Position L, R;

	if (Node) {
		L = Node->Left;
		R = Node->Right;
		return ((L && L->Color == RED) || (R && R->Color == RED));
	}

	return 0;
}

void SwapColor(Position P1, Position P2)
{
	NodeColor TmpColor;

	if (P1 && P2) {
		TmpColor = P1->Color;
		P1->Color = P2->Color;
		P2->Color = TmpColor;
	}
}

/*
 * According to the definition of red black tree, if
 * node's color is black, then its sibling must be exist.
 */
void FixDoubleBlack(Position Node, RBTree *T)
{
	Position P, S, SL, SR, L, R;

	if (!Node->Parent)
		return;

	P = Node->Parent;
	S = OnLeft(Node)? P->Right : P->Left;
	SL = S->Left;
	SR = S->Right;
	L = Node->Left;
	R = Node->Right;

	if (S->Color == RED) {
		if (OnLeft(Node)) {
			SL->Color = RED;
			S->Color = BLACK;
			LeftRotate(P, T);
			if (!L) {
				P->Left = R;
				if (R) R->Parent = P;
			} else {
				P->Left = L;
				L->Parent = P;
			}
		} else {
			SR->Color = RED;
			S->Color = BLACK;
			RightRotate(P, T);
			if (!R) {
				P->Right = L;
				if (L) L->Parent = P;
			} else {
				P->Right = R;
				R->Parent = P;
			}
		}
		free(Node);
	} else if (HaveRedChild(S)) {
		if (OnLeft(Node)) {
			if (SR) {
				SwapColor(P, S);
				SR->Color = BLACK;
				LeftRotate(P, T);
			} else {
				RightRotate(S, T);
				LeftRotate(P, T);
				SL->Color = P->Color;
				P->Color = BLACK;
			}
			if (!L) {
				P->Left = R;
				if (R) R->Parent = P;
			} else {
				P->Left = L;
				L->Parent = P;
			}
		} else {
			if (SL) {
				SwapColor(P, S);
				SL->Color = BLACK;
				RightRotate(P, T);
			} else {
				LeftRotate(S, T);
				RightRotate(P, T);
				SR->Color = P->Color;
				P->Color = BLACK;
			}
			if (!R) {
				P->Right = L;
				if (L) L->Parent = P;
			} else {
				P->Right = R;
				R->Parent = P;
			}
		}
		free(Node);
	} else {
		/* u,v,s black */
		if (P->Color == RED) {
			P->Color = BLACK;
			S->Color = RED;
			if (OnLeft(Node)) {
				if (!L) {
					P->Left = R;
					if (R) R->Parent = P;
				} else {
					P->Left = L;
					L->Parent = P;
				}
			} else {
				if (!R) {
					P->Right = L;
					if (L) L->Parent = P;
				} else {
					P->Right = R;
					R->Parent = P;
				}
			}
			free(Node);
		} else {
			S->Color = RED;
			FixDoubleBlack(P, T);
			if (OnLeft(Node)) {
				if (!L) {
					P->Left = R;
					if (R) R->Parent = P;
				} else {
					P->Left = L;
					L->Parent = P;
				}
			} else {
				if (!R) {
					P->Right = L;
					if (L) L->Parent = P;
				} else {
					P->Right = R;
					R->Parent = P;
				}
			}
			free(Node);
		}
	}
}

void Delete(ElementType x, RBTree *T)
{
	Position Node, L, R;

	Node = Successor(x, *T);
	/* x not exist */
	if (!Node)
		return;
	/* if Node is red, it must be leaf, and must have a black parent */
	if (Node->Color == RED) {
		if (OnLeft(Node))
			Node->Parent->Left = NULL;
		else
			Node->Parent->Right = NULL;
		free(Node);
	} else if (HaveRedChild(Node)) {
		/* remember that Node only have one child */
		L = Node->Left;
		R = Node->Right;
		/*
		 * Node is root, so no need set its color here, we
		 * will set its color at the end of function
		 */
		if (Node == *T) {
			if (L) {
				L->Parent = NULL;
				*T = L;
			}
			else {
				R->Parent = NULL;
				*T = R;
			}
		} else if (OnLeft(Node)) {
			if (L) {
				L->Color = BLACK;
				Node->Parent->Left = L;
				L->Parent = Node->Parent;
			} else {
				R->Color = BLACK;
				Node->Parent->Left = R;
				R->Parent = Node->Parent;
			}
		} else {
			if (L) {
				L->Color = BLACK;
				Node->Parent->Right = L;
				L->Parent = Node->Parent;
			} else {
				R->Color = BLACK;
				Node->Parent->Right = R;
				R->Parent = Node->Parent;
			}
		}
		/* free deleted node */
		free(Node);
	} else {
		if (Node == *T) {
			*T = NULL;
			free(Node);
			return;
		}
		FixDoubleBlack(Node, T);
	}

	if (*T)
		(*T)->Color = BLACK;
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
		if (T->Parent)
			fprintf(stdout, "\tParent->Element:%d Parent->Color:%s\n", T->Parent->Element, T->Parent->Color ? "BLACK" : "RED");
		InOrder(T->Right);
	}
}
