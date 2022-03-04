#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "genmap.h"
#include "genlist.h"
#include "dliststruct.h"
#include "dlistitr.h"
#include "listfunction.h"

static int DestroyStruct (void*_elemnent, void* _context);
static void PrintList(List* list, keyPrint _PrintKey, ValPrint _PrintValue);
struct DestroyElem
{
void (*m_keyDestroy)(void* _key);
void (*m_valDestroy)(void* _value);
int m_state;
};
struct HashMap
{
List**  m_data;
size_t (*m_hashFunction)(void* _data);
int (*m_equalityFunction)(void* _firstData, void* _secondData);
size_t m_capacity; /*real hash size */
size_t  m_numOfItems; /*number of occupied places in the table*/
};

struct KeyValue
{
	void* m_key;
	void* m_value;
};
/*-----------------------------------------------------------------*/
static size_t GetPrime(size_t _size)
{
	int div, res = 0;
	size_t capacity = _size;
	while (res == 0)
	{
		res = 1;
		for(div=2; div < sqrt(capacity); div++)
		{
			
			if(capacity % div==0)
			{
				res = 0;
				break;
			}
		}
		if (res == 1)
		{
			return capacity;
		}
		capacity++;
	}
	return capacity;
}
/*-----------------------------------------------------------------*/
HashMap* HashMap_Create(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
	HashMap* map;
	size_t capacity = GetPrime(_capacity);
	map = (HashMap*) malloc (sizeof(HashMap));
	if (map == NULL || _hashFunc == NULL || _keysEqualFunc == NULL || _capacity == 0) 
	{
       	return NULL;
   	}
   	map->m_data = (List**) calloc(capacity, sizeof(List*));
	if (map->m_data == NULL) 
	{
        return NULL;
   	}
   	
   
    map->m_capacity = capacity;
    map->m_numOfItems = 0;
    map->m_hashFunction = _hashFunc;
    map->m_equalityFunction = _keysEqualFunc;
    return map;
}
/*-----------------------------------------------------------------*/
void HashMap_Destroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	DestroyElem* destroyPtr;
	int state, i =0;
	ListItr listBegin, listEnd;
	if(_map == NULL || *_map == NULL)
	{
		return;  
	}
	if (_keyDestroy == NULL && _valDestroy == NULL)
	{
		state = 0;
	}
	if (_keyDestroy == NULL && _valDestroy != NULL)
	{
		state = 1;
	}
	if (_keyDestroy != NULL && _valDestroy == NULL)
	{
		state = 2;
	}
	if (_keyDestroy != NULL && _valDestroy != NULL)
	{
		state = 3;
	}
	for(i = 0; i < (*_map)->m_capacity; i++)
	{
		if ((*_map)->m_data[i] != NULL)
		{
			listBegin = ListItrBegin((*_map)->m_data[i]);
  			listEnd = ListItrEnd((*_map)->m_data[i]);
			ListItrForEach(listBegin, listEnd, DestroyStruct, destroyPtr);
			ListDestroy(&(*_map)->m_data[i], NULL); 
		}
		
	}
	
	free((*_map)-> m_data);
	free(*_map);
	*_map = NULL;
}
/*-----------------------------------------------------------------*/
static int DestroyStruct (void*_elemnent, void* _context)
{
	DestroyElem* destroyPtr = _context;
	KeyValue* KvPtr = _elemnent;
	if(_elemnent == NULL)
	{
		return 0;
	}
	if (destroyPtr->m_state == 0)
	{
		free((KeyValue*)KvPtr);
	}
	if (destroyPtr->m_state == 1)
	{
		destroyPtr->m_valDestroy(KvPtr->m_value);
		free((KeyValue*)KvPtr);
	}
	if (destroyPtr->m_state == 2)
	{
		destroyPtr->m_keyDestroy(KvPtr->m_key);
		free((KeyValue*)KvPtr);
	}
	if (destroyPtr->m_state == 3)
	{
		destroyPtr->m_valDestroy(KvPtr->m_value);
		destroyPtr->m_keyDestroy(KvPtr->m_key);
		free((KeyValue*)KvPtr);
	}
return 1;
}

