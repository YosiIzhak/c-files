#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "enum.h"
#define MAGIC_NUMBER 942199

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
int MyIsFullTree(Node* _root)
{
	if (_root == NULL)
	{
		return 1;
	}
	if (_root->m_left == NULL && _root->m_right == NULL)
        return 1;
 
       if ((_root->m_left) && (_root->n_right))
        return (MyIsFullTree(_root->m_left) && MyIsFullTree(_root->m_right));
 
    
    return 0;
}


int IsFullTree(Tree* _tree)
{
	if(_tree == NULL)
	{
		return 0;
	}
	if (_tree->m_root == NULL)
	{
		return 1;
	}
	MyIsFullTree (_tree->m_root);
}		
	
int MyAreSimilarTrees(Node* _root1, Node* _root2)
{
	if (_root1 != NULL && _root2 != NULL)
	{
		return MyAreSimilarTrees(_root1->m_left, _root2->m_left) &&
		MyAreSimilarTrees(_root1->m_right, _root2->m_right)
	}
	return 0;
}

int AreSimilarTrees(Tree* _tree1, Tree* _tree2)
{
	if(_tree1 == NULL && _tree2 == NULL)
	{
		return 1;
	}	
	if (_tree1->m_root == NULL && _tree2->m_root == NULL))
	{
		return 1;
	}
	MyAreSimilarTrees(_tree1->m_root, _tree2->m_root);
}

void MyMirrorTree(Node* _root)
{
	Node* temp;
	MyMirrorTree(_root->m_left);
    	MyMirrorTree(_root->m_right);
    	
    	temp = _root->m_left;
    	_root->m_left  = _root->m_right;
   	_root->m_right = temp;
}	
		
void MirrorTree(Tree* _tree)
{
	if(_tree == NULL)
	{
		return;
	}
	if (_tree->m_root == NULL)
	{
		return;
	}
	MyMirrorTree(_tree->m_root);
}

int MyCalcTreeHigh(Node* _root)
{
	int leftHigh, rightHigh;
	leftHigh = findHeight(_root->m_left);
   	rightHigh = findHeight(_root->m_right);

    	if (leftHigh > rightHigh)
    	{
      	 	 return leftHigh + 1;
   	} 
   	else
   	{
        	return rightHigh + 1;
    	}
}

int CalcTreeHigh(Tree* _tree)
{
	if(_tree == NULL)
	{
		return -1;
	}
	if (_tree->m_root == NULL)
	{
		return -1;
	}
	MyCalcTreeHigh (_tree->m_root);	
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
	
	
	
	
	
	
	
	
	
	
	
	
	
