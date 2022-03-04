#include <stdio.h> 
#include <string.h>
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <sys/wait.h>



int main() {
     char command[200];
    char* arg[20];
 	int len, i = 1, status_code;
      const char delimiters[3] = " \n";
  	 
    while(1)
	{
     	printf("Enter command\n");
        fgets(command, 200, stdin);
     	
     	arg[0] = strtok(command, delimiters);
     	while (arg[i] != NULL)
     	{
     		 arg[i] = strtok(NULL, delimiters);
     		 i++;
     	}
     	arg[i]  = NULL;
        if (fork() != 0)
    	{
       	 	printf("parent code\n");
    		wait(NULL);
    		/*waitpid(-1, &status, 0);*/
    	}
    	else
    	{
    		status_code = execvp(arg[0], arg);
 			if (status_code == -1)
       		{
            	printf("Terminated Incorrectly\n");
            	return 1;
        	}
    		
    	}
    }
 
    return 0;
}






	
	

