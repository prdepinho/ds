
#include "alist.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

typedef struct Coords {
	int x;
	int y;
	int z;
} Coords;

int compare_coords(const Coords *a, const Coords *b) {
	return (a->x + a->y + a->z) - (b->x + b->y + b->z);
}

int compare_ints(const int *a, const int *b) {
	return *a - *b;
}

int main() {
	AList *list;
	unsigned long max = 10;

	list = alist_new(max, sizeof(Coords));
	assert(list);
	assert(list->length == 0);


	// push
	{
		Coords coords = { 1, 2, 3 };
		int rval = alist_push(list, &coords);
		assert(rval == DS_OK);
		assert(list->length == 1);
	}

	// get
	{
		Coords coords = { 0, 0, 0 };
		int rval = alist_get(list, 0L, &coords);
		assert(rval == DS_OK);
		assert(coords.x == 1);
		assert(coords.y == 2);
		assert(coords.z == 3);
	}
	{
		Coords coords = { 0, 0, 0 };
		int rval = alist_get(list, 2L, &coords);
		assert(rval == DS_OUT_OF_BOUNDS);
	}

	// set
	{
		Coords coords = { 9, 7, 5 };
		int rval = alist_set(list, 0L, &coords);
		assert(rval == DS_OK);
	}
	{
		Coords coords = { 0, 0, 0 };
		int rval = alist_get(list, 0L, &coords);
		assert(rval == DS_OK);
		assert(coords.x == 9);
		assert(coords.y == 7);
		assert(coords.z == 5);
	}
	{
		Coords coords = { 9, 7, 5 };
		int rval = alist_set(list, 2L, &coords);
		assert(rval == DS_OUT_OF_BOUNDS);
	}
	{
		Coords coords = { 5, 5, 5 };
		int rval = alist_set(list, list->length, &coords);
		assert(rval == DS_OUT_OF_BOUNDS);
	}


	// pop
	{
		Coords coords = { 0, 0, 0 };
		int rval = alist_pop(list, &coords);
		assert(rval == DS_OK);
		assert(list->length == 0);
		assert(coords.x == 9);
		assert(coords.y == 7);
		assert(coords.z == 5);
	}

	// push && pop safety
	{
		for (unsigned long i = 0; i < max; i++) {
			Coords coords = { i, i, i };
			int rval = alist_push(list, &coords);
			assert(rval == DS_OK);
			assert(list->length == i + 1);
		}

		{
			Coords coords = { 99, 99, 99 };
			int rval = alist_push(list, &coords);
			assert(rval == DS_OVERFLOW);
			assert(list->length == max);
		}

		for (long i = max - 1; i >= 0; i--) {
			Coords coords = { 0, 0, 0 };
			int rval = alist_pop(list, &coords);
			assert(rval == DS_OK);
			assert(list->length == (unsigned long) i);
			assert(coords.x == (unsigned long) i);
			assert(coords.y == (unsigned long) i);
			assert(coords.z == (unsigned long) i);
		}

		assert(list->length == 0);

		{
			Coords coords = { 0, 0, 0 };
			int rval = alist_pop(list, &coords);
			assert(rval == DS_EMPTY);
			assert(list->length == 0);
		}

		
	}

	// resize
	{
		Coords coords = { 7, 7, 7 };
		int rval = alist_push(list, &coords);
		assert(rval == DS_OK);
		assert(list->length == 1);
	}
	{
		Coords filler = { 1, 1, 1 };
		int rval = alist_resize(list, 5L, &filler);
		assert(rval == DS_OK);
		assert(list->length == 5);

		{
			Coords coords = { 0, 0, 0 };
			int rval = alist_get(list, 0L, &coords);
			assert(rval == DS_OK);
			assert(coords.x == 7);
			assert(coords.y == 7);
			assert(coords.z == 7);
		}
		for (unsigned long i = 1; i < 5L; i++) {
			Coords coords;
			int rval = alist_get(list, i, &coords);
			assert(rval == DS_OK);
			assert(coords.x == filler.x);
			assert(coords.y == filler.y);
			assert(coords.z == filler.z);
		}
	}
	{
		Coords filler = { 1, 1, 1 };
		int rval = alist_resize(list, 2L, &filler);
		assert(rval == DS_OK);
		assert(list->length == 2);
	}
	{
		Coords filler = { 0, 0, 0 };
		int rval = alist_resize(list, 30L, &filler);
		assert(rval == DS_OVERFLOW);
		assert(list->length == 2);
	}

	// clear
	{
		alist_clear(list);
		assert(list->length == 0);
	}

	// tmp
	{
		unsigned long max_length = 5;
		AList *list = alist_new(max_length, sizeof(int));
		unsigned char *tmp = list->array + list->max_length * list->data_size;
		int tmpi = 77;
		memcpy(tmp, &tmpi, sizeof(int));

		for (unsigned long i = 0; i < max_length; i++) {
			int n = (int) i;
			alist_push(list, &n);
		}

		for (unsigned long i = 0; i < max_length; i++) {
			int n;
			alist_get(list, i, &n);
			assert(n == (int)i);
		}
		{
			int n = 10;
			int rval = alist_push(list, &n);
			assert(rval == DS_OVERFLOW);
		}
		assert((int)*tmp == tmpi);
	}

	// sort
	{
		srand(time(NULL));
		for (unsigned long i = 0; i < list->max_length; i++) {
			int n = rand() % 10;
			Coords coords = { n, 0, 0 };
			alist_push(list, &coords);
		}
		assert(list->length == 10);

		int rval = alist_sort(list, (DSCompare) compare_coords);
		assert(rval == DS_OK);

		Coords pcoords = { 0, 0, 0 };
		Coords ncoords;
		int n;
		for (unsigned long i = 0; i < list->length; i++) {
			int rval = alist_get(list, i, &ncoords);
			assert(rval == DS_OK);
			assert(pcoords.x <= pcoords.x);
		}
	}

	// sort
	{
		srand(time(NULL));
		const unsigned long max_size = 100;
		for (int i = 0; i < 100; i++) {
			AList *list = alist_new(max_size, sizeof(int));
			int its = rand() % max_size;
			for (int j = 0; j < its; j++) {
				int n = rand() % max_size;
				alist_push(list, &n);
			}

			alist_sort(list, (DSCompare) compare_ints);

			int p = 0;
			int n;
			int rval;
			for (unsigned long j = 0; j < list->length; j++) {
				rval = alist_get(list, j, &n);
				assert(rval == DS_OK);
				assert(n >= p);
				if (n > p) {
					p = n;
				}
			}

		}
	}

	// add, remove
	{
		AList *list = alist_new(10, sizeof(int));
		for (unsigned int i = 0; i < 10; i++) {
			int n = (int)i;
			alist_push(list, &n);
		}
		assert(list->length == 10);
		{
			int rval = alist_remove(list, 10);
			assert(rval == DS_OUT_OF_BOUNDS);
		}
		{
			int rval = alist_remove(list, 9);
			assert(rval == DS_OK);
			assert(list->length == 9);
		}
		{
			int n;
			int rval = alist_get(list, 9, &n);
			assert(rval == DS_OUT_OF_BOUNDS);
		}
		{
			int n;
			alist_get(list, 5, &n);
			assert(n == 5);
		}
		{
			int rval = alist_remove(list, 5);
			assert(rval == DS_OK);
			assert(list->length == 8);
		}
		{
			int n;
			alist_get(list, 5, &n);
			assert(n == 6);
		}
		{
			int n = 77;
			int rval = alist_add(list, 2, &n);
			assert(rval == DS_OK);
			assert(list->length == 9);
		}
		{
			int n;
			int rval = alist_get(list, 2, &n);
			assert(rval == DS_OK);
			assert(n == 77);
		}
		{
			int n = 55;
			int rval = alist_add(list, 9, &n);
			assert(rval == DS_OK);
			assert(list->length == 10);
		}
		{
			int n = 66;
			int rval = alist_add(list, 10, &n);
			assert(rval == DS_OVERFLOW);
		}
		{
			int n = 77;
			int r;
			alist_set(list, 8, &n);
			alist_get(list, 8, &r);
			assert(r == n);
		}
		{
			int n;
			alist_get(list, 1, &n);
			assert(n == 1);
			alist_get(list, 2, &n);
			assert(n == 77);
			alist_get(list, 3, &n);
			assert(n == 2);
			alist_get(list, 4, &n);
			assert(n == 3);
		}
	}

	alist_delete(list);
}
