#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

#define ARR_SIZE 30000

int MySearch (int _arr[], int _size, int _num)
{
	int index;
	int temp;
	
	if (_arr[_size -1] == _num)
	{
		return 1;
	}
	temp = _arr[_size -1];
	_arr[_size -1] = _num;
	for (index = 0; ; index++)
	{
		if (_arr[index] == _num)
		{
			if (index != (_size -1))
			{
				return 1;
			}
			else
			{
				_arr[_size -1] = temp;
				return 0;
			}	
		}
	}
	_arr[_size -1] = temp;
	return 0;
}

int simpleSearch (int _arr[], int _size, int _num)
{
	int  index;
	for (index = 0; index < _size; index++)
	{
		if (_arr[index] == _num)
		{
			return 1;
		}
	}
	return 0;
}
int main()
{
	clock_t start_t, end_t, total_t, total_t1;
	int i, arr[30000];
	for (i = 0; i < ARR_SIZE; i++)
	{
		arr[i] =  rand()%ARR_SIZE;
	}
	start_t = clock();
	printf("%d\n",simpleSearch(arr, ARR_SIZE, -9)); 
	end_t = clock();
	total_t = end_t - start_t;
	printf("search Total time: %f\n", (float)total_t/ 1000000  );
	start_t = clock();
	printf("%d\n",MySearch(arr, ARR_SIZE, -9)); 
	end_t = clock();
	total_t1 = end_t - start_t;
	printf("MySearch Total time: %f\n", (float)total_t1/ 1000000  );
	
}
