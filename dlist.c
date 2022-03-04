#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"

#include "enum.h"
#define MAGIC_NUMBER 942199

struct Node
{
int       m_data;
Node*     m_next;
Node*     m_prev;
};
struct List
{
Node m_head;
Node m_tail;
int m_magicNumber;
};


List* ListCreate()
{
	List* list;
	list = (List*) malloc (sizeof(List));
	if (list == NULL) 
	{
        	return NULL;
   	}
	
  	list->m_head.m_prev = NULL;
  	list->m_head.m_next = &(list->m_tail);
	list->m_tail.m_prev = &(list->m_head);
	list->m_tail.m_next = NULL;
  	return list;
}
void ListDestroy(List* _list)
{
	Node* temp;
	if(_list == NULL || _list-> m_magicNumber != 			MAGIC_NUMBER)
	{
		return;
	}
	_list-> m_magicNumber = 0;
	  

   	while (_list->m_head.m_next != NULL)
    	{
      	 	temp = &(_list->m_head);
      	 	_list->m_head = *(_list->m_head.m_next);
       	free(temp);
    	}
	free(_list);
	return;
}
ADTErr ListPushHead(List* _list, int _data)
{
	Node* ptr;
	if (_list == NULL) 
	{
        	return ERR_NOT_INITIALIZED;
   	} 
	ptr = (Node*) malloc(sizeof(Node));
	if (ptr == NULL) 
	{
        	return ERR_NOT_INITIALIZED;
   	}
   	ptr->m_data = _data;
   	ptr->m_prev = &(_list->m_head);
   	ptr-> m_next = _list->m_head.m_next;
	_list->m_head.m_next->m_prev = ptr;
	_list->m_head.m_next = ptr;
	return ERR_OK;
}
ADTErr     ListPushTail(List* _list, int _data)
{
	Node* ptr;
	if (_list == NULL) 
	{
        	return ERR_NOT_INITIALIZED;
   	} 
	ptr = (Node*) malloc(sizeof(Node));
	if (ptr == NULL) 
	{
        	return ERR_NOT_INITIALIZED;
   	}	
	ptr->m_data = _data;
	ptr-> m_prev = _list->m_tail.m_prev;
	ptr-> m_next = &(_list->m_tail);
	_list->m_tail.m_prev->m_next = ptr;
	_list->m_tail.m_prev = ptr;
	return ERR_OK;
}
ADTErr ListPopHead(List* _list, int* _data)
{
	Node* ptr;
	ptr = &(_list->m_head);
	if (_list == NULL || _data == NULL) 
	{
        	return ERR_NOT_INITIALIZED;
   	}
   	ptr = _list-> m_head.m_next;
   	*(_data) = ptr->m_data;
   	_list->m_head.m_next = ptr->m_next;
   	ptr->m_next->m_prev = ptr->m_prev;
}
ADTErr ListPopTail(List* _list, int* _data)
{
	Node* ptr;
	ptr = &(_list->m_tail);
	if (_list == NULL || _data == NULL) 
	{
        	return ERR_NOT_INITIALIZED;
   	}
   	ptr = _list-> m_tail.m_prev;
   	*(_data) = ptr->m_data;
	_list->m_tail.m_prev = ptr->m_prev;
	ptr->m_prev->m_next = ptr->m_next;
}

size_t ListCountItems(List* _list)
{
	size_t i = 0;
	Node *ptr;
	ptr =_list->m_head.m_next;
	if (_list == NULL) 
	{
        	return 0;
   	} 
	while(ptr-> m_next != NULL) 
	{
		ptr = ptr -> m_next; 
		i++;	
	} 
	return i;
}

int ListIsEmpty(List* _list)
{
	if (_list->m_head.m_next == &(_list->m_tail))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
	

void ListPrint(List* _list)
{
	int i = 1;
	List* ptr = _list;
	Node* nodePtr = &(_list->m_head);

	if (_list == NULL) 
	{
        	return;
   	} 
	while(nodePtr != NULL) 
	{
		printf("node number %d: \n", i);
		printf("data: %d \n", nodePtr -> m_data);
		
		printf("\n\n");
		nodePtr = nodePtr -> m_next; 
		i++;	
	} 
}






