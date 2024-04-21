
#include "commons.h"
#include <stdlib.h>
#include <string.h>

static void swap(
		unsigned char *array,
	   	unsigned long data_size,
		unsigned char *tmp,
	   	unsigned long a,
	   	unsigned long b);

static void swap(
		unsigned char *array,
	   	unsigned long data_size,
		unsigned char *tmp,
	   	unsigned long a,
	   	unsigned long b)
{
	memcpy(tmp, array + a * data_size, data_size);
	memcpy(array + a * data_size, array + b * data_size, data_size);
	memcpy(array + b * data_size, tmp, data_size);
}

void ds_quick_sort(
		unsigned char *array,
	   	unsigned long length,
	   	unsigned long data_size,
		unsigned char *tmp,
	   	DSCompare compare)
{
	unsigned long p, i, j;
	if (length <= 1) {
		return;
	}
	p = length / 2;
	j = 1;
	swap(array, data_size, tmp, 0, p);
	for (i = 1; i < length; i++) {
		if (compare(array + i * data_size, array) <= 0) {
			swap(array, data_size, tmp, i, j);
			j++;
		}
	}
	swap(array, data_size, tmp, 0, j-1);
	ds_quick_sort(array,					  j-1,			data_size, tmp, compare);
	ds_quick_sort(array + (j-1) * data_size, length - j+1, data_size, tmp, compare);
}

