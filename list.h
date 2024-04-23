
#ifndef __LIST__H__
#define __LIST__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Array List
 * Generic, simple, fast, unsafe array list.
 * No memory is allocated.
 * The array list has a fixed size, and boundaries are not checked.
 * The list is never resized.
 *
 * Prepare the list by using the macro DEFINE_ARRAY_LIST for value lists
 * or DEFINE_ARRAY_LIST_PTR for pointer lists. The first parameter is 
 * the type of the element and the second is the max size of the list.
 *
 * This will create a struct called List_<type>, so a list of ints 
 * will be List_int. Functions will have the prefix al_<type>_. The following
 * are the structs and functions for int and int* lists.
 *
 * This structure can be used as a queue. Push and Pop are O(1) and they
 * insert or remove an element at the tail of the list. To insert or remove
 * an element at the head, use insert(list, 0, elm) or remove(list, 0, elm),
 * but they run at O(n).
 *
 * DEFINE_ARRAY_LIST(int, 1024)
 * List_int
 * al_int_push			(list, elm)
 * al_int_pop			(list)					-> elm
 * al_int_insert		(list, index, elm)
 * al_int_remove		(list, index)
 * al_int_set			(list, index, elm)
 * al_int_get			(list, index)			-> elm
 * al_int_clear			(list)
 *
 * DEFINE_ARRAY_LIST_PTR(int, 1024)
 * List_int_ptr
 * al_int_ptr_push		(list, elm)
 * al_int_ptr_pop		(list)					-> elm
 * al_int_ptr_insert	(list, index, elm)
 * al_int_ptr_remove	(list, index)
 * al_int_ptr_set		(list, index, elm)
 * al_int_ptr_get		(list, index)			-> elm
 * al_int_ptr_clear		(list)
 *
 * Members of the list:
 * - elms: an array with the elements.
 * - length: the length of the array. Do not change this value.
 * 
 */

#define DEFINE_ARRAY_LIST(Type, size)									\
	typedef struct {													\
		Type elms[size];												\
		int length;														\
	} List_##Type;														\
																		\
	void al_##Type##_push(List_##Type *list, Type elm) {				\
		list->elms[list->length++] = elm;								\
	}																	\
																		\
	Type al_##Type##_pop(List_##Type *list) {							\
		return list->elms[--list->length];								\
	}																	\
																		\
	void al_##Type##_insert(List_##Type *list, int index, Type elm) {	\
		for (int i = list->length; i > index; i--) {					\
			list->elms[i] = list->elms[i-1];							\
		}																\
		list->elms[index] = elm;										\
		list->length += 1;												\
	}																	\
																		\
	void al_##Type##_remove(List_##Type *list, int index) {				\
		for (int i = index; i < list->length; i++) {					\
			list->elms[i] = list->elms[i+1];							\
		}																\
		list->length -= 1;												\
	}																	\
																		\
	void al_##Type##_set(List_##Type *list, int index, Type elm) {		\
		list->elms[index] = elm;										\
	}																	\
																		\
	Type al_##Type##_get(List_##Type *list, int index) {				\
		return list->elms[index];										\
	}																	\
																		\
	void al_##Type##_clear(List_##Type *list) {							\
		list->length = 0;												\
	}




