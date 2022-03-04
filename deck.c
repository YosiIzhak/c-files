#include <stdio.h>
#include <stdlib.h>
#include "deck.h"

#define MAGIC_NUMBER 942199
struct Deck
{
    int*    m_items;
    
    size_t  m_magicNumber;
};

Deck* DeckCreate(int _initialSize)
{
	Deck *ptr;
	int i;
	if (_initialSize == 0)
	{
		return NULL;
	}
	
	ptr = (Deck*) malloc (sizeof(Deck));
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
   	for (i = 0; i < _initialSize; i++)
   	{
   		DeckSet(ptr, i, i);	
   	}
  	
  	ptr->m_nItems = _initialSize;
  	ptr->m_magicNumber = MAGIC_NUMBER;
  	ptr->m_size = _initialSize;
  	return ptr;
}

void DeckDestroy (Deck* _deck)
{
	if(_deck == NULL || _deck-> m_magicNumber != MAGIC_NUMBER)
	{
		return;
	}
	_deck-> m_magicNumber = 0;
	free (_deck -> m_items);
	free(_deck);
	return;
}

void DeckShuffle (Deck* _deck)
{
	size_t len;
	int temp, swap;
	DeckItemsNum (_deck,&len);
	currIndex = len;
	for (int i = currIndex -1; i >= 0; i--)
	{
		temp =  rand()%i;
		DeckGet(_deck, i, &swap);
		DeckSet(_deck, i, temp);
		DeckSet(_deck, temp, swap);
	}
}

ADTErr DeckDelete(Deck* _deck, int* _item)
{

int *temp;

	if(_deck == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if (_deck -> m_nItems == 0)
	{
		return ERR_UNDERFLOW;
	}
	temp = (int*)realloc(_deck -> m_items, sizeof(int));
	if(temp != NULL)
	{
		_deck -> m_items = temp;
	}
	*_item =  _deck -> m_items [_deck -> m_nItems - 1];
	_deck -> m_nItems--;
	return ERR_OK;
}
ADTErr DeckGet(Deck *_deck, size_t _index, int *_item)
{
	  if (_deck == NULL || _item == NULL)
	  { 
		return ERR_NOT_INITIALIZED;
	  } 
	  if (_index >= _deck->m_nItems)
	  {
       	  return ERR_WRONG_INDEX;
          }
            *_item = _deck->m_items[_index ];
    return ERR_OK;
} 
ADTErr DeckSet(Deck *_deck, size_t _index, int  _item)
{
	  
	  if (_deck == NULL)
	  { 
		return ERR_NOT_INITIALIZED;
	  } 
	  if (_index >= _deck->m_nItems)
	  {
	      return ERR_WRONG_INDEX;
	  }
	    _deck->m_items[_index ] = _item;
	    return ERR_OK;
}

ADTErr DeckItemsNum(Deck *_deck, size_t*  _numOfItems)
{
	if (_deck == NULL || _numOfItems == NULL)
	  { 
		return ERR_NOT_INITIALIZED;
	  } 
	*_numOfItems = _deck->m_nItems;
	return ERR_OK;
}

void DeckPrint(Deck *_deck)
{
	int i;
	if (_deck == NULL)
	  { 
		return;
	  } 
	if (_deck->m_nItems == 0)
	  { 
		return;
	  } 
	for (i=0; i< _deck->m_nItems; i++)
	{
    		printf("%d ", _deck->m_items[i]);
	}
	return;
}



