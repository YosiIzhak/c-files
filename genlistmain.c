#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genlist.h"

void ElementDestroy(Node* _ptr)
{
	if (_ptr == NULL)
	{
		return;
	}
	free(_ptr);
	_ptr = NULL;
}

void PrintDoubleList()
{
	List* dList;
	dList = ListCreate();
	
	
	
	ListDestroy(dList);
}
int main()
{

PrintDoubleList();


}
