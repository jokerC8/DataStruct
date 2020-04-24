#include <stdio.h>

#include "rbtree.h"

#define rbtree_red(node) ((node)->color = 0)
#define rbtree_black(node) ((node)->color = 1)
#define rbtree_is_red(node) ((node)->color == 0)
#define rbtree_is_black(node) (!rbtree_is_red(node))

void rbtree_left_rotate(rbtree *root, rbtree node)
{
	rbtree r_child;

	r_child = node->right;

	node->right = r_child->left;
	if (r_child->left)
		r_child->left->parent = node;

	r_child->parent = node->parent;

	if (node == *root)
		*root = node;
	else if (node == node->parent->left)
		node->parent->left = r_child;
	else
		node->parent->right = r_child;

	node->parent = r_child;

	r_child->left = node;
}

void rbtree_right_rotate(rbtree *root, rbtree node)
{
	rbtree l_child;

	l_child = node->left;

	node->left = l_child->right;
	if (l_child->right)
		l_child->right->parent = node;

	l_child->parent = node->parent;

	if (node == *root)
		*root = node;
	else if (node == node->parent->left)
		node->parent->left = l_child;
	else
		node->parent->right = l_child;

	node->parent = l_child;

	l_child->right = node;
}

void rbtree_insert(rbtree *root, rbtree node)
{
	rbtree temp;

	if (!*root) {
		*root = node;
		rbtree_black(node);
		return;
	}

	temp = *root;

	for (; ;) {
		if (node->key < temp->key) {
			if (!temp->left) {
				temp->left = node;
				break;
			}

			temp = temp->left;
			continue;

		} else {
			if (!temp->right) {
				temp->right = node;
				break;
			}

			temp = temp->right;
			continue;
		}
	}

	node->parent = temp;

	rbtree_red(node);

	while (node != *root && rbtree_is_red(node->parent)) {
		int is_left;
		rbtree parent, uncle;

		parent = node->parent;
		is_left = (parent == parent->parent->left);
		uncle = is_left ? parent->parent->right : parent->parent->left;

		if (uncle && rbtree_is_red(uncle)) {
			rbtree_black(uncle);
			rbtree_black(parent);
			rbtree_red(parent->parent);
			node = parent->parent;
			continue;
		}

		if (is_left) {
			if (node == parent->right) {
				rbtree_left_rotate(root, parent);
				parent = node;
			}

			rbtree_black(parent);
			rbtree_red(parent->parent);
			rbtree_right_rotate(root, parent->parent);

		} else {
			if (node == parent->left) {
				rbtree_right_rotate(root, parent);
				parent = node;
			}

			rbtree_black(parent);
			rbtree_red(parent->parent);
			rbtree_left_rotate(root, parent->parent);
		}
	}

	rbtree_black(*root);
}

void rbtree_delete(rbtree *root, rbtree node)
{
	rbtree temp, subst;

	if (!node->left) {
		subst = node;
		temp = node->right; // temp may be NULL

	} else if (!node->right) {
		subst = node;
		temp = node->left;

	} else {
		subst = rbtree_min(node->right);
		temp = subst->right; // temp may be NULL
	}

	if (subst == *root) {
		*root = temp;
		if (*root) {
			(*root)->parent = NULL;
			rbtree_black(*root);
		}
		return;
	}

}

void rbtree_inorder(rbtree root)
{
	if (root) {
		rbtree_inorder(root->left);
		fprintf(stdout, "key:%d\n", root->key);
		rbtree_inorder(root->right);
	}
}
