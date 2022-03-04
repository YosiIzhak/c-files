#include <stdio.h>
#include <stdlib.h>
#include "gentree.h"

struct Node
{
    void*   m_data;
    Node*   m_left;
    Node*   m_right;
    Node*   m_father;
};

struct BSTree
{
    Node   m_root;
    LessComparator m_lessThan;
};

void removeTwoSons(Node *_node);
void removeOneSon(Node *_node);
void removeLeaf(Node *_node);

BSTree* BSTree_Create(LessComparator _less)
{
	BSTree* tree;
	tree = (BSTree*) malloc (sizeof(BSTree));
	if (tree == NULL) 
	{
        	return NULL;
   	}
   	tree->m_root.m_father = &tree->m_root;
    tree->m_lessThan = _less;
    tree->m_left = NULL;
    tree->m_right = NULL;
   	return tree;
}

void  Node_Destroy(Node* _root, void (*_destroyer)(void*))
{
	if (_root == NULL)
    {
      		return;
    }
	Node_Destroy(_root->m_left, _destroyer);
   	Node_Destroy(_root->m_right, _destroyer);
	if (_destroyer != NULL)
	{
		_destroyer(_root->m_data);
	}
	free(_root);
}

void  BSTree_Destroy(BSTree** _tree, void (*_destroyer)(void*))
{
	if (_tree == NULL || *_tree == NULL) 
	{
        	return;
   	}
   	Node_Destroy(*_tree->m_root.m_left, _destroyer);
   	free(*_tree);
   	*_tree = NULL;
}
 
Node* newNode(Node* _father, void* _item)
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

static BSTreeItr InsertToTree(Node* _root, void* _data)
{
	if (_root->m_left->m_data  == _data)
	{
 		return _root;
 	}
 	if (_root->m_left->m_data  > _data)
	{
 		if (_root->m_left->m_left == NULL)
 		{
 			_root->m_left->m_left = newNode(_root->m_left,_data);
 			return;
 		}
 	}
 		return InsertToTree (_root->m_left->m_left, _data);
 	if (_root->m_left->m_data < _data)
	{
		if (_root->m_left->m_right == NULL)
		{
 			_root->m_left->m_right = newNode(_root->m_left,_data);
 			return;
 		}
 		return InsertToTree (_root->m_left->m_right, _data);
 	}
}	
BSTreeItr BSTree_Insert(BSTree* _tree, void* _item)
{
	if(_tree == NULL)
	{
		return NULL;
	}
	return InsertToTree (_tree->m_root.m_left, _item);
}

static Node* findMinimum(Node* _root)
{
    while (_root->m_left)
    {
        _root = _root->m_left;
    }
 
    return _root;
}
BSTreeItr FindBegin(const Node* _root)
{
	while (_root->m_left != NULL)
	{
		_root = _root->m_left;
	}
	return (BSTreeItr)_root;
}


BSTreeItr BSTreeItr_Begin(const BSTree* _tree)
{
	
	if(_tree == NULL)
	{
		return NULL;
	}
	return FindBegin(&(_tree->m_root));
}
	
BSTreeItr BSTreeItr_End(const BSTree* _tree)
{
	if(_tree == NULL)
	{
		return NULL;
	}
	return (BSTreeItr*)&_tree->m_root;
}

int BSTreeItr_Equals(BSTreeItr _a, BSTreeItr _b)
{
	if (_a == _b)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
BSTreeItr BSTreeItr_Next(BSTreeItr _it)
{
	if (((Node*)_it)->m_right != NULL)
	{
		findMinimum(((Node*)_it)->m_right);
	}
	else
	{
		while (((Node*)_it) == ((Node*)_it)->m_father->m_left) 
		{
        	_it = ((Node*)_it)->m_father;
       		((Node*)_it)->m_father = ((Node*)_it)->m_father->m_father;
    	}
    return ((Node*)_it)->m_father;
	}
}

BSTreeItr BSTreeItr_Prev(BSTreeItr _it)
{
	 if (((Node*)_it)->m_left != NULL)
        {
             _it = ((Node*)_it)->m_left;
            while (((Node*)_it)->m_right != NULL)
            {
               _it = ((Node*)_it)->m_right;
            }
        }
      if(((Node*)_it) -> m_left == NULL)
      { 
			next = ;
			while(((Node*)_it)->m_father->m_left == ((Node*)_it))
			{
				((Node*)_it) = ((Node*)_it)->m_father;
			}
			((Node*)_it) = ((Node*)_it)->m_father;
      }
        return _it;
}	

void* BSTreeItr_Get(BSTreeItr _it)
{
	return ((Node*)_it)->m_data;
}

void* BSTreeItr_Remove(BSTreeItr _itr)
{
	void* toDelete;
	if(_itr == NULL){
		return NULL;
	}
	toDelete = ((Node*)_itr) -> m_data;
	if(isLeaf((Node*)_itr) == 1){
		removeLeaf((Node*)_itr);

	}
	else if(isOneSon((Node*)_itr) == 1){
		removeOneSon((Node*)_itr);
	}
	else{
		removeTwoSons((Node*)_itr);
	}
	return toDelete;
}

void removeTwoSons(Node *_node)
{
	Node* toSwap;
	toSwap = BSTreeItr_Next(_node);
	_node -> m_data = toSwap -> m_data;
	if(toSwap -> m_left == NULL && toSwap -> m_right == NULL){
	 	removeLeaf(toSwap);
	}
	else{
		removeOneSon(toSwap);
	}
}


int isLeaf(Node *_node)
{
	if(_node -> m_left == NULL && _node -> m_right == NULL){
		return 1;
	}
	return 0;
}

int isOneSon(Node *_node)
{
	if((_node-> m_left == NULL && _node -> m_right != NULL) || 
		(_node-> m_left != NULL && _node -> m_right == NULL)){
		return 1;
	}
	return 0;
}

void removeLeaf(Node *_node){
	if(_node -> m_father -> m_left == _node){
		_node -> m_father -> m_left = NULL;
	}
	else{
		_node -> m_father -> m_right = NULL;
	}
	free(_node);
}
void removeOneSon(Node *_node){
	if(_node-> m_right != NULL){	
		if(_node -> m_father -> m_left == _node){
			_node -> m_father -> m_left = _node-> m_right;
		}
		else{
			_node -> m_father -> m_right = _node-> m_right; 
		}
	}
	else{
		if(_node -> m_father -> m_left == _node){
			_node -> m_father -> m_left = _node -> m_left;
		}
		else{
			_node -> m_father -> m_right = _node -> m_left;
		}
	}
	free(_node);
}
	


