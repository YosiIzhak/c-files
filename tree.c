#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "enum.h"
#define MAGIC_NUMBER 942199

ADTErr InsertToTree(Node* _root, int _data);
void NodeDestroy(Node* _root);
int TreeIsDataSearch(Node* _root, int _data);
void PreOrderPrint(Node* _root);
void InOrderPrint(Node* _root);
void PostOrderPrint(Node* _root);
Node* newNode(Node* _father, int _item);

struct Node
{
    int     m_data;
    Node*   m_left;
    Node*   m_right;
    Node*   m_father;
};

struct Tree
{
    Node*   m_root;
    size_t  m_magicNumber;
};

Tree* TreeCreate()
{
	Tree* tree;
	tree = (Tree*) malloc (sizeof(Tree));
	if (tree == NULL) 
	{
        	return NULL;
   	}
   	tree->m_root = NULL;
   	tree->m_magicNumber = MAGIC_NUMBER;
   	return tree;
}
void NodeDestroy(Node* _root)
{
	if (_root == NULL) 
	{
        	return;
   	}
   	if (_root->m_left != NULL)
   	{
   		NodeDestroy(_root->m_left);
   	}
	if (_root->m_right != NULL)
   	{
		NodeDestroy(_root->m_right);
	}
	free(_root);
}

void TreeDestroy(Tree* _tree)
{
	if(_tree == NULL || _tree-> m_magicNumber != MAGIC_NUMBER)
	{
		return;
	}
	_tree-> m_magicNumber = 0;
	NodeDestroy(_tree->m_root);
	free(_tree);
	return;
}
Node* newNode(Node* _father, int _item)
{
    Node* temp;
    temp  = (Node*)malloc(sizeof(Node));
    if(temp == NULL)
    {
	return NULL;
    } 
    temp->m_data = _item;
    temp->m_left = temp->m_right = NULL;
    temp->m_father = _father;
    return temp;
}
ADTErr InsertToTree(Node* _root, int _data)
{
	if (_root->m_data == _data)
	{
		return ERR_WRONG_INDEX;
	}
	if (_root->m_data > _data)
	{
		if (_root->m_left == NULL)
		{
 			_root->m_left = newNode(_root,_data);
 			return ERR_OK;
 		}
 		return InsertToTree (_root->m_left, _data);
 	}
 	
 	if (_root->m_data < _data)
	{
		if (_root->m_right == NULL)
		{
 			_root->m_right = newNode(_root,_data);
 			return ERR_OK;
 		}
 		return InsertToTree (_root->m_right, _data);
 	}
}	
ADTErr TreeInsert(Tree* _tree, int _data)
{
	if(_tree == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_tree -> m_root == NULL)
	{
		_tree -> m_root = newNode(NULL , _data);	
		if (_tree -> m_root != NULL)
		{
			return ERR_OK;
		}
		return ERR_ALLOCATION_FAILED;
	}
	InsertToTree (_tree->m_root, _data);
}

int TreeIsDataSearch(Node* _root, int _data)
{
	if(_root == NULL)
	{
		return 0;
	}
	if (_root->m_data == _data)
	{
		return 1;
	}
	if (_root->m_data > _data)
	{
		if (_root->m_left == NULL)
		{
			return 0;
		}	
		TreeIsDataSearch(_root->m_left, _data);
		
 	}
 	if (_root->m_data < _data)
	{
		if (_root->m_right == NULL)
		{
			return 0;
		}
		TreeIsDataSearch(_root->m_right, _data);
 	}
}
	
int TreeIsDataFound(Tree* _tree, int _data)
{
	if(_tree == NULL)
	{
		return 0;
	}
	if (_tree->m_root == NULL)
	{
		return 0;
	}
	TreeIsDataSearch (_tree->m_root, _data);
}
void PreOrderPrint(Node* _root)
{
	if(_root == NULL)
	{
		return;
	}
	printf("%d\n",_root->m_data);
	PreOrderPrint(_root->m_left);
	PreOrderPrint(_root->m_right);
}
void InOrderPrint(Node* _root)
{
	if(_root == NULL)
	{
		return;
	}
	InOrderPrint(_root->m_left);
	printf("%d\n",_root->m_data);
 	InOrderPrint(_root->m_right);
}
void PostOrderPrint(Node* _root)
{
	if(_root == NULL)
	{
		return;
	}
	PostOrderPrint(_root->m_left);
	PostOrderPrint(_root->m_right);
	printf("%d\n",_root->m_data);
}

void TreePrint(Tree* _tree, TreeTraverse _traverseMode)
{
	if(_tree == NULL)
	{
		return;
	}
	if(_traverseMode == PRE_ORDER)
	{
		PreOrderPrint(_tree->m_root);
	}
	if(_traverseMode == IN_ORDER)
	{
		InOrderPrint(_tree->m_root);
	}
	if(_traverseMode == POST_ORDER)
	{
		PostOrderPrint(_tree->m_root);
	}
	
}
					
   	
   	
