#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include "vector.h"
#include "enum.h"
#define ARR_SIZE 30000

ADTErr MergeSort (Vector* _vec);
ADTErr InsertionSort (Vector* _vec);
static void Merge (Vector* _vec, int* _temp, size_t _start, size_t _end, int _mid);
void MergeRec (Vector* _vec, int* _ptr, size_t _begin, size_t _end);
ADTErr CountingSort (Vector* _vec, int _maxValue);
static void countingForRadix(Vector* _vec, int _nDigits, int _digit);

ADTErr RadixSort (Vector* _vec,int _nDigits)
{
	int i, digit = 1;
	size_t len;
	VectorItemsNum (_vec,&len);
	
	for (i = 1; i <= _nDigits; i++)
   	{		
		countingForRadix(_vec, len, digit);
		digit = digit * 10;
	}
}

static void countingForRadix(Vector* _vec, int _len, int _digit)
{
	int i, temp, curr_digit;
	int* initArr;
	int* orderArr;
	initArr = (int*) calloc (10, sizeof(int));
	if (initArr == NULL) 
	{
        	return;
   	}
	for (i = 0; i < _len; i++)
	{
		VectorGet(_vec, i, &temp);
		curr_digit = (temp / _digit) % 10;
		initArr[curr_digit]++;
	}
	orderArr = (int*) malloc (sizeof(int)*_len);
	if (orderArr == NULL) 
	{
        	return;
   	}
	for (i = 1; i < 10; i++)
	{
		initArr[i] = initArr[i] + initArr[i -1];
	}
	for (i = _len - 1; i >= 0; i--)
	{
		VectorGet(_vec, i, &temp);
		curr_digit = (temp / _digit) % 10;
		orderArr[initArr[curr_digit] - 1] = temp;
		initArr[curr_digit]--;
	}
	for (i = 0; i < _len; i++)
	{
		VectorSet(_vec, i, orderArr[i]);	
	}
	free(initArr);
	free(orderArr);
}


ADTErr CountingSort (Vector* _vec, int _maxValue)
{
	size_t len;
	int j, i, index, temp, size = _maxValue +1;
	int* initArr;
	int* orderArr;
	initArr = (int*) calloc (size, sizeof(int));
	if (initArr == NULL) 
	{
        	return ERR_NOT_INITIALIZED;
   	}
   	VectorItemsNum (_vec,&len);
   	for (i = 0; i < len; i++)
   	{
   		VectorGet(_vec, i, &temp);
   		initArr[temp]++;
   	}
   	orderArr = (int*) malloc (sizeof(int)*len);
	if (orderArr == NULL) 
	{
        	return ERR_NOT_INITIALIZED;
   	}
   	for (i = 1; i < size; i++)  /*------*/
   	{
   		initArr[i] = initArr[i] + initArr[i -1] ;
     	}
        for (i = len - 1; i >= 0 ; i--)
   	{
   		VectorGet(_vec, i, &temp);
   		orderArr[initArr[temp]-1] = temp;
   		initArr[temp]--;
   	}
        for (i = 0; i < len; i++)
   	{
   		VectorSet(_vec, i, orderArr[i]);	
   	}
   	free(initArr);
   	free(orderArr);
}
   	
ADTErr MergeSort (Vector* _vec)
{
	size_t len;
	int* ptr;
	int size;
	if(_vec == NULL)
   	{
		return ERR_NOT_INITIALIZED;
    	}
	VectorItemsNum (_vec,&len);
	size = len;
	ptr = ((int*) malloc (sizeof(int)*size));
	if (ptr == NULL) 
	{
        	return ERR_NOT_INITIALIZED;
   	}
	MergeRec(_vec, ptr, 0, len -1);
	free(ptr);
}
	
void MergeRec (Vector* _vec, int* _ptr, size_t _begin, size_t _end)
{
	size_t len;
	int mid;
	if (_end <= _begin)
	{
		return;
	}
	mid = (_begin + _end)/ 2; 
	MergeRec (_vec, _ptr, _begin, mid);	
	MergeRec (_vec, _ptr, mid + 1, _end);
	Merge (_vec, _ptr, _begin, _end, mid);
}

