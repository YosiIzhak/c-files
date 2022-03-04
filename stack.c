#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "vector.h"
#include "enum.h"
#define MAGIC_NUMBER 9421
struct Stack
{
    Vector *m_vector;
    size_t  m_magicNumber;
};

Stack* StackCreate (size_t _size, size_t _blockSize)
{
	Stack *stack;
	if (_size == 0 && _blockSize == 0)
	{
		return NULL;
	}
	
	stack = (Stack*) malloc (sizeof(Stack));
	if (stack == NULL) 
	{
        	return NULL;
   	}
	if ((stack->m_vector = VectorCreate(_size, _blockSize)) == NULL)
	{
		free(stack);
		return NULL;
	}
	return stack;
}

void StackDestroy(Stack* _stack)
{
	if(_stack != NULL && _stack->m_magicNumber == MAGIC_NUMBER)
	{
	_stack->m_magicNumber = 0;
	VectorDestroy(_stack->m_vector);
	free(_stack);
	}
	return;
}

ADTErr  StackPush   (Stack* _stack, int  _item)
{
	if(_stack ==NULL)
	{
	return ERR_NOT_INITIALIZED;
	}
	return VectorAdd(_stack->m_vector, _item);
}

ADTErr StackPop (Stack* _stack, int* _item)
{
	if(_stack ==NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	return VectorDelete(_stack->m_vector, _item);
}

ADTErr  StackTop    (Stack* _stack, int* _item)
{
	  size_t numOfElements;
	  ADTErr status;
	  if (_stack == NULL)
	  { 
		return ERR_NOT_INITIALIZED;
	  } 
	 if ((status == VectorItemsNum(_stack-> m_vector, 			&numOfElements)) != ERR_OK)
	 {
	 	return status;
	 }
	 return VectorGet(_stack-> m_vector, numOfElements -1, _item);
}

int StackIsEmpty(Stack* _stack)
{
	size_t numOfElements;
	if(_stack == NULL)
	{
		return 1;
	}
	VectorItemsNum(_stack-> m_vector, &numOfElements);
	if (numOfElements == 0)
	{ 
		return 1;
	} 
	else
	{
		return 0;
	}
}

void    StackPrint   (Stack *_stack)
{
	int i;
	if (_stack == NULL)
	  { 
		return;
	  } 
	VectorPrint(_stack->m_vector);
}
/*size_t GetStackSize(Stack* _stack)
{
	return _stack ->m_vector->m_size;
}
size_t GetStackNItems(Stack* _stack)
{
	return _stack ->m_vector->m_nItems;
}*/



