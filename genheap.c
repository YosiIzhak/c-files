#include<stdio.h>
#include<stdlib.h>
#include "genheap.h"
#define FATHER(i) (i-1)/2
#define LEFT_SON(i) (i*2)+1
#define RIGHT_SON(i) (i*2)+2

struct Heap{

	Vector *m_vec;
	size_t m_heapSize;
	Comparator m_lessThan;	
};

/*################### internal functions #############################*/
void Heapify(Heap* _heap, size_t _indx);
static int GetBiggest(Heap* _heap, size_t _indx);
static void swap(Heap* _heap, size_t _indx, size_t _big);
static int IsLeaf(Heap* _heap, size_t _indx);
static void BubbleUp(Heap *_heap, void *_element);
/*#####################################################################*/

Heap* HeapBuild(Vector *_vector, Comparator _pIfLess)
{
   	Heap *pHeap;
   	size_t i;
   	if(_vector == NULL || _pIfLess == NULL)
   	{
   		return NULL;
   	}
   	pHeap = (Heap*)malloc(sizeof(Heap));
   	if(pHeap == NULL)
   	{	
   		return NULL;
   	}
   	pHeap->m_vec = _vector;
   	pHeap->m_heapSize = VectorSize(_vector);
 	pHeap->m_lessThan = _pIfLess;
 
   	i = FATHER(pHeap->m_heapSize - 1);
   	while(i >= 0)
   	{
   		Heapify(pHeap, i);
	    if(i == 0){ 
   			break;
	    }
   		i--;		
   	}   	
	return pHeap;
}
/***********************************************************************/

Vector* HeapDestroy(Heap **_heap)
{
	Vector *pVec;
	if(_heap == NULL || *_heap == NULL){
		return NULL;  
	}
	pVec = (*_heap)->m_vec;
	free(*_heap);
	*_heap = NULL;
	return pVec;
}
/***********************************************************************/

HeapResultCode HeapInsert(Heap *_heap, void *_element)
{
	VectorResult eror;
	if(_heap == NULL || _element == NULL)
	{
		return HEAP_NOT_INITIALIZED;
	}
	eror = VectorAppend(_heap->m_vec, _element);
	if(eror != VECTOR_SUCCESS)
	{		
		return HEAP_APPEND_FAILED;
	}
	_heap->m_heapSize++;
	BubbleUp(_heap, _element);

	return HEAP_SUCCESS;
}
/***********************************************************************/

const void* HeapPeak(const Heap *_heap)              
{
	void *item;
	if(_heap == NULL|| _heap->m_heapSize == 0){
		return NULL;
	}
	VectorGet(_heap->m_vec, 0, &item);
	return item;                       
}
/***********************************************************************/

void* HeapExtract(Heap *_heap) 
{
	void *last, *item;
	if(_heap == NULL || _heap->m_heapSize == 0){
		return NULL;
	}

	VectorGet(_heap->m_vec, 0, &item);
	VectorRemove(_heap->m_vec, &last);
	_heap->m_heapSize--;
	if(_heap->m_heapSize > 0)
	{
		VectorSet(_heap->m_vec, 0, last);
		Heapify(_heap, 0); 
	}     
	return item;             
}
/***********************************************************************/

size_t HeapSize(const Heap* _heap)
{
	if(_heap == NULL){
		return 0;
	}
	return _heap->m_heapSize;
}
/***********************************************************************/

size_t HeapForEach(const Heap *_heap, ActionFunction _action, void *_context)
{
	size_t i;
	void *item;
	if(_heap == NULL || _action == NULL)
	{
		return 0;             /*include this in file.h*/
	}
	for(i = 0; i < _heap->m_heapSize; i++){
		VectorGet(_heap->m_vec, i, &item);
        if(_action(item, _context) == 0)
        {
        	break;	
        }			
  	}
	return i;
}
/***********************************************************************/

void HeapSort(Vector *_vec, Comparator _pIfLess)
{
	size_t i;
	Heap *pHeap;
	if(_vec == NULL)
	{
		return;
	}
	pHeap = HeapBuild(_vec, _pIfLess);
	for(i = 0; i < pHeap->m_heapSize; i++)
	{
		swap(pHeap, 0,  pHeap->m_heapSize-1);
		pHeap->m_heapSize--;
		Heapify(pHeap, 0);
	}
	HeapDestroy(&pHeap);
}
 
 
/*####################################################################*/
/*################### internal functions #############################*/

void Heapify(Heap* _heap, size_t _indx)
{
	size_t bigIndx;
	if(IsLeaf(_heap, _indx) == 1){
		return;
	}
	bigIndx = GetBiggest(_heap, _indx);
	if(bigIndx != _indx){
		swap(_heap, _indx ,bigIndx);
		Heapify(_heap, bigIndx);
	}
}
/*---------------------------------------------------------------------*/
static int IsLeaf(Heap* _heap, size_t _indx)
{	
	if(LEFT_SON(_indx) < _heap->m_heapSize)
	{
		return 0;
	}
	return 1;
}
/*---------------------------------------------------------------------*/
static int GetBiggest(Heap* _heap, size_t _indx)
{
	void *left, *right, *father, *bigValue;
	size_t bigIndx;
	VectorGet(_heap->m_vec, _indx, &father);
	VectorGet(_heap->m_vec, LEFT_SON(_indx), &left);
	bigValue = father;
	bigIndx = _indx;
		
	if(RIGHT_SON(_indx) < _heap->m_heapSize){    /*if right isn't NULL*/
		VectorGet(_heap->m_vec, RIGHT_SON(_indx), &right);	
		
		bigValue = (_heap->m_lessThan(right, father)) ? father : right;		
		bigIndx = (_heap->m_lessThan(right, father)) ? _indx : RIGHT_SON(_indx);
	}		
	bigIndx = (_heap->m_lessThan(left, bigValue)) ? bigIndx : LEFT_SON(_indx);
	return bigIndx;
}
/*---------------------------------------------------------------------*/
static void swap(Heap* _heap, size_t _indx, size_t _big)
{
	void *father, *son;
		
	VectorGet(_heap->m_vec, _big, &father);
	VectorGet(_heap->m_vec, _indx, &son);
	VectorSet(_heap->m_vec, _indx, father); 
	VectorSet(_heap->m_vec, _big, son); 
}
/*---------------------------------------------------------------------*/
static void BubbleUp(Heap *_heap, void *_element)
{ 
	void *father, *son = _element;
	size_t i = _heap->m_heapSize - 1;
	VectorGet(_heap->m_vec, FATHER(i), &father);
		
	while(i > 0 && _heap->m_lessThan(father, son)){ 
	 	VectorSet(_heap->m_vec, i, father);
	 	VectorSet(_heap->m_vec, FATHER(i), son);
		i = FATHER(i);
		VectorGet(_heap->m_vec, FATHER(i), &father);		
	}
}


















