#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

#define rbtree_red(node) ((node)->color = 1)
#define rbtree_black(node) ((node)->color = 0)
#define rbtree_is_red(node) ((node)->color)
#define rbtree_is_black(node) (!rbtree_is_red(node))

rbtree rbtree_min(rbtree node, rbtree sentinel)
{
	while (node->left != sentinel) {
		node = node->left;
	}

	return node;
}

rbtree rbtree_max(rbtree node, rbtree sentinel)
{
	while (node->right != sentinel) {
		node = node->right;
	}

	return node;
}

rbtree rbtree_find(rbtree root, rbtree sentinel, element_type x)
{
	while (root != sentinel) {
		if (x < root->element)
			root = root->left;
		else if (x > root->element)
			root = root->right;
		else
			break;
	}

	return root;
}

void rbtree_left_rotate(rbtree *root, rbtree sentinel, rbtree node)
{
	rbtree rchild;

	rchild = node->right;
	node->right = rchild->left;

	if (rchild->left != sentinel) {
		rchild->left->parent = node;
	}

	rchild->parent = node->parent;

	if (node == *root)
		*root = rchild;

	else if (node->parent->left == node)
		node->parent->left = rchild;
	else
		node->parent->right = rchild;

	rchild->left = node;

	node->parent = rchild;
}

void rbtree_right_rotate(rbtree *root, rbtree sentinel, rbtree node)
{
	rbtree lchild;

	lchild = node->left;
	node->left = lchild->right;

	if (lchild->right != sentinel)
		lchild->right->parent = node;

	lchild->parent = node->parent;

	if (node == *root)
		*root = lchild;

	else if (node->parent->left == node)
		node->parent->left = lchild;
	else
		node->parent->right = lchild;

	lchild->right = node;

	node->parent = lchild;
}

void rbtree_insert(rbtree *root, rbtree sentinel, rbtree node)
{
	rbtree temp;

	if (*root == sentinel) {
		node->parent = NULL;
		node->left = sentinel;
		node->right = sentinel;
		rbtree_black(node);
		*root = node;
		return;
	}

	temp = *root;

	for (; ;) {

		if (node->element < temp->element) {
			if (temp->left == sentinel) {
				temp->left = node;
				break;
			}

			temp = temp->left;
			continue;
		}

		if (node->element >= temp->element) {
			if (temp->right == sentinel) {
				temp->right = node;
				break;
			}

			temp = temp->right;
			continue;
		}
	}

	node->parent = temp;
	node->left = sentinel;
	node->right = sentinel;

	rbtree_red(node);

	/* reblance tree */

	while (node != *root && rbtree_is_red(node->parent)) {

		if (node->parent == node->parent->parent->left) {
			temp = node->parent->parent->right;

			if (rbtree_is_red(temp)) {
				rbtree_black(temp);
				rbtree_black(node->parent);
				rbtree_red(node->parent->parent);
				node = node->parent->parent;

			} else {
				if (node->parent->right == node) {
					node = node->parent;
					rbtree_left_rotate(root, sentinel, node);
				}

				rbtree_black(node->parent);
				rbtree_red(node->parent->parent);
				rbtree_right_rotate(root, sentinel, node->parent->parent);
			}

		} else {
			temp = node->parent->parent->left;

			if (rbtree_is_red(temp)) {
				rbtree_black(node->parent);
				rbtree_black(temp);
				rbtree_red(node->parent->parent);
				node = node->parent->parent;

			} else {
				if (node->parent->left == node) {
					node = node->parent;
					rbtree_right_rotate(root, sentinel, node);
				}

				rbtree_black(node->parent);
				rbtree_red(node->parent->parent);
				rbtree_left_rotate(root, sentinel, node->parent->parent);
			}
		}
	}

	rbtree_black(*root);
}

void rbtree_delete(rbtree *root, rbtree sentinel, rbtree node)
{
	int is_red;
	rbtree subst, temp, sbl;

	if (node->left == sentinel) {
		subst = node;
		temp = node->right;

	} else if (node->right == sentinel) {
		subst = node;
		temp = node->left;

	} else {
		subst = rbtree_min(node->right, sentinel);
		temp = subst->right;
	}

	if (subst == *root) {
		*root = temp;
		rbtree_black(*root);
		return;
	}

	is_red = subst->color;

	if (subst == subst->parent->left) {
		subst->parent->left = temp;

	} else {
		subst->parent->right = temp;
	}

	if (subst == node) {
		temp->parent = subst->parent;

	} else {
		if (subst->parent == node) {
			temp->parent = subst;

		} else {
			temp->parent = subst->parent;
		}

		subst->left = node->left;
		subst->right = node->right;
		subst->parent = node->parent;
		subst->color = node->color;

		if (node == *root) {
			*root = subst;

		} else if (node == node->parent->left) {
			node->parent->left = subst;

		} else {
			node->parent->right = subst;
		}

		if (subst->left != sentinel) {
			subst->left->parent = subst;
		}

		if (subst->right != sentinel) {
			subst->right->parent = subst;
		}
	}

	if (is_red) {
		return;
	}

	/* reblance tree */

	while (temp != *root && rbtree_is_black(temp)) {
		if (temp == temp->parent->left) {
			sbl = temp->parent->right;

			if (rbtree_is_red(sbl)) {
				rbtree_black(sbl);
				rbtree_red(temp->parent);
				rbtree_left_rotate(root, sentinel, temp->parent);
				sbl = temp->parent->right;
			}

			if (rbtree_is_black(sbl->left) && rbtree_is_black(sbl->right)) {
				rbtree_red(sbl);
				temp = temp->parent;

			} else {
				if (rbtree_is_black(sbl->right)) {
					rbtree_right_rotate(root, sentinel, sbl);
					sbl = sbl->parent;
				}

				sbl->color = temp->parent->color;
				rbtree_black(temp->parent);
				rbtree_black(sbl->right);
				rbtree_left_rotate(root, sentinel, temp->parent);
				temp = *root;
			}
		} else {
			sbl = temp->parent->left;

			if (rbtree_is_red(sbl)) {
				rbtree_black(sbl);
				rbtree_red(temp->parent);
				rbtree_right_rotate(root, sentinel, temp->parent);
				sbl = temp->parent->left;
			}

			if (rbtree_is_black(sbl->left) && rbtree_is_black(sbl->right)) {
				rbtree_red(sbl);
				temp = temp->parent;

			} else {
				if (rbtree_is_black(sbl->left)) {
					rbtree_left_rotate(root, sentinel, sbl);
					sbl = sbl->parent;
				}

				sbl->color = temp->parent->color;
				rbtree_black(temp->parent);
				rbtree_black(sbl->left);
				rbtree_right_rotate(root, sentinel, temp->parent);
				temp = *root;
			}
		}
	}

	rbtree_black(temp);
}

void inorder(rbtree root, rbtree sentinel)
{
	if (root != sentinel) {
		inorder(root->left, sentinel);
		fprintf(stdout, "key:%d color:%s\n", root->element, root->color ? "red" : "black");
		inorder(root->right, sentinel);
	}
}
