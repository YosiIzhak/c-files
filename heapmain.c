#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "vector.h"
#include "enum.h"

void CheckHeap()
{
	Heap* Heap;
	Vector* ptr;
	HeapBuild(ptr);
	HeapInsert(Heap, 10);
	HeapInsert(Heap, 4);
	HeapInsert(Heap, 6);
	HeapInsert(Heap, 2);
	HeapInsert(Heap, 7);
	HeapInsert(Heap, 12);
	
}
int main()
{

CheckHeap();


}
