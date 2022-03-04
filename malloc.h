#ifndef __MYMALLOC_H__
#define __MYMALLOC_H__
typedef unsigned char BYTE;
/*After initializiation only _memorySize-12 bytes are available
for client usage */
void MyMallocInit(void* _memory, size_t _memorySize);
/*Every allocation returns _requiredBlockSize bytes to the
client,
* but reserves _requiredBlockSize+4 bytes from _memory .
*/
void* MyMalloc(void* _memory, size_t _requiredBlockSize);
void MyFree(void* _myBlock);
#endif /* __MYMALLOC_H__*/
