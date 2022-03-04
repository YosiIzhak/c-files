#include <stdio.h>
#include <stdlib.h>
#include "genvector.h"

int VectorPrint(const Vector* _vector, int _index);
int main()
{
	int index, arr[] = {1,2,3,4,5};
	Vector *ptr;
	ptr = VectorCreate(10, 3);
	VectorAppend(ptr, &arr[0]);
	VectorAppend(ptr, &arr[1]);
	VectorAppend(ptr, &arr[2]);
	VectorAppend(ptr, &arr[3]);
	VectorAppend(ptr, &arr[4]);
	VectorForEach(ptr, VectorPrint, NULL);
	VectorDestroy(&ptr, NULL);
}
