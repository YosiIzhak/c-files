#ifndef __LINKED_H__
#define __LINKED_H__
#include "enum.h"



struct Person
{
    int     m_id;         /* Primary Key */
    char    m_name[128];
    int     m_age;
   struct Person* m_next;
};
typedef struct Person Person;

/* this function insert a Node in head of List. she get pointers
to head and to the new Node. and return pointer to new head.*/
Person* ListInsertHead(Person* _head ,Person* _p);
/* this function remove the Node in head of List. she get pointer
to head and pointer to pointer to the head Node. and return pointer to new head.*/
Person* ListRemoveHead(Person* _head, Person** _item);
/* this function insert a Node to List by key. she get pointers
to head and to the new Node and a key. and return pointer to new head. the List is ordered in ascend order*/
Person* ListInsertByKey(Person* _head, int _key, Person* _p);
/* this function insert a Node to List by key. she get pointers
to head and to the new Node and a key. and return pointer to new head. the List is ordered in ascend order. this function work in recursive way*/
Person* ListInsertByKeyRec(Person* _head, int _key, Person* _p);
/* this function remove a Node to List by key. she get pointers
to head and to the new Node and a key. and return pointer to new head. the List is ordered in ascend order*/
Person* ListRemoveByKey(Person* _head, int _key, Person* *_p);
/* this function remove a Node to List by key. she get pointers
to head and to the new Node and a key. and return pointer to new head. the List is ordered in ascend order. this function work in recursive way*/
Person* ListRemoveByKeyRec(Person* _head, int _key, Person**_p);
/* this function print all the data in Nodes of List. she get pointer
to head. she doesn't return nothing.*/
void      PrintList(Person* _head);




#endif
