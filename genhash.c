#include <stdio.h>
#include <stdlib.h>
#include "genhash.h"

#define FACTOR 1.3 
struct Hash
{
void**  m_data;
char* 	m_state;
size_t (*m_hashFunction)(void* _data);
int (*m_equalityFunction)(void* _firstData, void* _secondData);
size_t  m_hashSize; /*original size given by the client*/
size_t m_capacity; /*real hash size */
size_t  m_numOfItems; /*number of occupied places in the table*/
size_t  m_maxOfRehashOperations; /*maximum amount of rehash operations which have been done over one insertion*/
size_t  m_counterOfInsertions; /*total amount of insertions into the table*/
size_t  m_allRehashOperations; /*all rehash operations mutual counter*/
};

static int GetPrime(int _size)
{
	int div, res = 0;
	int capacity = _size*FACTOR;
	while (res == 0)
	{
		res = 1;
		for(div=2; div<capacity; div++)
		{
			
			if(capacity % div==0)
			{
				res = 0;
				break;
			}
		}
		capacity++;
	}
	capacity--;
	return capacity;
}
/*-----------------------------------------------------------------*/
Hash* HashCreate(size_t _size, size_t (*_hashFunction)(void*), int (*_equalityFunction)(void*, void*))
{
	Hash* hash;
	size_t capacity = GetPrime(_size);
	hash = (Hash*) malloc (sizeof(Hash));
	if (hash == NULL) 
	{
       	return NULL;
   	}
   	hash->m_data = (void**) malloc(capacity * sizeof(void*));
	if (hash->m_data == NULL) 
	{
        return NULL;
   	}
   	hash->m_state = (char*) malloc(capacity * sizeof(char));
	if (hash->m_state == NULL) 
	{
        return NULL;
   	}
   	
   	hash->m_hashSize = _size;
    hash->m_capacity = capacity;
    hash->m_numOfItems = 0;
    hash->m_maxOfRehashOperations = 4;
    hash->m_counterOfInsertions = 0;
    hash->m_allRehashOperations = 0;
    hash->m_hashFunction = _hashFunction;
    hash->m_equalityFunction = _equalityFunction;
   	return hash;
}
/*-----------------------------------------------------------------*/
void HashDestroy(Hash** _hash, void (*_keyDestroy)(void* _data))
{
	int i =0;
	if(_hash == NULL || *_hash == NULL)
	{
		return;  
	}
	if(_keyDestroy != NULL)
	{
		for(i = 0; i < (*_hash)->m_capacity; i++)
		{
			if (((*_hash)->m_state[i]) == 1)
			{
				(*_keyDestroy)((*_hash)-> m_data[i]);
			}
		}
	}
	free((*_hash)-> m_data);
	free((*_hash)-> m_state);
	free(*_hash);
	*_hash = NULL;
}
/*-----------------------------------------------------------------*/
int HashIsFound(const Hash* _hash, void* _key)
{
	
	size_t index = _hash->m_hashFunction(_key) % _hash->m_capacity;
	while (_hash->m_state[index] != 0)
	{
		if (_hash->m_equalityFunction(_key, _hash->m_data[index]) == 1)
		{
			return index;
		}
		index++;
	}
	return -1;
}
/*-----------------------------------------------------------------*/	
	
HashSet_Result HashInsert(Hash* _hash, void* _data)
{
	int rehashCounter = 0;
	int i = 0;
	size_t index = _hash->m_hashFunction(_data) % _hash->m_capacity;
	if(_hash == NULL || _data == NULL)
	{
		return SET_UNINITIALIZED;  
	}
	if (HashIsFound(_hash, _data) != -1)
	{
		return SET_KEY_DUPLICATE;
	}
	while (_hash->m_state[index] == 1)
	{
		index = index + 1 % _hash->m_capacity;
		rehashCounter++;
	}
	if (_hash->m_maxOfRehashOperations < rehashCounter)
	{
		_hash->m_maxOfRehashOperations = rehashCounter;
		 _hash->m_allRehashOperations += rehashCounter;
	}
	if (_hash->m_state[index] == 0 || _hash->m_state[index] == 2)
	{
		_hash->m_data[index] = _data;
		 _hash->m_numOfItems++;
		_hash->m_state[index] == 1;
		_hash->m_counterOfInsertions++;
		return SET_SUCCESS;
	}
}
/*-----------------------------------------------------------------*/			
HashSet_Result HashRemove(Hash* _hash, void* _key, void** _data)
{
	size_t index;
	if (_hash == NULL || _key == NULL || _data == == NULL)
	{
		return SET_UNINITIALIZED;
	}
	if (HashIsFound(_hash, _key) != -1)
	{	
		index = HashIsFound(_hash, _key);
		*_data = _hash->m_data[index];
		_hash->m_state[index] == 2;
		_hash->m_numOfItems--;
		free(_hash->m_data[index]);
	}
}
/*-----------------------------------------------------------------*/	
size_t HashNumOfItems(const Hash* _hash)
{
	if (_hash == NULL)
	{
		return 0;
	}
	return _hash->m_numOfItems;
}
/*-----------------------------------------------------------------*/
size_t HashCapacity(const Hash* _hash)
{
	if (_hash == NULL)
	{
		return 0;
	}
	return _hash->m_hashSize;
}
/*-----------------------------------------------------------------*/
double HashAverageRehashes(const Hash* _hash)
{
	double average;
	 if (_hash == NULL || _hash->m_counterOfInsertions == 0)
	{
		return 0;
	}
	 average = (double)_hash->m_allRehashOperations / _hash->m_counterOfInsertions;
	return average;
}
/*-----------------------------------------------------------------*/
size_t HashMaxReHash(const Hash* _hash)
{
	if (_hash == NULL)
	{
		return 0;
	}
	return _hash->m_maxOfRehashOperations;
}
/*-----------------------------------------------------------------*/
void HashPrint(const Hash* _hash, void (*PrintKey)(void*))
{
	size_t i;
	if (_hash == NULL || PrintKey == NULL)
	{
		return;
	}
	for(i = 0; i < _hash->m_capacity; i++)
	{
		if (_hash->m_state[i] == 1)
		{
			(*PrintKey)(_hash-> m_data[i]);
		}
	}
}
/************************************************************************/



/*
int main()
{
int a;
a= GetPrime(1000);
printf("%d", a);
}*/



	
