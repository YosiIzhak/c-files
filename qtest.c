#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

size_t GetQItems(Queue *_queue);
size_t GetQHead(Queue *_queue);
 
/* create tests */
void CreateQNotNull()
{
	Queue *ptr;
	ptr= QueueCreate(10);
	printf("Create test 1: ");
	if (ptr == NULL)
	{
		printf("fail\n");
	}
	else
	{
		printf("pass\n");
	}
	QueueDestroy(ptr);
}
void CreateQNull()
{
	Queue *ptr;
	ptr= QueueCreate(0);
	printf("Create test 2: ");
	if (ptr != NULL)
	{
		printf("fail\n");
	}
	else
	{
		printf("pass\n");
	}
	QueueDestroy(ptr);
}
/* destroy tests */
void DesroyTwoQ()
{
	Queue *ptr;
	size_t size, size1;
	printf("destroy test 2: ");
	ptr = QueueCreate(5);
	QueueDestroy(ptr);
	size  = GetQItems(ptr);
	QueueDestroy(ptr);
	size1  = GetQItems(ptr);
	if (size != size1)
	{
		printf("fail\n");
	}
	else
	{
		printf("pass\n");
	}
}
/* add tests */
void AddNullQ()
{
	Queue *ptr;
	printf("add test 1: ");
	ptr = QueueCreate(5);
	if(QueueInsert(NULL, 4) == ERR_NOT_INITIALIZED)
	{
		printf("pass\n");
	}
	else
	{
		printf("fail\n");
	}
	QueueDestroy(ptr);(ptr);
}
void AddNotNullQ()
{
	Queue *ptr;
	size_t size, size1;
	printf("add test 2: ");
	ptr = QueueCreate(10);
	size = GetQItems(ptr);
	QueueInsert(ptr, 4);
	size1 = GetQItems(ptr);
	if(size != size1)
	{
		printf("pass\n");
	}
	else
	{
		printf("fail\n");
	}
	QueueDestroy(ptr);
}
/*delete tests*/ 
void DeleteNotNullQ()
{
	Queue *ptr;
	int temp;
	printf("delete test 1: ");
	ptr = QueueCreate(10);
	if (QueueRemove(NULL, &temp) != ERR_OK)
	{
		printf("pass\n");
	}
	else
	{
		printf("fail\n");
	}
	QueueDestroy(ptr);
}
/*print test*/ 
void PrintQ()
{
	int a;
	Queue *ptr;
	printf("print test 1: ");
	ptr = QueueCreate(5);
	QueueInsert(ptr, 4);
	QueueInsert(ptr, 5);
	QueueInsert(ptr, 6);
	QueueInsert(ptr, 8);
	QueueInsert(ptr, 9);
	
	printf("\n");
	QueuePrint(ptr);
	QueueDestroy(ptr);
}
int main()
{
	CreateQNotNull();
	CreateQNull();
	DesroyTwoQ();
	AddNullQ();
	AddNotNullQ();
	DeleteNotNullQ();
	PrintQ();
}
