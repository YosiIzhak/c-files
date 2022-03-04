#include<stdio.h>
#include <time.h>
#define SWAP(x, y)\
{            \
	int temp;\
	temp = x;\
	x = y;\
	y = temp;\
}
#define ARR_SIZE 10
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void mySort(int(*func_ptr)(int,int),int arr[], int size)
{
	 clock_t start_t, end_t, total_t;
	 int order = 1;
	 register int i, j;
	 
	 srand(time(NULL));
      	 
      	 start_t = clock();
   	 printf("Starting of the program, start_t = %ld\n", start_t);
   	 
      	for (i = 0; i < ARR_SIZE-1; i++)
	{
		for (j = 0; j < ARR_SIZE - i -1; j++)
		{
			order = 1;
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
	end_t = clock();
   	printf("End of the big loop, end_t = %ld\n", end_t);
      	
	for(i = 0; i < ARR_SIZE; i++)
	{
		printf("%d ", arr[i]);
	}
	total_t = (double)(end_t - start_t);
	printf("Total time taken by CPU: %f\n", (float)total_t/ 1000000 );
}
void sortDefine()
{
	 clock_t start_t, end_t, total_t;
	 int order = 0, arr[ARR_SIZE];
	 register int i, j;
	 srand(time(NULL));
      	 
      	 start_t = clock();
   	 printf("Starting of the program, start_t = %ld\n", start_t);
   	 for(i=0;i<ARR_SIZE;i++)
   	 {
                arr[i]=(rand()%5000);
         }
      	for (i = 0; i < ARR_SIZE-1; i++)
	{
		order = 1;
		for (j = 0; j < ARR_SIZE - i -1; j++)
		{
			
			if (arr[j] > arr[j+1]) 
			{
				SWAP(arr[j], arr[j+1]);
				order = 0;
			}
		}
		if (order)
		{
			break;
		}
	}
	end_t = clock();
   	printf("End of the big loop, end_t = %ld\n", end_t);
   
   	
   	
	for(i = 0; i < ARR_SIZE; i++)
	{
		printf("%d ", arr[i]);
	}
	total_t = (double)(end_t - start_t);
	printf("Total time taken by CPU: %f\n", (float)total_t/ 1000000  );
}
int main( int argc, char **argv )
{
 int i, arr[] = {2,5,7,8,2,1,9,12,5,81};
 
 /*if( argc >= 2 )
  {
      	  printf("The argument supplied is %s\n", argv[1]);
      	printf("%d\n",atoi(argv[1]) * atoi(argv[2]));
 }*/
mySort(SortBySize, arr, ARR_SIZE);
/*sortDefine();*/
return 0;
}
