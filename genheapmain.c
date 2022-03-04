#include <stdio.h>
#include <stdlib.h>
#include "genheap.h"
#include "genvec.h"
int ToChangeMax(const void* item1, const void* item2)
{
	if (*(int*)item2 > *(int*)item1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int ToChangeMin(const void* item1, const void* item2)
{
	if (*(int*)item2 < *(int*)item1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int HeapPrint(const void* _element, void* _context)
{
	printf("%d, ", (*(int*)_element));
    return 1;	   	
}
int HeapFind(const void* _element, void* _context)
{
	if((*(int*)_element) == (*(int*)_context))
	{
		return 0;
	}
	return 1;
}
int	FindMax(const void *_element, void *_context)
{
	if((*(int*)_element) > (*(int*)_context))
	{
		(*(int*)_context) = (*(int*)_element);
	}
	return 1;
}
int main()
{
	Heap *ptr;
	Vector *vec = NULL;
	int max = 0, found, context = 24, arr[] = {1,122,23,4,15};
	vec = VectorCreate(10, 5);
	ptr = HeapBuild(vec, ToChangeMax);
	HeapInsert(ptr,&arr[4]);
	HeapInsert(ptr,&arr[3]);
	HeapInsert(ptr,&arr[1]);
	HeapInsert(ptr,&arr[2]);
	HeapInsert(ptr,&arr[0]);
	HeapForEach(ptr, HeapPrint, 0);
	found = HeapForEach(ptr, HeapFind, &context);
	printf("found: %d\n", found);
	HeapForEach(ptr, FindMax, &max);
	printf("Max value: %d\n", max);
	HeapDestroy(&ptr);
}
