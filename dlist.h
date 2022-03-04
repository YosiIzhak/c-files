#ifndef __DLIST_H__
#define __DLIST_H__
#include "enum.h"

typedef struct List List;
typedef struct Node Node;

/* this function create a double List. she get void, and return pointer to list. she allocate the memory of two Nodes, head and tail.
each node with his two pointers initialize to NULL*/
List* ListCreate(void);
/* this function destry a List. she get the pointer to the List,
and free the memory allocation of the Nodes and the List. */
void        ListDestroy(List* _list);
/* this function insert a Node to the head of List. she get the pointer to the List, and data. she return a messege if 
success or not. */
ADTErr     ListPushHead(List* _list, int _data);
/* this function insert a Node to the tail of List. she get the pointer to the List, and data. she return a messege if 
success or not. */
ADTErr     ListPushTail(List* _list, int _data);
/* this function remove a Node from the head of List. she get the pointer to the List, and data. she return a messege if 
success or not. */
ADTErr     ListPopHead(List* _list, int* _data);
/* this function remove a Node from the tail of List. she get the pointer to the List, and data. she return a messege if 
success or not. */
ADTErr    ListPopTail(List* _list, int* _data);
/* this function count the elements of List. she get the pointer to the List. she return the number of elements. */
size_t       ListCountItems(List* _list);
/* this function check if the List is empty or not. she get the pointer to the List. she return 1 if empty and 0 if not */
int            ListIsEmpty(List* _list);

/* ListPrint is only for debug */
void        ListPrint(List* _list);



#endif
