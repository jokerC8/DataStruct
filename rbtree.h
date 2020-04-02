#ifndef __RBTREE_H
#define __RBTREE_H

typedef int ElementType;

struct RBTreeNode;
typedef struct RBTreeNode *RBTree, *Position;

Position Find(ElementType x, RBTree T);
Position FindMin(RBTree T);
Position FindMax(RBTree T);
RBTree Insert(ElementType x, RBTree T);
RBTree Delete(ElementType x, RBTree T);
ElementType Retrive(Position P);
void InOrder(RBTree T);

#endif