#define DEFINE_ARRAY_LIST_PTR(Type, size)								\
	typedef struct {													\
		Type *elms[size];												\
		int length;														\
	} List_##Type##_ptr;												\
																		\
	void al_##Type##_ptr_push(List_##Type##_ptr *list, Type *elm) {		\
		list->elms[list->length++] = elm;								\
	}																	\
																		\
	Type *al_##Type##_ptr_pop(List_##Type##_ptr *list) {				\
		return list->elms[--list->length];								\
	}																	\
																		\
	void al_##Type##_ptr_insert(List_##Type##_ptr *list, int index, Type *elm) {	\
		for (int i = list->length; i > index; i--) {					\
			list->elms[i] = list->elms[i-1];							\
		}																\
		list->elms[index] = elm;										\
		list->length += 1;												\
	}																	\
																		\
	void al_##Type##_ptr_remove(List_##Type##_ptr *list, int index) {	\
		for (int i = index; i < list->length; i++) {					\
			list->elms[i] = list->elms[i+1];							\
		}																\
		list->length -= 1;												\
	}																	\
																		\
	void al_##Type##_ptr_set(List_##Type##_ptr *list, int index, Type *elm) {		\
		list->elms[index] = elm;										\
	}																	\
																		\
	Type *al_##Type##_ptr_get(List_##Type##_ptr *list, int index) {		\
		return list->elms[index];										\
	}																	\
																		\
	void al_##Type##_ptr_clear(List_##Type##_ptr *list) {				\
		list->length = 0;												\
	}
		

/*
 * Circular Array List
 * Generic, simple, fast, unsafe circular array list.
 * No memory is allocated.
 * The array list has a fixed size, and boundaries are not checked.
 * The list is never resized.
 *
 * A circular array list is such that if the list goes
 * over the boundaries set to it, it wraps around and continues from the 
 * other side. 
 *
 * It can be used as efficient queues and deques. Its functions push_tail 
 * and pop_tail are O(1) and insert or remove an element at the tail
 * of the list, and push_head and pop_head are O(1) are functions that do the
 * same at the head.
 *
 * This structure does not check if the head overtakes the tail, or
 * vice versa.
 *
 * The insert and remove functions shift the tail of the list, not the head,
 * so even though they have the same result, insert(list, 0, elm) is O(n),
 * while push_head(elm) is O(1).
 *
 * DEFINE_ARRAY_LIST(int, 1024)
 * CList_int
 * cl_int_length		(list)					-> int
 * cl_int_push_head		(list, elm)
 * cl_int_pop_head		(list)					-> elm
 * cl_int_push_tail		(list, elm)
 * cl_int_pop_tail		(list)					-> elm
 * cl_int_insert		(list, index, elm)
 * cl_int_remove		(list, index)
 * cl_int_set			(list, index, elm)
 * cl_int_get			(list, index)			-> elm
 * cl_int_clear			(list)
 *
 * DEFINE_ARRAY_LIST_PTR(int, 1024)
 * CList_int_ptr
 * cl_int_ptr_length	(list)					-> int
 * cl_int_ptr_push_head	(list, elm)
 * cl_int_ptr_pop_head	(list)					-> elm
 * cl_int_ptr_push_tail	(list, elm)
 * cl_int_ptr_pop_tail	(list)					-> elm
 * cl_int_ptr_insert	(list, index, elm)
 * cl_int_ptr_remove	(list, index)
 * cl_int_ptr_set		(list, index, elm)
 * cl_int_ptr_get		(list, index)			-> elm
 * cl_int_ptr_clear		(list)
 *
 * Members of the list:
 * - elms: an array with the elements.
 * - head: the head of the list, its first element.
 * - tail: the tail of the list, the next index after its last element.
 * 
 * The members head and tail may go over the limits of the size of the list,
 * but are corrected with a rest operator in order to get the real index
 * for each element. They are so that you can get the length of the list
 * by simply calculating their difference. If head and tail are equal, 
 * the list length is 0.
 *
 * The module operator (%) gives us the indices we need for a circular list,
 * but it only works for natural numbers. 
 * This means that if an head goes under 0, it will not wrap arround the
 * array as intended. For example, if head is -1, it will get an index -1, 
 * instead of size - 1.
 * I have written the function index for this reason. It does a trick
 * that allows us to have the same sequence of indices correctly output
 * from negative numbers as well as natural numbers at the cost of just a
 * couple of operations.
 * 
 */

