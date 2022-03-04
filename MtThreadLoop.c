// this is demo code and not productuion code dont ever use it in production
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


void * ThreadFunctionA(void *arg)
{
	puts("Hello world from threadA\n");
	for (int i = 0; i<500; i++) {
		sleep(1);
		printf("A");
		fflush(stdout);
	}
		printf("\n");
	puts("Exiting thread A\n");
	return(NULL);
}

void * ThreadFunctionB(void *arg)
{
	puts("Hello world from threadB\n");
	for (int i = 0; i<500; i++) {
		sleep(1);
		printf("B");
		fflush(stdout);
	}
		printf("\n");
	puts("Exiting thread B\n");
	return(NULL);
}

void * ThreadFunctionC(void *arg)
{
	puts("Hello world from threadC\n");
	for (int i = 0; i<500; i++) {
		sleep(1);
		printf("C");
		fflush(stdout);
	}
		printf("\n");
	puts("Exiting thread C\n");
	return(NULL);
}

void * ThreadFunctionD(void *arg)
{
	puts("Hello world from threadD\n");
	for (int i = 0; i<500; i++) {
		sleep(1);
		printf("D");
		fflush(stdout);
	}
		printf("\n");
	puts("Exiting thread D\n");
	return(NULL);
}

void * ThreadFunctionStam(void *arg)
{
	puts("Hello world from thread stam\n");
	for (int i = 0; i<500; i++) {
		sleep(1);
		printf("0");
		fflush(stdout);
	}
		printf("\n");
	puts("Exiting thread stam\n");
	return(NULL);
}

int main()
{
	int retval;
	pthread_t ThreadA,ThreadB,ThreadC,ThreadD,ThreadS1,ThreadS2;
	void * Arg = NULL;
	puts("Hello world!\n");
	puts("CreatingThread A\n");
	retval = pthread_create(&ThreadA, NULL, ThreadFunctionA, Arg);
	puts("Thread A Created\n");
	printf("retval from pthread_create is %i \n", retval);
	printf("pthread_t is %lu \n", ThreadA);
	puts("CreatingThread B\n");
	retval = pthread_create(&ThreadB, NULL, ThreadFunctionB, Arg);
	puts("Thread B Created\n");
	printf("retval from pthread_create is %i \n", retval);
	printf("pthread_t is %lu \n", ThreadB);
	puts("CreatingThread C\n");
	retval = pthread_create(&ThreadC, NULL, ThreadFunctionC, Arg);
	puts("Thread C Created\n");
	printf("retval from pthread_create is %i \n", retval);
	printf("pthread_t is %lu \n", ThreadC);
	puts("CreatingThread D\n");
	retval = pthread_create(&ThreadD, NULL, ThreadFunctionD, Arg);
	puts("Thread D Created\n");
	printf("retval from pthread_create is %i \n", retval);
	printf("pthread_t is %lu \n", ThreadD);
	puts("CreatingThread stam1\n");
	retval = pthread_create(&ThreadS1, NULL, ThreadFunctionStam, Arg);
	puts("Thread stam1 Created\n");
	printf("retval from pthread_create is %i \n", retval);
	printf("pthread_t is %lu \n", ThreadS1);
	puts("CreatingThread stam2\n");
	retval = pthread_create(&ThreadS2, NULL, ThreadFunctionStam, Arg);
	puts("Thread stam2 Created\n");
	printf("retval from pthread_create is %i \n", retval);
	printf("pthread_t is %lu \n", ThreadS2);

	for (int i = 0; i<500; i++) {
		sleep(1);
		printf("*");
		fflush(stdout);
	}
		printf("\n");
	puts("Press ENTER to exit\n");
	getchar();
	puts("Exiting Program\n");
	return 0;
}
