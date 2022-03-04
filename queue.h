#ifndef __QUEUE_H__
#define __QUEUE_H__
#include "enum.h"

typedef struct Queue Queue;

/* this function create a queue. she get the size of the queue,
and allocate the memory. the size must be positive*/
Queue* QueueCreate (size_t _size);
/* this function destry a queue. she get the pointer to the queue,
and free the memory. */
void    	QueueDestroy(Queue *_queue);
/* this function add a element a queue. she get the pointer to the queue,
and and the item value. she add him in the tail of the queue. the
function return OK or ERROR */
ADTErr  	QueueInsert (Queue *_queue, int  _item);
/* this function remove a element a queue. she get the pointer to the queue,and and pointer to item. she remove the item in the head of the queue. the function return OK or ERROR */
ADTErr  	QueueRemove (Queue *_queue, int *_item);
/* this function checks if the queue is empty. she get the pointer to the queue. the function return 1 if empty and 1 else */
int  		QueueIsEmpty(Queue *_queue);
/* this function prints all the elements of queue. she get the pointer to the queue. there isn't return */
void 	QueuePrint(Queue *_queue);


#endif
