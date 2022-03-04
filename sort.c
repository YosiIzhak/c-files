#include<stdio.h>

#define ARR_SIZE 10
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int SortBySize(int _a, int _b)
{
	if (_a > _b)
	{
		return 1;
	}
	return 0;
}
int SortBySizeOppsite(int _a, int _b)
{
	if (_a < _b)
	{
		return 1;
	}
	return 0;
}
int SortByLastDigit(int _a, int _b)
{
	if ((_a % 10) > (_b % 10))
	{
		return 1;
	}
	return 0;
}
int SortByLastDigitOppsite(int _a, int _b)
{
	if ((_a % 10) < (_b % 10))
	{
		return 1;
	}
	return 0;
}

void mySort(int(*func_ptr)(int,int),int arr[], int size)
{
	int order = 0;
	register int i, j;
	   	 
      	for (i = 0; i < ARR_SIZE-1; i++)
	{
		order = 1;
		for (j = 0; j < ARR_SIZE - i -1; j++)
		{
			if (func_ptr(arr[j], arr[j+1])) 
			{
				swap(&arr[j], &arr[j+1]);
				order = 0;
			}
		}
		if (order)
		{
			break;
		}
	}
	      	
	for(i = 0; i < ARR_SIZE; i++)
	{
		printf("%d ", arr[i]);
	}
	
}

int main( int argc, char **argv )
{
 int i, arr[] = {2,5,7,8,2,1,9,12,5,81};
 
 
mySort(SortByLastDigitOppsite, arr, ARR_SIZE);

return 0;
}
