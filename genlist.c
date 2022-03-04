#include <stdio.h>
#include <stdlib.h>
#include "genlist.h"
#include "dliststruct.h"

static void push(Node* _ptr, Node* _next);
static void pop(Node* _ptr);

/********************FunctionSignatures*******************/

static void PushNode(Node *_node, Node *_next);
static void PopNode(Node *_node);



/***********************ListCreate**********************/

List* ListCreate(void)
{
List* list;

	if ((list = (List*) malloc (sizeof(List))) == NULL) 
	{
        	return NULL;
   	}
   	
   	list-> m_head.m_next = &list-> m_tail;
  	list-> m_head.m_prev = &list-> m_head;
  	list-> m_tail.m_next = &list-> m_tail;
	list-> m_tail.m_prev = &list-> m_head;
	
 return list;
}

/***********************ListDestroy**********************/

void ListDestroy(List** _list, void (*_elementDestroy)(void* _item))
{
Node* temp;
Node* tempNext;

	if(_list == NULL || *_list == NULL)
	{
		return;
	}
	
	temp = (*_list) -> m_head.m_next;
   	while (temp != &(*_list)-> m_tail)
    	{
    		if(_elementDestroy != NULL)
    		{
    			_elementDestroy(temp -> m_data);		
    		}
    		tempNext = temp -> m_next;
      	 	free(temp);
      	 	temp = tempNext;   		
    	}
	free(*_list);
	*_list = NULL;
}

/***********************ListPushHead**********************/

ListResult ListPushHead(List* _list, void* _item)
{
Node *node = NULL;

	if(_list == NULL || _item == NULL)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	
	if((node = (Node*) malloc(sizeof(Node))) == NULL)
	{
		return LIST_ALLOCATION_ERROR;
	}
	node -> m_data = _item;
	PushNode(node,_list -> m_head.m_next);
	
return LIST_SUCCESS;
}

/***********************ListPushTail**********************/

ListResult ListPushTail(List* _list, void* _item)
{
Node* node = NULL;

	if(_list == NULL || _item == NULL)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	
	if((node = (Node*) malloc(sizeof(Node))) == NULL)
	{
		return LIST_ALLOCATION_ERROR;
	}
	node -> m_data = _item;
	PushNode(node, &_list -> m_tail);

return LIST_SUCCESS;
}

/***********************ListPopHead**********************/

ListResult ListPopHead(List* _list, void** _item)
{
	if (_list == NULL ||  _item == NULL) 
	{
      		  return LIST_UNINITIALIZED_ERROR;
   	}
   		
	if(_list -> m_head.m_next == &_list -> m_tail)
	{
		return LIST_UNDERFLOW_ERROR;
	}
	
	*_item = _list -> m_head.m_next -> m_data;
	PopNode (_list -> m_head.m_next);
   
return LIST_SUCCESS;
}

/***********************ListPopTail**********************/

ListResult ListPopTail(List* _list, void** _item)
{
	if (_list == NULL || _item == NULL) 
	{
      		  return LIST_UNINITIALIZED_ERROR;
   	}
   	
	if(_list ->m_head.m_next == &_list -> m_tail)
	{
		return LIST_UNDERFLOW_ERROR;
	}
	
	*_item = _list-> m_tail.m_prev -> m_data;
	PopNode(_list -> m_tail.m_prev);	
	
return LIST_SUCCESS;
}

/***********************ListSize**********************/

size_t ListSize(const List* _list)
{
size_t count = 0;
Node *node;


	if (_list == NULL) 
	{
       		 return 0;
   	} 
   	
	node = _list -> m_head.m_next;

	while(node != &_list-> m_tail) 
	{
		count++; 
		node = node -> m_next; 
	} 

return count;
}

/***********************PushNode**********************/

static void PushNode(Node *_node, Node *_next)
{
	_node -> m_prev = _next -> m_prev;
	_node -> m_next = _next;
	_next -> m_prev -> m_next = _node;
	_next -> m_prev = _node;
}

/***********************PopNode**********************/

static void PopNode(Node *_node)
{
	_node -> m_next -> m_prev = _node -> m_prev;
	_node -> m_prev -> m_next = _node -> m_next;
	free(_node);
}


/***********************TestFunction**********************/

struct Person
{
int m_id;
char m_name[128];
int m_age;
}; 

void ListPrint(List* _list)
{
int i;
Node *node;
void* item;
i = 1;

	if (_list == NULL) 
	{
        return;
   	} 
	
	node =_list -> m_head.m_next;

	while(node != &_list-> m_tail) 
	{
		item = node -> m_data;
		printf("Person %d\n",i);
		printf("id: %d\n",(((struct Person*) item) -> m_id));
		printf("name: %s\n",((struct Person*) item) -> m_name);
		printf("age: %d\n\n",((struct Person*) item) -> m_age);
		i++; 
		node = node -> m_next; 
	} 
}




/*Node* GetmHeadMPrev(List *_list)
{
	return _list-> m_head.m_prev;
}

int GetData(List* _list, int index)
{
int i;
Node *node;

	node = _list -> m_head.m_next;

	for(i = 0; i < index + 1; i++)
	{ 	
		if(i == index)
		{
			return node -> m_data;
		}
		node = node -> m_next;			
	}
}*/





