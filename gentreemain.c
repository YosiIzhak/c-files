#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gentree.h"


struct Person
{
int m_id;
char m_name[128];
int m_age;
}; 


/******ItemDestroy*****/

void ItemDestroy(void* _item)
{
	if(_item == NULL)
	{
		return;
	}
	free(_item);
	_item = NULL;
}

/******isIdExist*****

int isIdExist(void*_elemnent, void* _context)
{
	if( _elemnent == NULL)
	{
		return;
	}
	
	if(((struct Person*) _elemnent) -> m_id == (int) _context)
	{
		return 1;
	}
return 0;
}*/
int compareId(void* _item1, void* _item2)
{
	if (((Person*)_item2)->m_id > (((Person*)_item1)->m_id))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/******printPerson*****/

int printPerson (void*_elemnent, void* _context)
{
	if(_elemnent == NULL)
	{
		return 0;
	}
	printf("id: %d\n",((struct Person*) _elemnent) -> m_id);
	printf("name: %s\n",((struct Person*) _elemnent) -> m_name);
	printf("age: %d\n\n",((struct Person*) _elemnent) -> m_age);
	
return 1;
}

/******CaountIfIdEven*****/

int CaountIfIdEven (void*_elemnent,  void* _context)
{
	if(((struct Person*) _elemnent) -> m_id%2 == 0)
	{
		(*(int*)_context)++;
		return 1;	
	}
return 0;	
}

int main()
{
size_t countIf;
int count = 0;
BSTree* tree;
void* item;
void* item2;
void* item3;
void* item4;
void* item5;
void* item6;
void* data;
int id;

struct Person* p1;
struct Person* p2;
struct Person* p3;
struct Person* p4;
struct Person* p5;

p1 = (struct Person*)malloc(sizeof(struct Person)*1);		
p1 -> m_id = 50;
strcpy(p1 -> m_name, "yakov");
p1 -> m_age = 30;

p2 = (struct Person*)malloc(sizeof(struct Person)*1);		
p2 -> m_id = 20;
strcpy(p2 -> m_name, "dana");
p2 -> m_age = 15;

p3 = (struct Person*)malloc(sizeof(struct Person)*1);		
p3 -> m_id = 16;
strcpy(p3 -> m_name, "david");
p3 -> m_age = 17;

p4 = (struct Person*)malloc(sizeof(struct Person)*1);		
p4 -> m_id = 80;
strcpy(p4 -> m_name, "gal");
p4 -> m_age = 35;

p5 = (struct Person*)malloc(sizeof(struct Person)*1);		
p5 -> m_id = 7;
strcpy(p5 -> m_name, "yoni");
p5 -> m_age = 95;

tree = BSTree_Create(compareId);


}
