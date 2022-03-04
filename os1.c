#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <sys/wait.h>
int g_var=0;
main()
{
	int pid;
	int i, j;
	int  l_var=0;
	sleep(10);
	pid = fork();
	
	
	if (pid>0) 
	{
    	/* Parent code */
    	for(i = 0; i< 30; i++)
    	{
			++g_var; 
			printf(" %d g_p", g_var);
			++l_var; 
			printf(" %d l_p", l_var);
		}
		wait(NULL);
  		sleep(10);
    } 
    else 
    {
		for(i = 0; i< 30; i++)
    	{
			/* Child code */
			--g_var;
       	 printf(" %d g_child", g_var);
        	--l_var; 
       	 printf(" %d l_child", l_var);
       	}
       	sleep(20);
	}     
	
}

