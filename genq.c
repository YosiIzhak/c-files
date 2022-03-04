#include <stdio.h>
#include <stdlib.h>
#include "genq.h"




struct Queue
{
    void**    m_que;
    size_t  m_size;
    size_t  m_head;      /* Index of head in m_que. */
    size_t  m_tail;      /* Index of tail in m_que. */
    size_t  m_nItems;
};

Queue* QueueCreate(size_t _size)
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
	queue->m_que = (void**) malloc(_size * sizeof(void*));
	if (queue->m_que == NULL) 
	{
        	printf("Memory not allocated.\n");
       	return NULL;
   	}
  	queue->m_size = _size;
  	queue->m_nItems = 0;
  	queue->m_head = 0;
  	queue->m_tail =  0;
  	return queue;
}

void QueueDestroy(Queue** _queue, DestroyItem _itemDestroy)
{
	int i;
	if(*_queue == NULL)
	{
		return;
	}
	if(_itemDestroy != NULL)
	{
		for(i = 0; i < (*_queue)->m_nItems; i++)
		{
			_itemDestroy((*_queue)-> m_que[i]);
		}
	}
	free ((*_queue)->m_que);
	free(*_queue);
	return;
}

QueueResult QueueInsert(Queue* _queue,void* _item)
{
	if(_queue == NULL)
	{
		return QUEUE_UNINITIALIZED_ERROR;
	}
	if (_queue->m_nItems == _queue->m_size)
	{
		return QUEUE_OVERFLOW_ERROR;
	}
	_queue->m_que[_queue->m_tail] = _item;
	_queue->m_tail = ((_queue->m_tail +1) % _queue->m_size);
	_queue -> m_nItems++;
	return QUEUE_SUCCESS;
}
QueueResult QueueRemove(Queue* _queue,void** _item)
{
	if(_queue == NULL || _item == NULL)
	{
		return QUEUE_UNINITIALIZED_ERROR;
	}
	if(QueueIsEmpty(_queue))
	{
	return QUEUE_OVERFLOW_ERROR;
	}
	*_item =  _queue -> m_que [_queue -> m_head];
	if (_queue->m_tail == _queue -> m_head)
	{
		_queue->m_tail = 0;
		_queue -> m_head = 0;
		/*underflow*/
	}
	else
	{
		_queue->m_head = (_queue->m_head +1) % _queue->m_size;	
	}
	return QUEUE_SUCCESS;	
}

size_t QueueIsEmpty(Queue* _queue)
{
	if(_queue == NULL)
	{
		return QUEUE_UNINITIALIZED_ERROR;
	}
	if (_queue->m_nItems == 0)
	{
		return 1;
	}
  	return 0;
}

size_t QueueForEach(Queue* _queue, ActionFunction _action, void* _context)
{
void *elem;
	int index, counter;
	if (_action == NULL || _queue == NULL)
	{ 
		return QUEUE_UNINITIALIZED_ERROR;
	} 
	
	for(index = _queue->m_head, counter = 0; counter < _queue->m_nItems; index = (index+1)% _queue->m_size, counter++)
	{
       	elem = _queue->m_que[index];
       	if(_action(elem, _context) == 0)
       	{
 			break;	
 		}
 	}	
    
 	return index;

}
/*size_t GetQItems(Queue *_queue)
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
*/









