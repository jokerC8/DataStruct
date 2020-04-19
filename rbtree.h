#ifndef __RBTREE_H
#define __RBTREE_H

typedef int element_type;
struct rbtree_node;
typedef struct rbtree_node *rbtree;

struct rbtree_node {
	int color;
	element_type element;
	rbtree left;
	rbtree right;
	rbtree parent;
};

rbtree rbtree_min(rbtree node, rbtree sentinel);
rbtree rbtree_max(rbtree node, rbtree sentinel);
rbtree rbtree_find(rbtree node, rbtree sentinel, element_type x);
element_type retrive(struct rbtree_node *node);
void rbtree_delete(rbtree *root, rbtree sentinel, rbtree node);
void rbtree_insert(rbtree *root, rbtree sentinel, rbtree node);
void inorder(rbtree root, rbtree sentinel);
#endif
