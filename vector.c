#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

#define MAGIC_NUMBER 9421
struct Vector
{
    int*    m_items;
    size_t  m_originalSize; /* original allocated space for items)*/	
    size_t  m_size;      /* actual allocated space for items)*/
    size_t  m_nItems;     	    /* actual number of items */
    size_t  m_blockSize;/*the chunk size to be allocated when no space*/
    size_t  m_magicNumber;
};

Vector* VectorCreate(size_t _initialSize, size_t _extensionBblockSize)
{
	Vector *ptr;
	if (_initialSize == 0 && _extensionBblockSize == 0)
	{
		return NULL;
	}
	
	ptr = (Vector*) malloc (sizeof(Vector));
	if (ptr == NULL) 
	{
        	printf("Memory not allocated.\n");
       	return NULL;
   	}
	ptr->m_items = (int*) malloc(_initialSize * sizeof(int));
	if (ptr->m_items == NULL) 
	{
        	printf("Memory not allocated.\n");
       	return NULL;
   	}
  	ptr->m_originalSize = _initialSize;
  	ptr->m_nItems = 0;
  	ptr->m_blockSize = _extensionBblockSize;
  	ptr->m_magicNumber = MAGIC_NUMBER;
  	ptr->m_size = _initialSize;
  	return ptr;
}

void VectorDestroy (Vector* _vector)
{
	if(_vector == NULL || _vector-> m_magicNumber != MAGIC_NUMBER)
	{
		return;
	}
	_vector-> m_magicNumber = 0;
	free (_vector -> m_items);
	free(_vector);
	return;
}

ADTErr VectorAdd (Vector *_vector, int  _item)
{
	int *temp;
	if(_vector == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}

	if((_vector -> m_nItems) < (_vector -> m_size))
	{
		_vector -> m_items[_vector -> m_nItems] = _item;
		_vector -> m_nItems++;
	}

	else
	{
		if(_vector -> m_blockSize == 0)
		{
			return ERR_OVERFLOW;
		}
		
		temp = (int*)realloc(_vector -> m_items, (_vector -> m_size + _vector -> m_blockSize) * sizeof(int));
		if(temp == NULL)
		{
			return ERR_NOT_INITIALIZED;
		}
		
		_vector -> m_items = temp;
		_vector -> m_size = (_vector -> m_size + _vector -> m_blockSize);
		_vector -> m_items[_vector -> m_nItems] = _item;
		_vector -> m_nItems++;
	}
return ERR_OK;
}

ADTErr VectorDelete(Vector* _vector, int* _item)
{

int *temp;

	if(_vector == NULL || _item == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if (_vector -> m_nItems == 0)
	{
		return ERR_UNDERFLOW;
	}
	
	if ((_vector -> m_size) - (_vector -> m_nItems) >= (_vector -> m_blockSize)*2 && (_vector -> m_size) - (_vector ->  m_blockSize) >= (_vector ->  m_originalSize))
	{
		temp = (int*)realloc(_vector -> m_items, (_vector -> m_size - _vector -> m_blockSize) * sizeof(int));
		if(temp != NULL)
		{
			_vector -> m_items = temp;
			_vector -> m_size = (_vector -> m_size - _vector -> m_blockSize);		 
		}
		
	}
		*_item =  _vector -> m_items [_vector -> m_nItems - 1];
		_vector -> m_nItems--;
		return ERR_OK;
}

ADTErr VectorGet(Vector *_vector, size_t _index, int *_item)
{
	  if (_vector == NULL || _item == NULL)
	  { 
		return ERR_NOT_INITIALIZED;
	  } 
	  if (_index >= _vector->m_nItems)
	  {
       	  return ERR_WRONG_INDEX;
          }
            *_item = _vector->m_items[_index ];
    return ERR_OK;
}

ADTErr VectorSet(Vector *_vector, size_t _index, int  _item)
{
	  
	  if (_vector == NULL)
	  { 
		return ERR_NOT_INITIALIZED;
	  } 
	  if (_index >= _vector->m_nItems)
	  {
	      return ERR_WRONG_INDEX;
	  }
	    _vector->m_items[_index ] = _item;
	    return ERR_OK;
}

ADTErr VectorItemsNum(Vector *_vector, size_t*  _numOfItems)
{
	if (_vector == NULL || _numOfItems == NULL)
	  { 
		return ERR_NOT_INITIALIZED;
	  } 
	*_numOfItems = _vector->m_nItems;
	return ERR_OK;
}

void VectorPrint(Vector *_vector)
{
	int i;
	if (_vector == NULL)
	  { 
		return;
	  } 
	if (_vector->m_nItems == 0)
	  { 
		return;
	  } 
	for (i=0; i< _vector->m_nItems; i++)
	{
    		printf("%d ", _vector->m_items[i]);
	}
	return;
}
size_t GetSize(Vector* _vector)
{
	return _vector->m_size;
}
size_t GetNItems(Vector* _vector)
{
	return _vector->m_nItems;
}
size_t Getn(Vector* _vector, int i)
{
	return _vector->m_items[i];
}


