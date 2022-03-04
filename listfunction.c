#include <stdio.h>
#include <stdlib.h>
#include "genlist.h"
#include "dliststruct.h"
#include "dlistitr.h"
#include "listfunction.h"

static int InFindFirst(int _returnVal, void* _inContext);
static int InCountIf(int _returnVal, void* _inContext);
static int InForEach(int _returnVal, void* _inContext);

ListItr GenEngine(ListItr _begin, ListItr _end, InFunction _Innear, PredicateFunction _predicate, void* _context, void* _inContext)
{
	ListItr temp = _begin;
	void* element;
	while (temp != _end) 
	{
		element = ListItrGet(temp);
		if (_Innear(_predicate(element, _context), _inContext))
		{
			break;
		}
		temp =  ((Node*)temp)->m_next;
	}
	return temp;
}
ListItr ListItrFindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	ListItr temp;
	if (_predicate == NULL) 
	{
        	return NULL;
   	}
	temp = GenEngine(_begin, _end, InFindFirst,  _predicate, _context, NULL);
	return temp;
}

size_t ListItrCountIf(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	size_t  count = 0;
	ListItr* temp = _begin;
	void* element;
	void* inContext = &count;
	if (_predicate == NULL) 
	{
        	return;
   	}
	GenEngine( _begin, _end, InCountIf, _predicate, _context, inContext);
	return count;
}
ListItr ListItrForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context)
{
	ListItr* temp;
	void* element;
	if (_action == NULL) 
	{
        	return NULL;
   	}
	temp = GenEngine( _begin, _end, InForEach, _action, _context, NULL);
	return temp;
}

static int InFindFirst(int _returnVal, void* _inContext)
{
	if (_returnVal)
	{
		return 1;
	}
	return 0;
}

static int InCountIf(int _returnVal, void* _inContext)
{
	if (_returnVal)
	{
		(*(int*)_inContext)++;
	}
	return 0;
}

static int InForEach(int _returnVal, void* _inContext)
{
	if (!_returnVal)
	{
		return 1;
	}
	return 0;
}


	
	
	
	
