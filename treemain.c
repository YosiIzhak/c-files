#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

void CheckTree()
{
	Tree* Tree;
	int a;
	Tree = TreeCreate();
	TreeInsert(Tree, 7);
	TreeInsert(Tree, 1);
	TreeInsert(Tree, 4);
	TreeInsert(Tree, 9);
	TreeInsert(Tree, 8);
	/*a = TreeIsDataFound(Tree, 8);
	printf("%d\n", a);*/
	TreePrint(Tree,PRE_ORDER);
	TreeDestroy(Tree);
}
int main()
{

CheckTree();


}