#define DEFINE_CIRCULAR_ARRAY_LIST(Type, size)							\
	typedef struct {													\
		Type elms[size];												\
		int head;														\
		int tail;														\
	} CList_##Type;														\
																		\
	int cl_##Type##_index(int index) {									\
		return (index % size + size) % size;							\
	}																	\
																		\
	int cl_##Type##_length(CList_##Type *list) {						\
		return list->tail - list->head;									\
	}																	\
																		\
	void cl_##Type##_push_tail(CList_##Type *list, Type elm) {			\
		list->elms[cl_##Type##_index(list->tail++)] = elm;				\
	}																	\
																		\
	Type cl_##Type##_pop_tail(CList_##Type *list) {						\
		return list->elms[cl_##Type##_index(--list->tail)];				\
	}																	\
																		\
	void cl_##Type##_push_head(CList_##Type *list, Type elm) {			\
		list->elms[cl_##Type##_index(--list->head)] = elm;				\
	}																	\
																		\
	Type cl_##Type##_pop_head(CList_##Type *list) {						\
		return list->elms[cl_##Type##_index(list->head++)];				\
	}																	\
																		\
	void cl_##Type##_insert(CList_##Type *list, int index, Type elm) {	\
		for (int i = cl_##Type##_length(list); i > index; i--) {		\
			list->elms[cl_##Type##_index(list->head + i)] = list->elms[cl_##Type##_index(list->head + i - 1)];	\
		}																\
		list->elms[cl_##Type##_index(list->head + index)] = elm;					\
		list->tail += 1;												\
	}																	\
																		\
	void cl_##Type##_remove(CList_##Type *list, int index) {			\
		for (int i = index; i < cl_##Type##_length(list); i++) {		\
			list->elms[cl_##Type##_index(list->head + i)] = list->elms[cl_##Type##_index(list->head + i + 1)];	\
		}																\
		list->tail -= 1;												\
	}																	\
																		\
	void cl_##Type##_set(CList_##Type *list, int index, Type elm) {		\
		list->elms[cl_##Type##_index(list->head + index)] = elm;					\
	}																	\
																		\
	Type cl_##Type##_get(CList_##Type *list, int index) {				\
		return list->elms[cl_##Type##_index(list->head + index)];					\
	}																	\
																		\
	void cl_##Type##_clear(CList_##Type *list) {						\
		list->head = 0;													\
		list->tail = 0;													\
	}

#define DEFINE_CIRCULAR_ARRAY_LIST_PTR(Type, size)							\
	typedef struct {													\
		Type *elms[size];												\
		int head;														\
		int tail;														\
	} CList_##Type##_ptr;														\
																		\
	int cl_##Type##_ptr_index(int index) {									\
		return (index % size + size) % size;							\
	}																	\
																		\
	int cl_##Type##_ptr_length(CList_##Type##_ptr *list) {						\
		return list->tail - list->head;									\
	}																	\
																		\
	void cl_##Type##_ptr_push_tail(CList_##Type##_ptr *list, Type *elm) {			\
		list->elms[cl_##Type##_ptr_index(list->tail++)] = elm;				\
	}																	\
																		\
	Type *cl_##Type##_ptr_pop_tail(CList_##Type##_ptr *list) {						\
		return list->elms[cl_##Type##_ptr_index(--list->tail)];				\
	}																	\
																		\
	void cl_##Type##_ptr_push_head(CList_##Type##_ptr *list, Type *elm) {			\
		list->elms[cl_##Type##_ptr_index(--list->head)] = elm;				\
	}																	\
																		\
	Type *cl_##Type##_ptr_pop_head(CList_##Type##_ptr *list) {						\
		return list->elms[cl_##Type##_ptr_index(list->head++)];				\
	}																	\
																		\
	void cl_##Type##_ptr_insert(CList_##Type##_ptr *list, int index, Type *elm) {	\
		for (int i = cl_##Type##_ptr_length(list); i > index; i--) {		\
			list->elms[cl_##Type##_ptr_index(list->head + i)] = list->elms[cl_##Type##_ptr_index(list->head + i - 1)];	\
		}																\
		list->elms[cl_##Type##_ptr_index(list->head + index)] = elm;					\
		list->tail += 1;												\
	}																	\
																		\
	void cl_##Type##_ptr_remove(CList_##Type##_ptr *list, int index) {			\
		for (int i = index; i < cl_##Type##_ptr_length(list); i++) {		\
			list->elms[cl_##Type##_ptr_index(list->head + i)] = list->elms[cl_##Type##_ptr_index(list->head + i + 1)];	\
		}																\
		list->tail -= 1;												\
	}																	\
																		\
	void cl_##Type##_ptr_set(CList_##Type##_ptr *list, int index, Type *elm) {		\
		list->elms[cl_##Type##_ptr_index(list->head + index)] = elm;					\
	}																	\
																		\
	Type *cl_##Type##_ptr_get(CList_##Type##_ptr *list, int index) {				\
		return list->elms[cl_##Type##_ptr_index(list->head + index)];					\
	}																	\
																		\
	void cl_##Type##_ptr_clear(CList_##Type##_ptr *list) {						\
		list->head = 0;													\
		list->tail = 0;													\
	}