/*-----------------------------------------------------------------*/
Map_Result HashMap_Insert(HashMap* _map, const void* _key, void* _value)
{
	KeyValue* temp;
	ListItr itr, listEnd;
	KeyValue* kV_pair;
	int i, compare;
	size_t index = _map->m_hashFunction((void*)_key) % _map->m_capacity;
	if (_map == NULL || _key == NULL) 
	{
       	return MAP_UNINITIALIZED_ERROR;
   	}
	if (_map->m_data[index] == NULL)
	{
		_map->m_data[index] = ListCreate();
		if (_map->m_data[index] == NULL) 
		{
        	return MAP_UNINITIALIZED_ERROR;
   		}
   	}	
  	itr = ListItrBegin(_map->m_data[index]);
  	listEnd = ListItrEnd(_map->m_data[index]);
  	while (itr != listEnd)
   	{
   		temp = ListItrGet(itr);
   		compare = _map->m_equalityFunction((void*)_key, temp->m_key);
   		if (compare == 1)
   		{
   			return MAP_KEY_DUPLICATE_ERROR;
   		}
   		itr = ListItrNext(itr);
   	}
   	kV_pair = (KeyValue*) malloc(sizeof(KeyValue));
	if (kV_pair == NULL) 
	{
        	return MAP_UNINITIALIZED_ERROR;
   	}
   	kV_pair->m_key = (void*)_key;
	kV_pair->m_value = _value;	
	_map->m_numOfItems++;
   	ListPushTail(_map->m_data[index], kV_pair);
   	return MAP_SUCCESS;
}
/*-----------------------------------------------------------------*/
Map_Result HashMap_Remove(HashMap* _map, void* _searchKey, void** _pKey, void** _pValue)
{
	KeyValue* temp;
	ListItr itr, listEnd;
	int i, compare;
	size_t index = _map->m_hashFunction(_searchKey) % _map->m_capacity;
	if (_map == NULL || _pKey == NULL || _pValue == NULL)
	{
       	return MAP_UNINITIALIZED_ERROR;
   	}
   	if (_searchKey == NULL) 
   	{
   		return MAP_KEY_NULL_ERROR;
   	}
	itr = ListItrBegin(_map->m_data[index]);
	listEnd = ListItrEnd(_map->m_data[index]);
	while (itr != listEnd)
   	{
   		temp = ListItrGet(itr);
   		compare = _map->m_equalityFunction(_searchKey, temp->m_key);
   		if (compare == 1)
   		{
   			*_pKey = temp->m_key;
   			*_pValue = temp->m_value;
   			_map->m_numOfItems--;
   			free(temp);
   			return MAP_SUCCESS;
   		}
   		itr = ListItrNext(itr); 
   	}
	return MAP_KEY_NOT_FOUND_ERROR;
}
/*-----------------------------------------------------------------*/
Map_Result HashMap_Find(const HashMap* _map, const void* _key, void** _pValue)
{
	KeyValue* temp;
	ListItr itr, listEnd;
	int i, compare;
	size_t index = _map->m_hashFunction((void*)_key) % _map->m_capacity;
	if (_map == NULL || _pValue == NULL)
	{
       	return MAP_UNINITIALIZED_ERROR;
   	}
   	if (_key == NULL) 
   	{
   		return MAP_KEY_NULL_ERROR;
   	}
	itr = ListItrBegin(_map->m_data[index]);
	listEnd = ListItrEnd(_map->m_data[index]);
	while (itr != listEnd)
   	{
   		temp = ListItrGet(itr);
   		compare = _map->m_equalityFunction((void*)_key, temp->m_key);
   		if (compare == 1)
   		{
   			*_pValue = temp->m_value;
   			return MAP_SUCCESS;
   		}
   		itr = ListItrNext(itr); 
   	}
   	return MAP_KEY_NOT_FOUND_ERROR;
}
/*-----------------------------------------------------------------*/
size_t HashMap_Size(const HashMap* _map)
{
	return _map->m_numOfItems;
}
/*-----------------------------------------------------------------*/
void PrintMap(HashMap* _map, void (*_keyPrint)(void* _key), void (*_valPrint)(void* _value))
{
	size_t i;
	KeyValue* temp;
	if (NULL == _map)
	{
       	return;
   	}
	for(i = 0; i < _map->m_capacity; i++)
	{
		if (_map->m_data[i] != NULL)
		{
			PrintList(_map->m_data[i], _keyPrint, _valPrint);
		}	
	}
}
/*-----------------------------------------------------------------*/
static void PrintList(List* list, keyPrint _PrintKey, ValPrint _PrintValue)
{
	KeyValue* temp;
	ListItr itr, listEnd;
	itr = ListItrBegin(list);
	listEnd = ListItrEnd(list);
		
	while(itr != listEnd) 
	{
		temp = ListItrGet(itr);

		_PrintKey((temp) -> m_key);
		if(_PrintValue != NULL)
		{
			_PrintValue((temp) -> m_value);
		}
		itr = ListItrNext(itr);	 
	} 
}

	
	
	



