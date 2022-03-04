#include <stdio.h>
#include <stdlib.h>
#include "genvector.h"


struct Vector
{
    void**    m_items;
    size_t  m_originalSize; /* original allocated space for items)*/	
    size_t  m_size;      /* actual allocated space for items)*/
    size_t  m_nItems;     	    /* actual number of items */
	size_t  m_blockSize;
};
Vector* VectorCreate(size_t _initialCapacity, size_t _blockSize)
{
	Vector *ptr;
	if (_initialCapacity == 0 && _blockSize == 0)
	{
		return NULL;
	}
	
	ptr = (Vector*) malloc (sizeof(Vector));
	if (ptr == NULL) 
	{
        	printf("Memory not allocated.\n");
       	return NULL;
   	}
	ptr->m_items = (void**) malloc(_initialCapacity * sizeof(void*));
	if (ptr->m_items == NULL) 
	{
        	printf("Memory not allocated.\n");
       	return NULL;
   	}
  	ptr->m_originalSize = _initialCapacity;
  	ptr->m_nItems = 0;
  	ptr->m_blockSize = _blockSize;
  	ptr->m_size = _initialCapacity;
  	return ptr;
}

void VectorDestroy(Vector** _vector, void (*_elementDestroy)(void* _item))
{
	int i;
	if(*_vector == NULL )
	{
		return;
	}
	if(_elementDestroy != NULL )
	{
		for(i = 0; i < (*_vector)-> m_nItems; i++)
		{
			_elementDestroy((*_vector) -> m_items[i]);
		}
	}
	free ((*_vector)->m_items);
	free(*_vector);
	return;
}

VectorResult VectorAppend(Vector* _vector, void* _item)
{
	void *temp;
	if(_vector == NULL)
	{
		return VECTOR_ALLOCATION_ERROR;
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
			return VECTOR_UNITIALIZED_ERROR;
		}
		
		temp = (void**)realloc(_vector -> m_items, (_vector -> m_size +   _vector->m_blockSize) * sizeof(void*));
		if(temp == NULL)
		{
			return VECTOR_ALLOCATION_ERROR;
		}
		
		_vector -> m_items = temp;
		_vector -> m_size = (_vector -> m_size + _vector->m_blockSize);
		_vector -> m_items[_vector -> m_nItems] = _item;
		_vector -> m_nItems++;
	}
return VECTOR_SUCCESS;
}

VectorResult VectorRemove(Vector* _vector, void** _pValue)
{

	void *temp;

	if(_vector == NULL || _pValue == NULL)
	{
		return VECTOR_ALLOCATION_ERROR;
	}
	if (_vector -> m_nItems == 0)
	{
		return VECTOR_UNITIALIZED_ERROR;
	}
	
	if ((_vector -> m_size) - (_vector -> m_nItems) >= (_vector -> m_blockSize)*2 && (_vector -> m_size) - (_vector ->  m_blockSize) >= (_vector ->  m_originalSize))
	{
		temp = (void**)realloc(_vector -> m_items, (_vector->m_size - _vector -> m_blockSize) * sizeof(void*));
		if(temp != NULL)
		{
			_vector -> m_items = temp;
			_vector -> m_size = (_vector->m_size - _vector->m_blockSize);		 
		}
		
	}
		*_pValue =  _vector->m_items [_vector -> m_nItems - 1];
		_vector -> m_nItems--;
		return VECTOR_SUCCESS;
}

VectorResult VectorGet(const Vector* _vector, size_t _index, void** _pValue)
{
	  if (_vector == NULL)
	  { 
		return VECTOR_ALLOCATION_ERROR;
	  } 
	  if (_index >= _vector->m_nItems)
	  {
       	  return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
          }
            *_pValue = _vector->m_items[_index];
    return VECTOR_SUCCESS;
}

VectorResult VectorSet(Vector* _vector, size_t _index, void*  _value)
{
	  if (_vector == NULL)
	  { 
		return VECTOR_ALLOCATION_ERROR;
	  } 
	  if (_index >= _vector->m_nItems)
	  {
	      return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	  }
	    _vector->m_items[_index] = _value;
	    return VECTOR_SUCCESS;
}

size_t VectorSize(const Vector* _vector)
{
	if (_vector == NULL)
	  { 
		return VECTOR_UNITIALIZED_ERROR;
	  } 
	return _vector->m_nItems;
}

int VectorPrint(void* _element, size_t _index, void* _temp)
{
	Vector* ptr;
	int i;
	VectorGet(vector, _index, &elem);
    printf("%d ", *(int*)elem);
	return;
}

size_t VectorCapacity(const Vector* _vector)
{
	if (_vector == NULL)
	{ 
		return VECTOR_UNITIALIZED_ERROR;
	} 
	return _vector->m_size;
}
/*VectorElementAction VectorFind(void* element, int _index, void* _pValue)
{
	return &element - &_pValue;
}*/

size_t VectorForEach(const Vector* _vector, VectorElementAction _action, void* _context)
{
	int i;
	size_t len = VectorSize(_vector);
	void *elem = (void**)malloc(sizeof(void*));
	for(i = 0; i < len; ++i)
	{
       VectorGet(_vector, i, &elem);
       if(_action(elem, i, _context) == 0)
       {
 			break;	
 	   }	
    }
 	return i;
}