/*
 * Stack
 */
#define DEFINE_STACK(Type, size)													\
	typedef struct Stack_##Type {												\
		Type elms[size];													\
		int length;															\
	} Stack_##Type;															\
																			\
	int st_##Type##_length(Stack_##Type *stack) {						\
		return stack->length;									\
	}																	\
																		\
	void st_##Type##_push(Stack_##Type *stack, Type elm) {					\
		stack->elms[stack->length++] = elm;								\
	}																		\
																			\
	Type st_##Type##_pop(Stack_##Type *stack) {								\
		return stack->elms[--stack->length];								\
	}																		\
																			\
	Type st_##Type##_peek(Stack_##Type *stack) {							\
		return stack->elms[stack->length - 1];								\
	}																		\
																			\
	int st_##Type##_clear(Stack_##Type *stack) {							\
		stack->length = 0;													\
	}																		\

#define DEFINE_STACK_PTR(Type, size)										\
	typedef struct Stack_##Type##_ptr {										\
		Type *elms[size];													\
		int length;															\
	} Stack_##Type##_ptr;													\
																			\
	int st_##Type##_ptr_length(Stack_##Type##_ptr *stack) {						\
		return stack->length;												\
	}																		\
																			\
	void st_##Type##_ptr_push(Stack_##Type##_ptr *stack, Type *elm) {				\
		stack->elms[stack->length++] = elm;									\
	}																		\
																			\
	Type *st_##Type##_ptr_pop(Stack_##Type##_ptr *stack) {						\
		return stack->elms[--stack->length];								\
	}																		\
																			\
	Type *st_##Type##_ptr_peek(Stack_##Type##_ptr *stack) {						\
		return stack->elms[stack->length - 1];								\
	}																		\
																			\
	int st_##Type##_ptr_clear(Stack_##Type##_ptr *stack) {						\
		stack->length = 0;													\
	}																		\


/*
 * Queue
 */
#define DEFINE_QUEUE(Type, size)										\
	typedef struct Queue_##Type {											\
		Type elms[size];													\
		int head;															\
		int tail;															\
	} Queue_##Type;															\
																			\
	int qu_##Type##_length(Queue_##Type *queue) {							\
		return queue->tail - queue->head;									\
	}																		\
																			\
	void qu_##Type##_push(Queue_##Type *queue, Type elm) {					\
		queue->elms[queue->tail++ % size] = elm;							\
	}																		\
																			\
	Type qu_##Type##_pop(Queue_##Type *queue) {								\
		return queue->elms[queue->head++ % size];							\
	}																		\
																			\
	Type qu_##Type##_peek(Queue_##Type *queue) {							\
		return queue->elms[queue->head % size];								\
	}																		\
																			\
	int qu_##Type##_clear(Queue_##Type *queue) {							\
		queue->head = 0;													\
		queue->tail = 0;													\
	}																		\

