#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

DEFINE_ARRAY_LIST(int, 12)
DEFINE_ARRAY_LIST_PTR(int, 12)
DEFINE_CIRCULAR_ARRAY_LIST(int, 12)
DEFINE_CIRCULAR_ARRAY_LIST_PTR(int, 12)
DEFINE_LINKED_LIST(int)
DEFINE_LINKED_LIST_PTR(int)

int main(void) {

	// array list
	{
		List_int list = { 0 };

		for (int i = 0; i < 10; i++) {
			al_int_push(&list, i);
		}
		assert(list.length == 10);
		for (int i = 0; i < 10; i++) {
			assert(al_int_get(&list, i) == i);
		}
		for (int i = 9; i >= 0; i--) {
			assert(al_int_pop(&list) == i);
		}
		assert(list.length == 0);

		for (int i = 0; i < 10; i++) {
			al_int_push(&list, i);
		}
		assert(list.length == 10);
		al_int_insert(&list, 4, 44);
		assert(list.length == 11);
		assert(al_int_get(&list, 4) == 44);
		assert(al_int_get(&list, list.length - 1) == 9);
		al_int_set(&list, 0, 11);
		assert(al_int_get(&list, 0) == 11);

		al_int_remove(&list, 4);
		assert(al_int_get(&list, 4) == 4);

		al_int_remove(&list, 0);
		assert(al_int_get(&list, 0) == 1);

		al_int_remove(&list, list.length - 1);
		assert(al_int_get(&list, list.length - 1) == 8);
		assert(list.length == 8);

	}
	{

		int values[32] = { 1, 2, 3, 4, 5, 6 };

		List_int_ptr list = { 0 };

		for (int i = 0; i < 6; i++) {
			al_int_ptr_push(&list, &(values[i]));
		}

		for (int i = 5; i >= 0; i--) {
			assert(*(al_int_ptr_pop(&list)) == values[i]);
		}


	}


	// circular array list
	{
		CList_int list = { 0 };

		for (int i = 0; i < 10; i++) {
			cl_int_push_tail(&list, i);
		}
		assert(cl_int_length(&list) == 10);
		for (int i = 0; i < 10; i++) {
			assert(cl_int_get(&list, i) == i);
		}
		for (int i = 9; i >= 0; i--) {
			assert(cl_int_pop_tail(&list) == i);
		}
		assert(cl_int_length(&list) == 0);

		for (int i = 0; i < 10; i++) {
			cl_int_push_head(&list, i);
		}
		assert(cl_int_length(&list) == 10);
		for (int i = 0; i < 10; i++) {
			assert(cl_int_get(&list, i) == 9 - i);
		}
		for (int i = 9; i >= 0; i--) {
			assert(cl_int_pop_head(&list) == i);
		}
		assert(cl_int_length(&list) == 0);

		for (int i = 0; i < 10; i++) {
			cl_int_push_tail(&list, i);
		}
		assert(cl_int_length(&list) == 10);
		cl_int_insert(&list, 4, 44);
		assert(cl_int_length(&list) == 11);
		assert(cl_int_get(&list, 4) == 44);
		assert(cl_int_get(&list, cl_int_length(&list) - 1) == 9);
		cl_int_set(&list, 0, 11);
		assert(cl_int_get(&list, 0) == 11);

		cl_int_remove(&list, 4);
		assert(cl_int_get(&list, 4) == 4);

		cl_int_remove(&list, 0);
		assert(cl_int_get(&list, 0) == 1);

		cl_int_remove(&list, cl_int_length(&list) - 1);
		assert(cl_int_get(&list, cl_int_length(&list) - 1) == 8);
		assert(cl_int_length(&list) == 8);

		cl_int_pop_head(&list);
		cl_int_pop_head(&list);
		cl_int_pop_head(&list);
		assert(cl_int_length(&list) == 5);

		assert(list.head == 3);
		assert(list.tail == 8);

		cl_int_push_tail(&list, 44);
		cl_int_push_tail(&list, 55);
		cl_int_push_tail(&list, 66);
		cl_int_push_tail(&list, 77);
		cl_int_push_tail(&list, 88);

		assert(list.tail == 13);
		assert(cl_int_length(&list) == 10);

	}
	{
		CList_int_ptr list = { 0 };
		int v[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int w[] = { 0, 11, 22, 33, 44, 55, 66, 77, 88, 99 };

		for (int i = 0; i < 10; i++) {
			cl_int_ptr_push_tail(&list, &v[i]);
		}
		assert(cl_int_ptr_length(&list) == 10);
		for (int i = 0; i < 10; i++) {
			assert(*cl_int_ptr_get(&list, i) == i);
		}
		for (int i = 9; i >= 0; i--) {
			assert(cl_int_ptr_pop_tail(&list) == &v[i]);
		}
		assert(cl_int_ptr_length(&list) == 0);

		for (int i = 0; i < 10; i++) {
			cl_int_ptr_push_head(&list, &v[i]);
		}
		assert(cl_int_ptr_length(&list) == 10);
		for (int i = 0; i < 10; i++) {
			assert(*cl_int_ptr_get(&list, i) == 9 - i);
		}
		for (int i = 9; i >= 0; i--) {
			assert(cl_int_ptr_pop_head(&list) == &v[i]);
		}
		assert(cl_int_ptr_length(&list) == 0);

		for (int i = 0; i < 10; i++) {
			cl_int_ptr_push_tail(&list, &v[i]);
		}
		assert(cl_int_ptr_length(&list) == 10);
		cl_int_ptr_insert(&list, 4, &w[4]);
		assert(cl_int_ptr_length(&list) == 11);
		assert(*cl_int_ptr_get(&list, 4) == w[4]);
		assert(*cl_int_ptr_get(&list, cl_int_ptr_length(&list) - 1) == 9);
		cl_int_ptr_set(&list, 0, &w[1]);
		assert(*cl_int_ptr_get(&list, 0) == w[1]);

		cl_int_ptr_remove(&list, 4);
		assert(*cl_int_ptr_get(&list, 4) == 4);

		cl_int_ptr_remove(&list, 0);
		assert(*cl_int_ptr_get(&list, 0) == 1);

		cl_int_ptr_remove(&list, cl_int_ptr_length(&list) - 1);
		assert(*cl_int_ptr_get(&list, cl_int_ptr_length(&list) - 1) == 8);
		assert(cl_int_ptr_length(&list) == 8);

		cl_int_ptr_pop_head(&list);
		cl_int_ptr_pop_head(&list);
		cl_int_ptr_pop_head(&list);
		assert(cl_int_ptr_length(&list) == 5);

		assert(list.head == 3);
		assert(list.tail == 8);

		cl_int_ptr_push_tail(&list, &w[4]);
		cl_int_ptr_push_tail(&list, &w[5]);
		cl_int_ptr_push_tail(&list, &w[6]);
		cl_int_ptr_push_tail(&list, &w[7]);
		cl_int_ptr_push_tail(&list, &w[8]);

		assert(list.tail == 13);
		assert(cl_int_ptr_length(&list) == 10);

	}

	// linked list
	{
		LList_int *head = ll_int_push(NULL, 0);
		LList_int *tail = head;
		for (int i = 1; i < 10; i++) {
			tail = ll_int_push(tail, i);
		}
		assert(ll_int_length(head) == 10);
		int i = 0;
		for (LList_int *node = head; node != NULL; node = node->next) {
			assert(node->elm == i++);
		}
		assert(tail->elm == 9);
		i = 10;
		for (LList_int *node = tail; node != NULL; node = node->prev) {
			assert(node->elm == --i);
		}
		tail = ll_int_pop(tail);
		assert(tail->elm == 8);

		while (head != NULL) {
			head = ll_int_remove(head);
		}
		assert(ll_int_length(head) == 0);
		tail = NULL;

		tail = ll_int_insert(NULL, 0);
		head = tail;

		tail = ll_int_insert(NULL, 9);
		head = tail;
		for (int i = 8; i >= 0; i--) {
			head = ll_int_insert(head, i);
		}

		i = 10;
		for (LList_int *node = tail; node != NULL; node = node->prev) {
			assert(node->elm == --i);
		}

		i = 0;
		for (LList_int *node = head; node != NULL; node = node->next) {
			assert(node->elm == i);
			if (node->elm == 4) {
				node = ll_int_remove(node);
				break;
			}
			i++;
		}
		assert(ll_int_length(head) == 9);

		ll_int_clear(head);
		head = NULL;
		tail = NULL;

	}
	{
		int v[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int w[] = { 0, 11, 22, 33, 44, 55, 66, 77, 88, 99 };
		LList_int_ptr *head = ll_int_ptr_push(NULL, &v[0]);
		LList_int_ptr *tail = head;
		for (int i = 1; i < 10; i++) {
			tail = ll_int_ptr_push(tail, &v[i]);
		}
		assert(ll_int_ptr_length(head) == 10);
		int i = 0;
		for (LList_int_ptr *node = head; node != NULL; node = node->next) {
			assert(*node->elm == i++);
		}
		assert(*tail->elm == 9);
		i = 10;
		for (LList_int_ptr *node = tail; node != NULL; node = node->prev) {
			assert(*node->elm == --i);
		}
		tail = ll_int_ptr_pop(tail);
		assert(*tail->elm == 8);

		while (head != NULL) {
			head = ll_int_ptr_remove(head);
		}
		assert(ll_int_ptr_length(head) == 0);
		tail = NULL;

		tail = ll_int_ptr_insert(NULL, &v[0]);
		head = tail;

		tail = ll_int_ptr_insert(NULL, &v[9]);
		head = tail;
		for (int i = 8; i >= 0; i--) {
			head = ll_int_ptr_insert(head, &v[i]);
		}

		i = 10;
		for (LList_int_ptr *node = tail; node != NULL; node = node->prev) {
			assert(*node->elm == --i);
		}

		i = 0;
		for (LList_int_ptr *node = head; node != NULL; node = node->next) {
			assert(*node->elm == i);
			if (*node->elm == 4) {
				node = ll_int_ptr_remove(node);
				break;
			}
			i++;
		}
		assert(ll_int_ptr_length(head) == 9);

		ll_int_ptr_clear(head);
		head = NULL;
		tail = NULL;

	}
	return 0;
}
