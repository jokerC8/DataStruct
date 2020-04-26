#ifndef __TREE_H
#define __TREE_H

struct TreeNode;
typedef struct TreeNode *Tree;
typedef struct TreeNode *Position;

void MakeEmpty(Tree T);
Position Find(int x, Tree T);
Position FindMin(Tree T);
Position FindMax(Tree T);
Tree Insert(int x, Tree T);
Tree Delete(int x, Tree T);
int Retrive(Position P);
int Height(Tree T);
void PrintTree(Tree T);

#endif
