#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
 
#define SIZE 100
#define TRUE 1

int value = 0; 
sem_t mutex; 
sem_t full;  
sem_t empty; 
 
void *Producer(void *_a) 
{
   
    while (TRUE)
    {
        sem_wait(&empty); 
        sem_wait(&mutex); 
        
        value++;
        printf("%d ", value);
        sem_post(&mutex); 
        sem_post(&full); 
    }
}
 
void *Consumer(void *_a) 
{
   
    while (TRUE) 
    {
        sem_wait(&full);
        sem_wait(&mutex); 
        value--;
        printf("%d ",  value);
        sem_post(&mutex); 
        sem_post(&empty); 
    }
}
 
int main()
{
	pthread_t producer;
	pthread_t producer1;
	pthread_t producer2;
	pthread_t consumer;
	
	sem_init(&mutex,0,1);
	sem_init(&empty,0,SIZE);
	sem_init(&full,0,0);
	
	pthread_create(&producer, NULL, Producer, NULL); 
	pthread_create(&producer1, NULL, Producer, NULL); 
	pthread_create(&producer2, NULL, Producer, NULL); 
    pthread_create(&consumer, NULL, Consumer, NULL);  
      
	
	pthread_join(producer, NULL);
	pthread_join(producer1, NULL);
	pthread_join(producer2, NULL);
	pthread_join(consumer, NULL);
	
	sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);
	
}




