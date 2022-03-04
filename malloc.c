#include<stdio.h>
#include<stdlib.h>
#include "malloc.h"

void MyMallocInit(void* _memory, size_t _memorySize)
{
	long* ptr = (long*)_memory;
	size_t available = _memorySize;
	*ptr = _memorySize;
	ptr++;
	*ptr = _memorySize - 24;
	ptr += _memorySize/ 8 - 2;
	*ptr = 0;
	available = _memorySize - 24;
	ptr = _memory;
	ptr++;
}
void* MyMalloc(void* _memory, size_t _requiredBlockSize)
{
	char flag = 0;
	long res, available, value;
	long* ptr = (long*)_memory;
	long* newPtr;
	ptr++;
	while (flag == 0 && *ptr!= 0)
	{
		flag = 0;
		res = *ptr & (1 << 63); 
		if (*ptr < 0)
		{
			value = (*ptr) * -1;
		}
		else
		{
			value = *ptr;
		}
		if (res == 0 && *ptr > _requiredBlockSize)
		{
			flag = 1;
			available = *ptr;
			*ptr = _requiredBlockSize;
			newPtr = ptr;
			ptr += _requiredBlockSize/8;
			*ptr = available - _requiredBlockSize;
			return newPtr;
		}
		else
		{
			ptr += value/8;
		}
	}
	if (*ptr == 0)
	{
		return;
	}
	
}
void MyFree(void* _myBlock)
{
	long* ptr = (long*)_myBlock;
	if (*ptr < 0)
	{
		(*ptr) = (*ptr) * -1;
	}
}
int main()
{
	char* ptr;
	char* ptr1;
	ptr = (char*) malloc (1000 * sizeof(char));
	MyMallocInit((void*)ptr, 1000);
	ptr1 = MyMalloc((void*)ptr, 40);
	MyFree((void*) ptr1);

}
