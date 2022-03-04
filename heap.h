#ifndef __HEAP_H__
#define __HEAP_H__
#include "enum.h"
#include "vector.h"
typedef struct Heap Heap;


/*this function build an Heap. she get a pointer to Vector and rearrange
the elements of the Vector in Heap struct. the function return pointer to Heap*/
Heap*   HeapBuild(Vector* _vec); /* O(n) */
/*this function destroy an Heap. she get a pointer to Vector. she doesn't return nothing*/
void    HeapDestroy(Heap* _heap);
/*this function insert an element to the Heap.
 she get a pointer to Heap and the data.
 the function return a compatible messege*/
ADTErr  HeapInsert(Heap* _heap, int _data); /* O(log n) */
/*this function return the max element in thr Heap*/
ADTErr  HeapMax(Heap* _heap, int* _data);
/*this function renove the max element in thr Heap and rearrange
the Heap*/
ADTErr  HeapExtractMax(Heap* _heap, int* _data); /* O(log n) */
/*this function count how many element there are in the Heap. 
she get pointer to the Heap and return the number of elements*/
int     HeapItemsNum(Heap* _heap);
/*this function print all the elements in the Heap. 
she get pointer to the Heap and return void*/
void HeapPrint(Heap* _heap);
#endif
