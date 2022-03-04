#include <stdio.h>
#include <stdlib.h>
#include "genlist.h"
#include "dliststruct.h"
#include "dlistitr.h"

 void push(Node* _ptr, Node* _next)
{
	_ptr->m_prev = _next->m_prev;
	_ptr->m_next = _next;
	_next->m_prev->m_next = _ptr;
	_next->m_prev = _ptr;
}
ListItr ListItrBegin(const List* _list)
{
	if (_list == NULL) 
	{
        	return NULL;
   	}
	return _list->m_head.m_next;
}

ListItr ListItrEnd(const List* _list)
{
	if (_list == NULL) 
	{
        	return NULL;
   	}
	return (ListItr*)&_list->m_tail;
}

int ListItrEquals(const ListItr _a, const ListItr _b)
{
	if (_a == _b)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

ListItr ListItrNext(ListItr _itr)
{
	if (_itr == NULL) 
	{
        	return NULL;
   	}
	return ((Node*)_itr)->m_next;
}

ListItr ListItrPrev(ListItr _itr)
{
	if (_itr == NULL) 
	{
        	return NULL;
   	}
	if (ListItrEquals(((Node*)_itr)->m_prev->m_prev, ((Node*)_itr)->m_prev) == 1)
	{
		return _itr;
	}
	return ((Node*)_itr)->m_prev;
}

void* ListItrGet(ListItr _itr)
{
	if (_itr == NULL || _itr ==ListItrNext(_itr)) 
	{
        	return NULL;
   	}
	return ((Node*)_itr)->m_data;
}

void* ListItrSet(ListItr _itr, void* _element)
{
	void* temp;
	if (_itr == NULL || _element == NULL || _itr ==ListItrNext(_itr))  
	{
        	return NULL;
   	}
	temp = ((Node*)_itr)->m_data;
	((Node*)_itr)->m_data = _element;
	return temp;
}

ListItr ListItrInsertBefore(ListItr _itr, void* _element)
{
	Node* temp;
	if (_itr == NULL || _element == NULL) 
	{
        	return NULL;
   	}
   	temp = (Node*) malloc(sizeof(Node));
	if (temp == NULL) 
	{
        	return NULL;
   	}	
   	PushNode(temp, _itr);
   	temp->m_data = _element;
   	
   	return temp;
}

void* ListItrRemove(ListItr _itr)
{
	void* deletedNodeData;

	if(_itr == NULL || _itr == ListItrNext(_itr))
	{
		return NULL;
	}
	
	deletedNodeData = ((Node*)_itr) -> m_data;
	PopNode(_itr);		/*free in PopNode function*/

return deletedNodeData;
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
	
	
	
	
	
	
	
	
	
	
	
	






