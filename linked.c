#include <stdio.h>
#include <stdlib.h>
#include "linked.h"
#include "enum.h"
#define MAGIC_NUMBER 942199

Person* ListInsertHead(Person* _head ,Person* _p)
{
	if(_p == NULL)
	{
		return _head;
	}
	_p->m_next = _head;
    	return _p;
}

Person* ListRemoveHead(Person* _head, Person** _item)
{
	if(_item == NULL)
	{
		return _head;
	}
	if(_head == NULL)
	{
		*_item = NULL;
		return NULL;
	}
	*_item = _head;
	return _head->m_next;
}


void PrintList(Person *_head)
{
int i;
Person *ptr;
ptr = _head;
i = 1;

	while(ptr != NULL) 
	{
		printf("node number %d: \n", i);
		printf("id: %d \n", ptr -> m_id);
		printf("name: %s \n", ptr -> m_name);
		printf("age: %d \n", ptr -> m_age);
		printf("\n\n");
		ptr = ptr -> m_next; 
		i++;	
	} 
}

Person* ListInsertByKey(Person *_head, int _key, Person *_p)
{
Person *ptr;
Person *prev;
ptr = _head;
prev = NULL;
	if(_head == NULL)
	{
		return _p;
	}
	if(_p == NULL)
	{
		return _head;
	}
	
	while(ptr != NULL) 
	{
		if(ptr ->  m_id == _key)
		{
			return _head;		
		}
		
		if(ptr ->  m_id < _key)
		{
			if(prev == NULL)
			{
				_p -> m_next = ptr;
				return _p;
			}
			_p -> m_next = ptr;
			prev -> m_next = _p;
			return _head;		
		}
		prev = ptr;
		ptr = ptr -> m_next;
	}
	
 _p -> m_next = NULL;
prev -> m_next = _p;
return _head;
}  
Person* ListInsertByKeyRec(Person* _head, int _key, Person* _p)
{
	if (_p == NULL)
	{
		return _head;
	}
	if ( _head == NULL|| _key > _head->m_id)
	{
		_p->m_next =_head;
		return _p;
	}
	if (_key == _head->m_id)
	{
		return _head;
	}
	_head->m_next = ListInsertByKeyRec(_head->m_next, _key, _p);
	 return _head;
}
Person* PointerToLastRec(Person* _head)
{
	
	if (_head == NULL || _head->m_next == NULL)
	{
		return _head;
	}
	_head->m_next = PointerToLastRec(_head->m_next);
	 return _head->m_next;
}

int YoungestPersonRec(Person* _head)
{
	int age;
	if (_head == NULL)
	{
		return -1;
	}
	age = YoungestPersonRec(_head->m_next);
	if (_head->m_age < age)
	{
		return _head->m_age;
	}
	return age;
}
Person* ListRemoveByKeyRec(Person* _head, int _key, Person**_p)
{
	if (_p == NULL || _head == NULL|| _key > _head->m_id)
	{
		return _head;
	}
	if (_key == _head->m_id)
	{
		*_p =_head;
		return _head->m_next;
	}
	_head->m_next =ListRemoveByKeyRec(_head->m_next, _key, _p);
	return _head;
}

Person* ListRemoveByKey(Person* _head, int _key, Person **_p)
{
	Person *ptr;
	Person *previous;
	ptr = _head;
	previous = NULL;
	
	if(_p == NULL)
	{
		return _head;
	}
	if(_head == NULL)
	{
		*_p = NULL;
		return _head;
	}
	
	while(ptr != NULL) 
	{
		if(ptr ->  m_id  < _key)
		{
			return _head;
		}
		if(ptr ->  m_id  == _key)
		{	
			if(previous == NULL)
			{
				*_p = ptr;
				return ptr -> m_next;
			}
			*_p = ptr;
			previous -> m_next = ptr -> m_next;
			return _head;		
		}
		previous = ptr;
		ptr = ptr -> m_next;
	}
return _head;
}
	
	
	
	
	
	
	
    	
    	
    	