static void Merge (Vector* _vec, int* _temp, size_t _start, size_t _end, int _mid)
{
int i = _start;
int j = _mid + 1;
int k = _start;
int p;
int leftItem;
int rightItem;

	while(i <= _mid && j <= _end)
	{
		VectorGet(_vec, i, &leftItem);
		VectorGet(_vec, j, &rightItem);
		if(leftItem > rightItem)
		{
			_temp[k] = rightItem;
			k++;
			j++;	
		}
		else
		{
			_temp[k] = leftItem;
			k++;
			i++;
		}		
	}
	

	while(i <= _mid)	
	{
		VectorGet(_vec, i, &leftItem);
		_temp[k] = leftItem;
		k++;
		i++;	
	}
	
	while(j <= _end)
	{
		VectorGet(_vec, j, &rightItem);
		_temp[k] = rightItem;
		k++;
		j++;
	}
	
	for(p = _start; p <= _end; p++)
	{
		VectorSet(_vec, p, _temp[p]);	
	}
}

ADTErr SelectionSort (Vector* _vec)
{
	size_t len;
	int i, j, curr, temp, index, min;
	if(_vec == NULL)
   	 {
		return ERR_NOT_INITIALIZED;
    	}
    	VectorItemsNum (_vec,&len);
	
	for (i = 0; i < len; i++)
	{
		VectorGet(_vec, i, &curr);
		min = curr;
		for (j = i; j < len; j++)
		{
			VectorGet(_vec, j, &temp);
			if (temp < min)
			{
				min = temp;
				index = j; 
			}
		}
		VectorSet(_vec, i, min);
		VectorSet(_vec, index, curr);
	}
}

static ADTErr ShellCompare (Vector* _vec, int gap, size_t len)
{
	int j, i, k, count = 0;
	int item1, item2;
	while (gap > 1)
	{
		for (i = 1; i <= gap; i++)
		{
			for (k = i*len / gap -1; count < len / gap - 1 ; k--)
        		{	
				count++;
				VectorGet(_vec, k, &item1);
       	 		VectorGet(_vec, k - gap, &item2);
				if(item1 > item2)
       			{
       				VectorSet(_vec, k, item2);
       				VectorSet(_vec, k - gap, item1);
          			}
          		}
          		count = 0;
		}	
		gap = gap / 2;
	}
	InsertionSort(_vec);
}
		
		
ADTErr ShellSort (Vector* _vec)
{
    int p, i, gap;
    size_t len;
    int item1, item2;
    if(_vec == NULL)
    {
		return ERR_NOT_INITIALIZED;
    }
    VectorItemsNum (_vec,&len);
    gap = 1;
    ShellCompare(_vec, gap, len);
}  


