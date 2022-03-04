#ifndef __VECTOR_H__
#define __VECTOR_H__
#include "enum.h"

typedef struct Vector Vector;


void HandleErr(ADTErr errNum, char *msg);


Vector* VectorCreate (size_t _initialSize, size_t _extensionBblockSize);

void VectorDestroy (Vector* _vector);


ADTErr VectorAdd (Vector *_vector,  int  _item); 

ADTErr VectorDelete (Vector *_vector, int* _item); 

ADTErr VectorGet(Vector *_vector, size_t _index, int *_item);

ADTErr VectorSet(Vector *_vector, size_t _index, int  _item);

ADTErr VectorItemsNum(Vector *_vector, size_t*  _numOfItems);

void VectorPrint(Vector *_vector);

size_t GetSize(Vector* _vector);

size_t GetNItems(Vector* _vector);

size_t Getn(Vector* _vector, int i);

#endif


















