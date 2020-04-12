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

	while (Node != *T && Node->Parent->Color == RED && Node->Color == RED) {

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

	if (!Find(X, T)) {
		T = __BSTInsert(P, T);
		Rebalance(P, &T);
	}
	else
		free(P);

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
	Position P, S, SL, SR;

	if (!Node->Parent)
		return;

	P = Node->Parent;
	S = OnLeft(Node)? P->Right : P->Left;
	SL = S->Left;
	SR = S->Right;

	if (S->Color == RED) {
		fprintf(stdout, "FixDoubleBlack Sibling is RED\n");
		if (OnLeft(Node)) {
			LeftRotate(P, T);
			if (HaveRedChild(SL)) {
				if (SL->Right) {
					LeftRotate(P, T);
					if (SL->Left && SL->Right) {
						S->Color = BLACK;
						SL->Color = RED;
						SL->Right->Color = BLACK;
					} else {
						S->Color = BLACK;
						P->Color = RED;
					}
				} else {
					RightRotate(SL, T);
					LeftRotate(P, T);
					S->Color = BLACK;
					P->Color = RED;
					SL->Color = RED;
					SL->Parent->Color = BLACK;
				}
			} else {
				S->Color = BLACK;
				SL->Color = RED;
			}
		} else {
			RightRotate(P, T);
			if (HaveRedChild(SR)) {
				if (SR->Left) {
					RightRotate(P, T);
					if (SR->Left && SR->Right) {
						S->Color = BLACK;
						SR->Color = RED;
						SR->Left->Color = BLACK;
					} else {
						S->Color = BLACK;
						P->Color = RED;
					}
				} else {
					LeftRotate(SR, T);
					RightRotate(P, T);
					S->Color = BLACK;
					P->Color = RED;
					SR->Color = RED;
					SR->Parent->Color = BLACK;
				}
			} else {
				S->Color = BLACK;
				SR->Color = RED;
			}
		}
	} else if (HaveRedChild(S)) {
		fprintf(stdout, "FixDoubleBlack Sibling is BLACK and have a red child\n");
		if (OnLeft(Node)) {
			if (SR) {
				SwapColor(P, S);
				SR->Color = BLACK;
				LeftRotate(P, T);
			} else {
				SL->Color = P->Color;
				P->Color = BLACK;
				RightRotate(S, T);
				LeftRotate(P, T);
			}
		} else {
			if (SL) {
				SwapColor(P, S);
				SL->Color = BLACK;
				RightRotate(P, T);
			} else {
				SR->Color = P->Color;
				P->Color = BLACK;
				LeftRotate(S, T);
				RightRotate(P, T);
			}
		}
	} else {
		fprintf(stdout, "FixDoubleBlack Sibling is BLACK and all child is black\n");
		/* u,v,s black */
		if (P->Color == RED) {
			P->Color = BLACK;
			S->Color = RED;
		} else {
			S->Color = RED;
			FixDoubleBlack(P, T);
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
		fprintf(stdout, "Node is leaf, and is red\n");
		if (OnLeft(Node))
			Node->Parent->Left = NULL;
		else
			Node->Parent->Right = NULL;

		free(Node);
	} else if (HaveRedChild(Node)) {
		fprintf(stdout, "Node have red child\n");
		/* remember that Node only have one child */
		L = Node->Left;
		R = Node->Right;
		/*
		 * Node is root, so no need set its color here, we
		 * will set its color at the end of function
		 */
		if (!Node->Parent) {
			if (L) {
				L->Parent = NULL;
				*T = L;
			} else {
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
		FixDoubleBlack(Node, T);
		if (!Node->Parent) {
			*T = NULL;
		} else {
			L = Node->Left;
			R = Node->Right;
			if (OnLeft(Node)) {
				if (!L) {
					Node->Parent->Left = R;
					if (R) R->Parent = Node->Parent;
				} else {
					Node->Parent->Left = L;
					L->Parent = Node->Parent;
				}
			} else {
				if (!R) {
					Node->Parent->Right = L;
					if (L) L->Parent = Node->Parent;
				} else {
					Node->Parent->Right = R;
					R->Parent = Node->Parent;
				}
			}
		}
//		free(Node);
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

RBTree BuildTreeForTest(ElementType x, int c, RBTree T)
{
	if (!T) {
		T = malloc(sizeof(*T));
		if (!T) return NULL;
		T->Color = c;
		T->Element = x;
		T->Left = T->Right = T->Parent = 0;
	} else {
		if (x < T->Element) {
			T->Left = BuildTreeForTest(x, c, T->Left);
			T->Left->Parent = T;
		}
		else if (x > T->Element) {
			T->Right = BuildTreeForTest(x, c, T->Right);
			T->Right->Parent = T;
		}
	}

	return T;
}
