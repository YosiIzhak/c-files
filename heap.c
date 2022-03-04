#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "vector.h"
#include "enum.h"
#define MAGIC_NUMBER 9421
#define LEFT_SON(i) 2*(i)+1
#define RIGHT_SON(i) 2*(i)+2
#define FATHER(i) (i-1)/2

static void BubbleUp (Heap* _heap);
static void Heapify(Heap* _heap, int _index);
struct Heap
{
Vector* m_vec;
size_t  m_heapSize;
size_t  m_magicNumber;
};



Heap* HeapBuild(Vector* _vec)
{
	Heap* heap;
	size_t numOfItems;
	int i, lastFather;
	if (_vec == NULL) 
	{
        	return NULL;
   	}
	heap = (Heap*) malloc (sizeof(Heap));
	if (heap == NULL) 
	{
        	return NULL;
   	}
	
	heap->m_vec = _vec;
	heap->m_heapSize = VectorItemsNum(_vec, &numOfItems);
	heap->m_magicNumber = MAGIC_NUMBER;
	lastFather = FATHER(heap->m_heapSize);
	
	for (i = lastFather; i >= 0; i--) 
	{
        	Heapify(heap, i);
    	}
    	return heap;
}

void HeapDestroy(Heap* _heap)
{
	if(_heap == NULL || _heap ->m_magicNumber != MAGIC_NUMBER)
	{
		return;
	}
	_heap ->  m_magicNumber = 0;
	free(_heap);
	return;
}
ADTErr  HeapMax(Heap* _heap, int* _data)
{
	if (_heap == NULL) 
	{
        	return ERR_NOT_INITIALIZED;
   	}
	VectorGet(_heap->m_vec, 0, _data);	
		return ERR_OK;
}
ADTErr HeapExtractMax (Heap* _heap, int* _data)
{
	int last;
	if(_heap == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}

	VectorGet(_heap -> m_vec ,0, _data);
	VectorGet(_heap -> m_vec ,_heap -> m_heapSize - 1, &last);
	VectorSet(_heap -> m_vec, 0, last);
	VectorDelete(_heap -> m_vec,  &last);
	_heap -> m_heapSize--;
	Heapify(_heap, 0);

return ERR_OK;	
}

ADTErr HeapInsert(Heap* _heap, int _data)
{
	ADTErr bubbleUpErr;
	VectorAdd(_heap->m_vec, _data);
       _heap->m_heapSize++;
        BubbleUp(_heap);
}	

int HeapItemsNum(Heap* _heap)
{
	if (_heap == NULL) 
	{
        	return -1;
   	}
	return _heap->m_heapSize;
}

void HeapPrint(Heap* _heap)
{
	VectorPrint(_heap->m_vec);
}
static void Heapify(Heap* _heap, int _index)
{
        int curr_data = VectorGet(_heap->m_vec, _index, &curr_data);
	int l_data = VectorGet(_heap->m_vec, LEFT_SON(_index), &l_data);
	int r_data = VectorGet(_heap->m_vec, RIGHT_SON(_index), &r_data);
        int largest = VectorGet(_heap->m_vec, largest, &largest);
        int temp; 
        largest = _index; 
   
    if (l_data > curr_data)
    {
    		largest = l_data;
    }
     if (r_data > curr_data)
     {
       	 largest = r_data;
     }
     if (largest != _index) 
     {
        temp = curr_data;
        curr_data = largest;
        largest = temp;
        Heapify(_heap, largest);
     }
}
static void BubbleUp (Heap* _heap)
{
int New;
int Father;
int iNew = 0;
int iFather = 0;

	iNew = _heap -> m_heapSize -1;
	iFather = FATHER(iNew);
	
	VectorGet(_heap -> m_vec, iNew, &New);
	VectorGet(_heap -> m_vec,iFather, &Father);
	
	while( New > Father && iNew > 0)
	{
		VectorSet(_heap -> m_vec, iNew, Father);
		VectorSet(_heap -> m_vec, iFather, New);

		iNew = 	iFather;
		iFather = FATHER(iNew);
		
		VectorGet(_heap -> m_vec, iNew, &New);
	        VectorGet(_heap -> m_vec, iFather, &Father);
	}	
}
	
