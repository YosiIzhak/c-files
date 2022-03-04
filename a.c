#include <stdio.h>
#include <stdlib.h>
#include "genq.h"

int QueuePrint(const void* _element, void* _context)
{
	printf("%d, ", (*(int*)_element));
    return 1;	   	
}
int QueueFind(const void* _element, void* _context)
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
	Queue *ptr;
	int max = 0, found, context = 24, arr[] = {1,122,23,4,15};
	ptr = QueueCreate(10);
	QueueInsert(ptr,&arr[4]);
	QueueInsert(ptr,&arr[3]);
	QueueInsert(ptr,&arr[1]);
	QueueInsert(ptr,&arr[2]);
	QueueInsert(ptr,&arr[0]);
	QueueForEach(ptr, QueuePrint, 0);
	found = QueueForEach(ptr, QueueFind, &context);
	printf("found: %d\n", found);
	QueueForEach(ptr, FindMax, &max);
	printf("Max value: %d\n", max);
	QueueDestroy(&ptr, NULL);
}
