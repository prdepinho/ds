
#ifndef __COMMONS_H__
#define __COMMONS_H__

// return <0 if a<b; 0 if a==b; >0 if a>b
typedef int (*DSCompare) (const void *a, const void *b);

void ds_quick_sort(
		unsigned char *array,
	   	unsigned long length,
	   	unsigned long data_size,
		unsigned char *tmp,
		DSCompare compare);


#endif  // __COMMONS_H__
