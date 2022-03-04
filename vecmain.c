#include <stdio.h>
#include <stdlib.h>
#include "genvec.h"

int VectorPrint(void* _element, size_t _index, void* _context)
{
	
	printf("%d, ", (*(int*)_element));
	return 1;
}
int VectorFind(void* _element, size_t _index, void* _context)
{
	if((*(int*)_element) == (*(int*)_context))
	{
		return 0;
	}
	return 1;
}
int	FindMax(void *_element, size_t _index, void *_context)
{
	if((*(int*)_element) > (*(int*)_context))
	{
		(*(int*)_context) = (*(int*)_element);
	}
	return 1;
}
int main()
{
	int max = 0, found, context = 2, arr[] = {1,2,3,4,5};
	Vector *ptr;
	ptr = VectorCreate(10, 3);
	VectorAppend(ptr, &arr[0]);
	VectorAppend(ptr, &arr[1]);
	VectorAppend(ptr, &arr[2]);
	VectorAppend(ptr, &arr[3]);
	VectorAppend(ptr, &arr[4]);
	VectorForEach(ptr, VectorPrint, 0);
	found = VectorForEach(ptr, VectorFind, &context);
	printf("found: %d\n", found);
	VectorForEach(ptr, FindMax, &max);
	printf("Max value: %d\n", max);
	VectorDestroy(&ptr, NULL);
}