/*#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "heap.h"
#include "enum.h"
#define MAGIC_NUMBER 8123475
#define FATHER(i) ((i)-1)/2
#define RIGHT_CHILD(i) (i)*2 + 2
#define LEFT_CHILD(i) (i)*2 + 1

/****Auxiliary functions******

void bubbleUp (Heap* _heap);
void Heapify(Heap* _heap, int _index);


/*struct Heap*

struct Heap
{
Vector* m_vec;
size_t m_heapSize;
int m_magicNumber;
};

/*****HeapBuild*****

Heap* HeapBuild(Vector* _vec)
{
Heap* heapPtr;
size_t numOfltems;
int i;

	if(_vec == NULL)
	{
		return NULL;
	}
	
	if((heapPtr = ((Heap*)malloc(sizeof(Heap)))) == NULL)
	{
		return NULL;
	}
	
	VectorItemsNum (_vec, &numOfltems);
	heapPtr -> m_vec = _vec;
	heapPtr -> m_heapSize = numOfltems;
	heapPtr -> m_magicNumber = MAGIC_NUMBER;
	
	for(i = FATHER(heapPtr -> m_heapSize - 1); i >= 0; i--)
	{
		Heapify(heapPtr,i);
	}
	
return heapPtr;
}


/****HeapDestroy******

void HeapDestroy(Heap* _heap)
{
	if(_heap == NULL || _heap ->  m_magicNumber != MAGIC_NUMBER)
	{
		return;
	}
	
	_heap ->  m_magicNumber = 0;
	free(_heap);
}

/*******HeapInsert********

ADTErr HeapInsert(Heap* _heap, int _data)
{
ADTErr addErr;
ADTErr bubbleUpErr;

	if(_heap == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	addErr = VectorAdd (_heap -> m_vec , _data);
	if( addErr != ERR_OK)
	{
		return addErr;
	}
	
	bubbleUp(_heap);
	_heap -> m_heapSize++;
	
return ERR_OK;
}

void bubbleUp (Heap* _heap)
{
int New;
int Father;
int iNew = 0;
int iFather = 0;

	iNew = _heap -> m_heapSize -1;
	iFather = FATHER(iNew);
	
	VectorGet(_heap -> m_vec, iNew, &New);
	VectorGet(_heap -> m_vec,iFather, &Father);
	
	while( New > Father && iNew > 0)
	{
		VectorSet(_heap -> m_vec, iNew, Father);
		VectorSet(_heap -> m_vec, iFather, New);

		iNew = 	iFather;
		iFather = FATHER(iNew);
		
		VectorGet(_heap -> m_vec, iNew, &New);
	        VectorGet(_heap -> m_vec, iFather, &Father);
	}	
}


/*******HeapMax********

ADTErr HeapMax (Heap* _heap, int* _data)
{
	if(_heap == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}

	VectorGet(_heap -> m_vec ,0, _data);
	
return ERR_OK;
}

ADTErr HeapHxtractMax (Heap* _heap, int* _data)
{
int last;

	if(_heap == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}

	VectorGet(_heap -> m_vec ,0, _data);
	VectorDelete(_heap -> m_vec,  &last);
	VectorSet(_heap -> m_vec, 0, last);
	_heap -> m_heapSize--;
	Heapify(_heap, 0);

return ERR_OK;	
}


void Heapify(Heap* _heap, int _index)
{
int Father;
int Bigest;
int iBigest;
int iFather;
int iLeftChild;

	iFather = _index;
	iLeftChild = LEFT_CHILD( _index);
	
	if(iLeftChild >  _heap -> m_heapSize - 1)
	{
		return;
	}
	
	iBigest = CheckBigest( _heap, _index);
	
	VectorGet(_heap -> m_vec ,iBigest, &Bigest);
	VectorGet(_heap -> m_vec ,iFather, &Father);
			
	if(iBigest != _index)
	{
		VectorSet(_heap -> m_vec , iBigest, Father);
		VectorSet(_heap -> m_vec , iFather, Bigest);	
		Heapify(_heap, iBigest);	
	}
}

int CheckBigest(Heap* _heap, int _index)
{
int Father;
int LeftChild;
int RightChild;
int iFather;
int iLeftChild;
int iRightChild;
int flag = 0;

	iFather = _index;
	iLeftChild = LEFT_CHILD( _index);
	iRightChild = RIGHT_CHILD( _index);

	VectorGet(_heap -> m_vec ,iFather, &Father);
	VectorGet(_heap -> m_vec ,iLeftChild, &LeftChild);		
	if(VectorGet(_heap -> m_vec  ,iRightChild, &RightChild) == ERR_WRONG_INDEX)
	{
		flag = 1;
	}
	
	if (flag == 0)
	{
		if(Father >= LeftChild && Father >= RightChild)
		{
			return iFather;
		}
		else if ( LeftChild >= RightChild)
		{
			return iLeftChild;
		}
		else
		{
			return iRightChild;
		}
	}
	
	if(Father >= LeftChild)
	{
		return iFather;
	}
	else 
	{
		return iLeftChild;
	}
}


/****test function***

getHeapSize(Heap* Heap)
{
	return Heap -> m_heapSize;
}

getMagicNumber(Heap* Heap)
{
	return Heap -> m_magicNumber;
}	
	
	*/
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	


