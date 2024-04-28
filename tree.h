
#ifndef __TREE__H__
#define __TREE__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Binary Search Tree
 */
#define DEFINE_BTREE(Type, Compare)												\
	typedef struct BTree_##Type {												\
		Type elm;																\
		BTree_##Type *left;														\
		BTree_##Type *right;													\
	} BTree_##Type;																\
																				\
	int bt_##Type##_length(BTree_##Type *root) {								\
	}																			\

/*
 * Binary Search Tree
 * Unbalanced. Inserting an element allocs memory for the node,
 * and removing frees it. Functions return a node.
 *
 */
struct BTree;

typedef struct BTree {
	long elm;
	struct BTree *left;
	struct BTree *right;
} BTree;

BTree *_bt_create_leaf(BTree *node, long elm);
BTree *_bt_remove_node(BTree *node, long elm);
BTree *_bt_merge(BTree *lesser, BTree *greater);

int bt_compare(long a, long b) {
	return (int) (a - b);
}

int bt_length(BTree *root) {
	if (root == NULL) {
		return 0;
	}
	else {
		return 1 + bt_length(root->left) + bt_length(root->right);
	}
}

int bt_check_bst(BTree *node) {
	int valid = 1;
	if (node->left) {
		valid = valid &&
			bt_check_bst(node->left) && 
			bt_compare(node->left->elm, node->elm) < 0;
	}
	if (node->right) {
		valid = valid &&
			bt_check_bst(node->right) &&
			bt_compare(node->right->elm, node->elm) >= 0;
	}
	return valid;
}


BTree *bt_insert(BTree *root, long elm) {
	if (root == NULL) {
		root = malloc(sizeof(BTree));
		*root = (BTree) { elm, NULL, NULL };
		return root;
	}
	else {
		return _bt_create_leaf(root, elm);
	}
}

BTree *_bt_create_leaf(BTree *node, long elm) {
	if (bt_compare(elm, node->elm) < 0) {
		if (node->left == NULL) {
			node->left = malloc(sizeof(BTree));
			*node->left = (BTree) { elm, NULL, NULL };
			return node->left;
		}
		else {
			return _bt_create_leaf(node->left, elm);
		}
	}
	else {
		if (node->right == NULL) {
			node->right = malloc(sizeof(BTree));
			*node->right = (BTree) { elm, NULL, NULL };
			return node->right;
		}
		else {
			return _bt_create_leaf(node->right, elm);
		}
	}
}

BTree *bt_find(BTree *root, long elm) {
	if (root == NULL) {
		return NULL;
	}
	else {
		int c = bt_compare(elm, root->elm);
		if (c == 0) {
			return root;
		}
		else if (c < 0) {
			return bt_find(root->left, elm);
		}
		else {
			return bt_find(root->right, elm);
		}
	}
}

BTree *bt_remove(BTree *root, long elm) {
	if (bt_compare(elm, root->elm) == 0) {
		BTree *lesser = root->left;
		BTree *greater = root->right;
		free(root);
		return _bt_merge(lesser, greater);
	}
	else {
		return _bt_remove_node(root, elm);
	}
}

BTree *_bt_remove_node(BTree *node, long elm) {
	if (bt_compare(elm, node->elm) < 0) {
		if (node->left == NULL) {
			return NULL;
		}
		else if (bt_compare(node->left->elm, elm) == 0) {
			BTree *lesser = node->left->left;
			BTree *greater = node->left->right;
			free(node->left);
			if (lesser == NULL) {
				node->left = greater;
			}
			else {
				node->left = _bt_merge(lesser, greater);
			}
			return node->left;
		}
		else {
			return _bt_remove_node(node->left, elm);
		}
	}
	else {
		if (node->right == NULL) {
			return NULL;
		}
		else if (bt_compare(node->right->elm, elm) == 0) {
			BTree *lesser = node->right->left;
			BTree *greater = node->right->right;
			free(node->right);
			if (lesser == NULL) {
				node->right = greater;
			}
			else {
				node->right = _bt_merge(lesser, greater);
			}
			return node->right;
		}
		else {
			return _bt_remove_node(node->right, elm);
		}
	}
}

// merge the greater tree into the lesser tree
// return the root of the tree, which is the same as the root of the lesser tree.
BTree *_bt_merge(BTree *lesser, BTree *greater) {
	if (lesser->right == NULL) {
		lesser->right = greater;
		return lesser;
	}
	else {
		return _bt_merge(greater, lesser->right);
	}
}

#endif  // __TREE__H__
