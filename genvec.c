#include <stdio.h>
#include <stdlib.h>
#include "genvec.h"


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
	if(*_vector == NULL || _vector == NULL)
	{
		return;
	}
	if(_elementDestroy != NULL)
	{
		for(i = 0; i < (*_vector)->m_nItems; i++)
		{
			(*_elementDestroy)((*_vector)-> m_items[i]);
		}
	}
	free((*_vector)-> m_items);
	free(*_vector);
	*_vector = NULL;
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



size_t VectorCapacity(const Vector* _vector)
{
	if (_vector == NULL)
	{ 
		return VECTOR_UNITIALIZED_ERROR;
	} 
	return _vector->m_size;
}


size_t VectorForEach(const Vector* _vector, VectorElementAction _action, void* _context)
{
	void *elem;
	int i;
	if (_action == NULL || _vector == NULL)
	{ 
		return VECTOR_UNITIALIZED_ERROR;
	} 
	
	for(i = 0; i < _vector->m_nItems; ++i)
	{
       	elem = _vector->m_items[i];
       	if(_action(elem, i, _context) == 0)
       	{
 			break;	
 		}
 	}	
    
 	return i;
}
/*
#include<stdio.h>
#include<stdlib.h>
#include "genvector.h"

typedef struct Person
{
	int m_id;                   
	char m_name[128];
	int m_age;
}Person;


void ElementDestroy(void *_item)
{
 	if(_item == NULL)
 	{
 		return;
 	}
 	free(_item);
}

int	PrintPerson(void *_element, size_t _index, void *_context)
{
	printf("%d, ", ((Person*)_element)->m_id);
	printf("%s, ", ((Person*)_element)->m_name);
	printf("%d\n", ((Person*)_element)->m_age);
	return 1;
}

int	FindPersonById(void *_element, size_t _index, void *_context)
{
	if(((Person*)_element)->m_id == *((int*)_context))
	{
		return 0;
	}
	return 1;
}

int	FindPersonMaxAge(void *_element, size_t _index, void *_context)
{
	if(((Person*)_element)->m_age > ((Person*)_context)->m_age)
	{
		((Person*)_context)->m_age = ((Person*)_element)->m_age;
	}
	return 1;
}
/**************************************************************************
int main()
{
	Person people[] = {{0, "Adi", 17},
						{1, "Shay", 24},
						{2, "Tom", 13},
						{3, "Maya", 40}};
		
	Vector *pVec;
	Person *removed;
	Person *getVal;
	int found, id = 2;
	Person *maxAge = (Person*)malloc(sizeof(Person));
	if(maxAge == NULL)
	{
		printf("Allocatin failed!\n");
	}
	
	pVec = VectorCreate(5, 3);
	
	VectorAppend(pVec, people);
	VectorAppend(pVec, people+1);
	VectorAppend(pVec, people+2);
	VectorAppend(pVec, people+3);
	
	
	/*printf("size: %ld\n",VectorSize(pVec));
	
	printf("capacity: %ld\n",VectorCapacity(pVec));
	
	VectorRemove(pVec, (void*)&removed);	
	printf("size after remove: %ld\n",VectorSize(pVec));
	printf("removed age: %d\n", removed->m_age);
	
	VectorGet(pVec, 1, (void*)&getVal);
	printf("get name: %s\n", getVal->m_name);
	 
	VectorSet(pVec, 2, people);
	
	VectorForEach(pVec, PrintPerson, 0);
	
	found = VectorForEach(pVec, FindPersonById, &id);
	printf("found: %d\n", found);
	

	maxAge->m_age = people[0].m_age;
	VectorForEach(pVec, FindPersonMaxAge, maxAge);
	printf("Max age: %d\n", maxAge->m_age);
	free(maxAge);
	
	VectorDestroy(&pVec, NULL);
	VectorDestroy(&pVec, NULL);
	
	
}
*/



















