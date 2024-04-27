#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


int main(void) {

	{
		BTree *node;
		BTree *root = bt_insert(NULL, 10);
		assert(root->elm == 10);
		assert(bt_length(root) == 1);

		node = bt_insert(root, 5);
		assert(root->left != NULL);
		assert(root->left->elm == 5);
		assert(bt_length(root) == 2);

		node = bt_insert(root, 15);
		assert(root->right != NULL);
		assert(root->right->elm == 15);
		assert(bt_length(root) == 3);

		assert(bt_check_bst(root) != 0);

		{
			BTree *leaf = bt_insert(root, 18);
			assert(node->right != NULL);
			assert(node->right->elm == 18);
			assert(bt_length(root) == 4);
		}
		{
			BTree *leaf = bt_insert(root, 13);
			assert(node->left != NULL);
			assert(node->left->elm == 13);
			assert(bt_length(root) == 5);
		}

		assert(bt_check_bst(root) != 0);

		node = bt_find(root, 18);
		assert(node != NULL);
		assert(node->elm == 18);

		{
			BTree *leaf = bt_insert(root, 17);
			assert(node->left != NULL);
			assert(node->left->elm == 17);
			assert(bt_length(root) == 6);
		}

		node = bt_remove(root, 15);
		assert(node != NULL);
		assert(node->elm == 13);
		assert(bt_length(root) == 5);

		node = bt_find(root, 15);
		assert(node == NULL);

		root = bt_remove(root, 10);
		assert(root != NULL);
		assert(root->elm == 5);
		assert(bt_length(root) == 4);

		node = bt_find(root, 17);
		assert(node != NULL);
		assert(node->elm == 17);
	}

	return 0;
}