#define DEFINE_QUEUE_PTR(Type, size)										\
	typedef struct Queue_##Type##_ptr {										\
		Type *elms[size];													\
		int head;															\
		int tail;															\
	} Queue_##Type##_ptr;													\
																			\
	int qu_##Type##_ptr_length(Queue_##Type##_ptr *queue) {						\
		return queue->tail - queue->head;									\
	}																		\
																			\
	void qu_##Type##_ptr_push(Queue_##Type##_ptr *queue, Type *elm) {				\
		queue->elms[queue->tail++ % size] = elm;							\
	}																		\
																			\
	Type *qu_##Type##_ptr_pop(Queue_##Type##_ptr *queue) {						\
		return queue->elms[queue->head++ % size];							\
	}																		\
																			\
	Type *qu_##Type##_ptr_peek(Queue_##Type##_ptr *queue) {						\
		return queue->elms[queue->head % size];								\
	}																		\
																			\
	int qu_##Type##_ptr_clear(Queue_##Type##_ptr *queue) {						\
		queue->head = 0;													\
		queue->tail = 0;													\
	}																		\


/*
 * Linked List
 * Generic, simple, fast, doubly linked list.
 * Memory is allocated for each new node and it is deleted when the node is
 * removed.
 *
 * A linked list is a connected list of nodes, so the list is variable in size.
 * Contrary to other structures, this linked list represents just one node,
 * and you can access the other nodes in the list from it and functions take
 * a node as parameter. If it is necessary, you need to make sure you have
 * a reference of the list's head and tail.
 *
 * The methods are different from the previous structures. 
 * The method push creates a node after the referenced node and returns it.
 * The method pop deletes the referenced node and returns the previous node.
 * The method insert creates a node befores the referenced node and returns it.
 * The method remove deletes the referenced node and returns the next node.
 *
 * If you are calling a function for an empty the list, then pass NULL to 
 * the node reference. The function will return the list's first node.
 * Even if a reference to a node has been deleted, do not forget to set it 
 * to NULL, otherwise, the program may crash.
 *
 * Linked lists have no random access, so you have to iterate through
 * the nodes in order to find the element you want.
 *
 * On the other hand, inserting and removing elements in any point of the 
 * list is constant complexity O(1). Therefore you may use this as efficient
 * stacks and queues unlimited in size. The downsize is that the use of 
 * dynamic memory is relatively expensive.
 *
 * The length function therefore is O(n) in complexity. Make sure to give it
 * the actual head of the list if you want the whole size, otherwise the 
 * function will calculate the length of the list from the node you give 
 * it forwards.
 *
 */
#define DEFINE_LINKED_LIST(Type)												\
	struct LList_##Type;														\
	typedef struct LList_##Type {												\
		Type elm;																\
		struct LList_##Type *next;												\
		struct LList_##Type *prev;												\
	} LList_##Type;																\
																				\
	Type ll_##Type##_length(LList_##Type *list) {								\
		int count = 0;															\
		for (; list != NULL; list = list->next) {								\
			count += 1;															\
		}																		\
		return count;															\
	}																			\
																				\
	LList_##Type *ll_##Type##_push(LList_##Type *node, Type elm) {				\
		LList_##Type *l = malloc(sizeof(LList_##Type));							\
		l->elm = elm;															\
		l->prev = NULL;															\
		l->next = NULL;															\
		if (node) {																\
			if (node->next) {													\
				node->next->prev = l;											\
			}																	\
			l->next = node->next;												\
			node->next = l;														\
		}																		\
		l->prev = node;															\
		return l;																\
	}																			\
																				\
	LList_##Type *ll_##Type##_pop(LList_##Type *node) {							\
		LList_##Type *prev = node->prev;										\
		if (node->prev) {														\
			node->prev->next = node->next;										\
		}																		\
		if (node->next) {														\
			node->next->prev = node->prev;										\
		}																		\
		free(node);																\
		return prev;															\
	}																			\
																				\
	LList_##Type *ll_##Type##_insert(LList_##Type *node, Type elm) {			\
		LList_##Type *l = malloc(sizeof(LList_##Type));							\
		l->elm = elm;															\
		l->next = NULL;															\
		l->prev = NULL;															\
		if (node) {																\
			if (node->prev) {													\
				node->prev->next = l;											\
			}																	\
			l->prev = node->prev;												\
			node->prev = l;														\
		}																		\
		l->next = node;															\
		return l;																\
	}																			\
																				\
	LList_##Type *ll_##Type##_remove(LList_##Type *node) {						\
		LList_##Type *next = node->next;										\
		if (node->prev) {														\
			node->prev->next = node->next;										\
		}																		\
		if (node->next) {														\
			node->next->prev = node->prev;										\
		}																		\
		free(node);																\
		return next;															\
	}																			\
																				\
	void ll_##Type##_clear(LList_##Type *head) {								\
		LList_##Type *next;														\
		for (LList_##Type *node = head; node != NULL; node = next) {			\
			next = node->next;													\
			free(node);															\
		}																		\
	}																			\

