#ifndef __TREE_H__
#define __TREE_H__
#include "enum.h"
typedef struct Node Node;
typedef struct Tree Tree;
typedef enum
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER
} TreeTraverse;

/* this function create a Tree, and allocate the memory.
 she doesn't getsomething. she return NULL if allocation fails*/
Tree*   TreeCreate();
/* this function destry a Tree. she get the pointer to the Tree,
and free the memory. */
void    TreeDestroy(Tree* _tree);
/* this function add data to the Tree. she get the pointer to the Tree,
and data to insert. she add him in the Tree. the function return 
OK or ERROR */
ADTErr  TreeInsert(Tree* _tree, int _data);
/* this function search data in the Tree. she get the pointer to the Tree, and data to search. the function return 1 if data found and 0 if not */
int     TreeIsDataFound(Tree* _tree, int _data);
/* this function search data in the Tree. she get the pointer to the Tree, and data to search. the function return 1 if data found and 0 if not */
void    TreePrint(Tree* _tree, TreeTraverse _traverseMode);


#endif
