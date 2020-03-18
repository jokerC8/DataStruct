#ifndef __AVL_TREE_H
#define __AVL_TREE_H

struct AVLTreeNode;
typedef struct AVLTreeNode *AVLTree;
typedef struct AVLTreeNode *Position;

AVLTree MakeEmpty(AVLTree T);
Position Find(int x, AVLTree T);
Position FindMin(AVLTree T);
Position FindMax(AVLTree T);
AVLTree Insert(int x, AVLTree T);
AVLTree Delete(int x, AVLTree T);
int Height(AVLTree T);
int Retrive(Position P);
void PrintTree(AVLTree T);

#endif