#define DEFINE_LINKED_LIST_PTR(Type)												\
	struct LList_##Type##_ptr;														\
	typedef struct LList_##Type##_ptr {												\
		Type *elm;																\
		struct LList_##Type##_ptr *next;												\
		struct LList_##Type##_ptr *prev;												\
	} LList_##Type##_ptr;																\
																				\
	Type ll_##Type##_ptr_length(LList_##Type##_ptr *list) {								\
		int count = 0;															\
		for (; list != NULL; list = list->next) {								\
			count += 1;															\
		}																		\
		return count;															\
	}																			\
																				\
	LList_##Type##_ptr *ll_##Type##_ptr_push(LList_##Type##_ptr *node, Type *elm) {				\
		LList_##Type##_ptr *l = malloc(sizeof(LList_##Type##_ptr));							\
		l->elm = elm;															\
		l->prev = NULL;															\
		l->next = NULL;															\
		if (node) {																\
			if (node->next) {													\
				node->next->prev = l;											\
			}																	\
			l->next = node->next;												\
			node->next = l;														\
		}																		\
		l->prev = node;															\
		return l;																\
	}																			\
																				\
	LList_##Type##_ptr *ll_##Type##_ptr_pop(LList_##Type##_ptr *node) {							\
		LList_##Type##_ptr *prev = node->prev;										\
		if (node->prev) {														\
			node->prev->next = node->next;										\
		}																		\
		if (node->next) {														\
			node->next->prev = node->prev;										\
		}																		\
		free(node);																\
		return prev;															\
	}																			\
																				\
	LList_##Type##_ptr *ll_##Type##_ptr_insert(LList_##Type##_ptr *node, Type *elm) {			\
		LList_##Type##_ptr *l = malloc(sizeof(LList_##Type##_ptr));							\
		l->elm = elm;															\
		l->next = NULL;															\
		l->prev = NULL;															\
		if (node) {																\
			if (node->prev) {													\
				node->prev->next = l;											\
			}																	\
			l->prev = node->prev;												\
			node->prev = l;														\
		}																		\
		l->next = node;															\
		return l;																\
	}																			\
																				\
	LList_##Type##_ptr *ll_##Type##_ptr_remove(LList_##Type##_ptr *node) {						\
		LList_##Type##_ptr *next = node->next;										\
		if (node->prev) {														\
			node->prev->next = node->next;										\
		}																		\
		if (node->next) {														\
			node->next->prev = node->prev;										\
		}																		\
		free(node);																\
		return next;															\
	}																			\
																				\
	void ll_##Type##_ptr_clear(LList_##Type##_ptr *head) {								\
		LList_##Type##_ptr *next;														\
		for (LList_##Type##_ptr *node = head; node != NULL; node = next) {			\
			next = node->next;													\
			free(node);															\
		}																		\
	}																			\

/*
 * Map
 */
#define DEFINE_MAP(Key, Value, KeyCompare)													\
	typedef Map_##Key##_##Value {												\
	} Map_##Key##_##Value;														\



#endif  // __LIST__H__
