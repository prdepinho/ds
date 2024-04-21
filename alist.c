#include "alist.h"
#include <stdlib.h>
#include <string.h>


AList *alist_new(unsigned long max_length, unsigned long data_size) {
	AList *list;
	list = malloc(sizeof(AList));
	if (!list) {
		return NULL;
	}
	list->max_length = max_length;
	list->data_size = data_size;
	list->length = 0L;
	list->array = malloc((max_length + 1) * data_size);  // the last element is the temporary element used for sorting
	if (!list->array) {
		free(list);
		return NULL;
	}
	return list;
}

void alist_delete(AList *list) {
	if (list) {
		free(list->array);
		free(list);
	}
}

int alist_resize(AList *list, unsigned long length, const void *filler) {
	if (length >= list->max_length) {
		return DS_OVERFLOW;
	}
	for (; list->length < length; list->length++) {
		memcpy(list->array + list->length * list->data_size, filler, list->data_size);
	}
	list->length = length;
	return DS_OK;
}

int alist_push(AList *list, const void *data) {
	if (list->length == list->max_length) {
		return DS_OVERFLOW;
	}
	memcpy(list->array + list->length * list->data_size, data, list->data_size);
	list->length++;
	return DS_OK;
}

int alist_pop(AList *list, void *out_data) {
	if (list->length == 0) {
		return DS_EMPTY;
	}
	list->length--;
	memcpy(out_data, list->array + list->length * list->data_size, list->data_size);
	return DS_OK;
}

int alist_set(AList *list, unsigned long index, const void *data) {
	if (index >= list->length) {
		return DS_OUT_OF_BOUNDS;
	}
	memcpy(list->array + index * list->data_size, data, list->data_size);
	return DS_OK;
}

int alist_get(AList *list, unsigned long index, void *out_data) {
	if (index >= list->length) {
		return DS_OUT_OF_BOUNDS;
	}
	memcpy(out_data, list->array + index * list->data_size, list->data_size);
	return DS_OK;
}

int alist_add(AList *list, unsigned long index, const void *data) {
	if (index > list->length) {
		return DS_OUT_OF_BOUNDS;
	}
	if (list->length == list->max_length) {
		return DS_OVERFLOW;
	}
	for (unsigned long i = list->length; i > index; i--) {
		memcpy(list->array + i * list->data_size,
			   list->array + (i-1) * list->data_size,
			   list->data_size);
	}
	memcpy(list->array + index * list->data_size, data, list->data_size);
	list->length++;
	return DS_OK;
}

int alist_remove(AList *list, unsigned long index) {
	if (index >= list->length) {
		return DS_OUT_OF_BOUNDS;
	}
	if (list->length == 0) {
		return DS_EMPTY;
	}
	for (; index < list->length; index++) {
		memcpy(list->array + index * list->data_size,
			   list->array + (index+1) * list->data_size,
			   list->data_size);
	}
	list->length--;
	return DS_OK;
}

void alist_clear(AList *list) {
	list->length = 0;
}


int alist_sort(AList *list, DSCompare compare) {
	unsigned char *tmp = list->array + list->max_length * list->data_size;
	ds_quick_sort(list->array, list->length, list->data_size, tmp, compare);
	return DS_OK;
}

