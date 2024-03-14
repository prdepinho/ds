#ifndef __ALIST_H__
#define __ALIST_H__

enum DataStructErrors {
	DS_OK = 0,
	DS_OVERFLOW,
	DS_EMPTY,
	DS_OUT_OF_BOUNDS,
	DS_MALLOC_ERROR
};

typedef struct AList {
	unsigned char *array;
	unsigned long max_length;
	unsigned long data_size;
	unsigned long length;
} AList;

// return <0 if a<b; 0 if a==b; >0 if a>b
typedef int (*DSCompare) (const void *a, const void *b);


AList *alist_new(unsigned long max_length, unsigned long data_size);
void alist_delete(AList *list);

int alist_resize(AList *list, unsigned long length, const void *filler);

int alist_push(AList *alist, const void *data);
int alist_pop(AList *alist, void *out_data);

int alist_set(AList *list, unsigned long index, const void *data);
int alist_get(AList *list, unsigned long index, void *out_data);

int alist_add(AList *list, unsigned long index, const void *data);
int alist_remove(AList *list, unsigned long index);

void alist_clear(AList *list);

int alist_sort(AList *list, DSCompare compare);


#endif  // __ALIST_H__
