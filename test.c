#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>



int main()
{
   pid_t pid;
   char *data1[] = {"ls", "-al", 0};


   pid = fork();

   if(pid < 0) {
      perror("fork error occur!");
      return -1;
   }

   else if(pid == 0) {
      // execve("path", "option", NULL)
      execve("/bin/ls", data1, NULL);
      exit(0);
   }

   else {
      wait(NULL);
   }

 
   return 0;
}

