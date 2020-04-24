#ifndef __RBTREE_H
#define __RBTREE_H

struct rbtree_node;
typedef struct rbtree_node *rbtree;

typedef int element_type;

struct rbtree_node {
	int color;
	element_type key;
	rbtree left;
	rbtree right;
	rbtree parent;
};

rbtree rbtree_min(rbtree root);
rbtree rbtree_max(rbtree root);
void rbtree_inorder(rbtree root);
void rbtree_insert(rbtree *root, rbtree node);
void rbtree_delete(rbtree *root, rbtree node);

#endif
