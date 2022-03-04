#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#include "enum.h"
#define MAGIC_NUMBER 942199

struct Queue
{
    int*    m_que;
    size_t  m_size;
    size_t  m_head;      /* Index of head in m_que. */
    size_t  m_tail;      /* Index of tail in m_que. */
    size_t  m_nItems;
    size_t  m_magicNumber;
};

Queue* QueueCreate (size_t _size)
{
	Queue* queue;
	if (_size == 0)
	{
		return NULL;
	}
	queue = (Queue*) malloc (sizeof(Queue));
	if (queue == NULL) 
	{
        	printf("Memory not allocated.\n");
       	return NULL;
   	}
	queue->m_que = (int*) malloc(_size * sizeof(int));
	if (queue->m_que == NULL) 
	{
        	printf("Memory not allocated.\n");
       	return NULL;
   	}
  	queue->m_size = _size;
  	queue->m_nItems = 0;
  	queue->m_magicNumber = MAGIC_NUMBER;
  	queue->m_head = 0;
  	queue->m_tail =  0;
  	return queue;
}

void QueueDestroy(Queue *_queue)
{
	if(_queue == NULL || _queue-> m_magicNumber != 			MAGIC_NUMBER)
	{
		return;
	}
	_queue-> m_magicNumber = 0;
	free (_queue -> m_que);
	free(_queue);
	return;
}

ADTErr QueueInsert (Queue *_queue, int  _item)
{
	if(_queue == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if (_queue->m_nItems == _queue->m_size)
	{
		return ERR_OVERFLOW;
	}
	_queue->m_que[_queue->m_tail] = _item;
	_queue->m_tail = ((_queue->m_tail +1) % _queue->m_size);
	_queue -> m_nItems++;
	return ERR_OK;
}
ADTErr QueueRemove (Queue *_queue, int *_item)
{
	if(_queue == NULL || _item == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(QueueIsEmpty(_queue))
	{
	return ERR_UNDERFLOW;
	}
	*_item =  _queue -> m_que [_queue -> m_head];
	if (_queue->m_tail == _queue -> m_head)
	{
		_queue->m_tail = 0;
		_queue -> m_head = 0;
	}
	else
	{
		_queue->m_head == (_queue->m_head +1) % 
		_queue->m_size;	
	}
	return ERR_OK;	
}

int QueueIsEmpty(Queue *_queue)
{
	if(_queue == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if (_queue->m_head == 0)
	{
		return 1;
	}
  	return 0;
}
void QueuePrint(Queue *_queue)
{
	int i;
	int index = _queue->m_head;
	 for (i = 0; i < _queue->m_nItems; i++)
		 {
      			
      			printf("%d\n ",_queue->m_que[index]);
      			index = ((index+1) % (_queue->m_size));
    		 }
    	   	
}

size_t GetQItems(Queue *_queue)
{
	if(_queue == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	return _queue ->m_nItems;
}
size_t GetQHead(Queue *_queue)
{
	if(_queue == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	return _queue ->m_head;
}