ADTErr MyQuickSort (Vector* _vec, size_t start, size_t end)
{
	size_t j = end, i= start + 1, pivot = start;
    	int i_item, j_item, pivot_item;
    	if (start >= end)
    	{
    		return ERR_OK;
    	}
    	while (i <= j)
		{
		VectorGet(_vec ,i, &i_item);
		VectorGet(_vec ,pivot, &pivot_item);
		while (i <= end && i_item <= pivot_item)
		{
			i++;
			VectorGet(_vec ,i, &i_item);
		}
		VectorGet(_vec ,j, &j_item);
		while (j > start && j_item >= pivot_item)
		{
			j--;
			VectorGet(_vec ,j, &j_item);
		}
		if (i > j)
		{
			VectorSet(_vec, j, pivot_item);
      			VectorSet(_vec, pivot, j_item);
      		}
      		else
      		{
      			VectorSet(_vec, i, j_item);
      			VectorSet(_vec, j, i_item);
      		}
      	}
      	MyQuickSort(_vec, start, j - 1);
      	MyQuickSort(_vec, j + 1, end);
}
	
	
ADTErr QuickSort (Vector* _vec)
{
        size_t len;
        if(_vec == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	VectorItemsNum (_vec,&len);
	MyQuickSort (_vec, 0, len - 1);
}
	
ADTErr InsertionSort (Vector* _vec)
{
    int p, i, flag;
    size_t len;
    int item1, item2;
    if(_vec == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	VectorItemsNum (_vec,&len);
	for (p = 1; p < len ; p++)
       {
		for (i = p; i > 0; i--)
        	{
			VectorGet(_vec, i, &item1);
       	 	VectorGet(_vec, i - 1, &item2);
			if(item1 < item2)
       		{
       			VectorSet(_vec, i, item2);
       			VectorSet(_vec, i - 1, item1);
          		}
			else
			{
				break;
			}
		}
	}
}	
ADTErr ShakeSort(Vector* _vec)
{
    int p, i, flag;
    size_t len;
    int item1, item2;
    if(_vec == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	VectorItemsNum (_vec,&len);
    for (p = 1; p <= len / 2; p++)
    {
        for (i = p - 1; i < len - p; i++)
        {
            VectorGet(_vec, i, &item1);
            VectorGet(_vec, i + 1, &item2);
            if(item1 > item2)
            {
       	VectorSet(_vec, i, item2);
       	VectorSet(_vec, i + 1, item1);
       	flag = 1;
            }
	 }
        if(flag == 0)
        {
       	return ERR_OK;
        }
        flag = 0;
        for (i = len - p - 1; i >= p; i--)
        {
            VectorGet(_vec, i, &item1);
            VectorGet(_vec, i - 1, &item2);
            if(item1 < item2)
            {
       	VectorSet(_vec, i, item2);
       	VectorSet(_vec, i - 1, item1);
       	flag = 1;
            }
        }
        if(flag == 0)
        {
       	return ERR_OK;
        }
	 flag = 0;
    }
}
ADTErr BubbleSort(Vector* _vec)
{
int i;
int j;
size_t len;
int item1;
int item2;
int flag = 0;

	if(_vec == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum (_vec,&len);
	
	for (i = 0; i < len - 1; i++)
        {
        	for(j = 0; j < len - i -1; j++)
        	{
        		VectorGet(_vec, j, &item1);
        		VectorGet(_vec, j + 1, &item2);
        		
       			if(item1 > item2)
       			{
       				VectorSet(_vec, j, item2);
       				VectorSet(_vec, j + 1, item1);
       				flag = 1;
       			}
       	}
       	if(flag == 0)
       	{
       		return ERR_OK;
       	}
      		flag = 0;
        }
      
return ERR_OK;
}

int main()
{
int i;
int baseArr[ARR_SIZE];
int bubbleArr[ARR_SIZE];
int shakeArr[ARR_SIZE];
int insertArr[ARR_SIZE];
int quickArr[ARR_SIZE];
int shellArr[ARR_SIZE];
int selectionArr[ARR_SIZE];
int mergeArr[ARR_SIZE];
int countingArr[ARR_SIZE];
int radixArr[ARR_SIZE];
clock_t start_t, end_t, total_t, start_t2, end_t2, total_t2,
	start_t3, end_t3, total_t3, start_t4, end_t4, total_t4,
	total_t5;
Vector* vecPtr;
int nDigits = 0, size = ARR_SIZE;
	for (i = size; i > 0; i = i/10)
	{
		nDigits++;
	}

	vecPtr = VectorCreate(ARR_SIZE, 50);
	for (i = 0; i < ARR_SIZE; i++)
	{
		baseArr[i] =  rand()%ARR_SIZE;
	}
	memcpy(bubbleArr, baseArr, sizeof(baseArr));
	for (i = 0; i < ARR_SIZE; i++)
	{
		VectorAdd (vecPtr, bubbleArr[i]);
	}
	memcpy(shakeArr, baseArr, sizeof(baseArr));
	memcpy(insertArr, baseArr, sizeof(baseArr));
	memcpy(quickArr, baseArr, sizeof(baseArr));
	memcpy(shellArr, baseArr, sizeof(baseArr));
	memcpy(selectionArr, baseArr, sizeof(baseArr));
	memcpy(mergeArr, baseArr, sizeof(baseArr));
	memcpy(countingArr, baseArr, sizeof(baseArr));
	memcpy(radixArr, baseArr, sizeof(baseArr));
/*start_t = clock();
BubbleSort(vecPtr);
end_t = clock();
total_t = end_t - start_t;
printf("Bubble Total time: %f\n", (float)total_t/ 1000000  );
VectorPrint(vecPtr);
VectorDestroy (vecPtr);
/*----------------------------------------
vecPtr = VectorCreate(ARR_SIZE, 50);	
	
	for (i = 0; i < ARR_SIZE; i++)
	{
		VectorAdd (vecPtr, shakeArr[i]);
	}
start_t2 = clock();
ShakeSort(vecPtr);
end_t2 = clock();
total_t2 = end_t2- start_t2;
printf("Shake Total time: %f\n", (float)total_t2/ 1000000  );
VectorPrint(vecPtr);
VectorDestroy (vecPtr);
---------------------------------------
vecPtr = VectorCreate(ARR_SIZE, 50);	
for (i = 0; i < ARR_SIZE; i++)
	{
		VectorAdd (vecPtr, insertArr[i]);
	}
start_t3 = clock();
InsertionSort(vecPtr);
end_t3 = clock();
total_t3 = end_t3- start_t3;
printf("Insert Total time: %f\n", (float)total_t3/ 1000000  );
VectorPrint(vecPtr);
VectorDestroy (vecPtr);
/*----------------------------------------
vecPtr = VectorCreate(ARR_SIZE, 50);	
for (i = 0; i < ARR_SIZE; i++)
	{
		VectorAdd (vecPtr, quickArr[i]);
	}
start_t4 = clock();
QuickSort(vecPtr);
end_t4 = clock();
total_t4 = end_t4- start_t4;
printf("Quick Total time: %f\n", (float)total_t4/ 1000000  );
VectorPrint(vecPtr);
VectorDestroy (vecPtr);


vecPtr = VectorCreate(ARR_SIZE, 50);	
for (i = 0; i < ARR_SIZE; i++)
	{
		VectorAdd (vecPtr, shellArr[i]);
	}
start_t4 = clock();
ShellSort(vecPtr);
end_t4 = clock();
total_t5 = end_t4- start_t4;
printf("Shell Total time: %f\n", (float)total_t5/ 1000000  );
VectorPrint(vecPtr);
VectorDestroy (vecPtr);

vecPtr = VectorCreate(ARR_SIZE, 50);	
for (i = 0; i < ARR_SIZE; i++)
	{
		VectorAdd (vecPtr, selectionArr[i]);
	}
start_t4 = clock();
SelectionSort(vecPtr);
end_t4 = clock();
total_t5 = end_t4- start_t4;
VectorPrint(vecPtr);
printf("Shell Total time: %f\n", (float)total_t5/ 1000000  );
VectorDestroy (vecPtr);
vecPtr = VectorCreate(ARR_SIZE, 50);	
for (i = 0; i < ARR_SIZE; i++)
	{
		VectorAdd (vecPtr, mergeArr[i]);
	}
start_t4 = clock();
MergeSort(vecPtr);
end_t4 = clock();
total_t5 = end_t4- start_t4;
VectorPrint(vecPtr);
printf("Merge Total time: %f\n", (float)total_t5/ 1000000  );
VectorDestroy (vecPtr); 

vecPtr = VectorCreate(ARR_SIZE, 50);	

for (i = 0; i < ARR_SIZE; i++)
	{
		VectorAdd (vecPtr, countingArr[i]);
	}
start_t4 = clock();
CountingSort(vecPtr, ARR_SIZE);
end_t4 = clock();
total_t5 = end_t4- start_t4;
VectorPrint(vecPtr);
printf("Counting Total time: %f\n", (float)total_t5/ 1000000  );
VectorDestroy (vecPtr);*/
vecPtr = VectorCreate(ARR_SIZE, 50);	

for (i = 0; i < ARR_SIZE; i++)
	{
		VectorAdd (vecPtr, radixArr[i]);
	}
start_t4 = clock();
RadixSort(vecPtr, nDigits);
end_t4 = clock();
total_t5 = end_t4- start_t4;
VectorPrint(vecPtr);
printf("Radix Total time: %f\n", (float)total_t5/ 1000000  );
VectorDestroy (vecPtr);

}

