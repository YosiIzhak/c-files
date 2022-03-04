#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#define NUM_THREADS 50
int global = 0;
void *Change_s(void *threadid) 
{
   int j, local = 0;
   long tid;
   tid = (long)threadid;
   for( j = 0; j < 10000; j++ ) 
   {
  	 local++;
   	global++;
   	printf("Thread ID, %ld   %d\n", tid, local);
  	 printf("global %d\n", global);
  	}
   pthread_exit(NULL);
}
int main ()
{
   pthread_t threads[NUM_THREADS];
   int rc;
   int i, j;
    int ret;
   
   		for( i = 0; i < NUM_THREADS; i++ ) 
   		{
     		 rc = pthread_create(&threads[i], NULL, Change_s, (void*)i);
      		if (rc) 
      		{
        		return 1;
      		}
   		}
   	
   for (i = 0; i < NUM_THREADS; i++) 
   {
       pthread_join(threads[i], NULL);
   }
   pthread_exit(NULL);
}
