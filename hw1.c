#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
 {
	printf("----------shell_by_hyunjin_32144165----------\n");
	pid_t pid;
	char in_command[100];
	char *tmp_command[100];
	char *par_command[100];

	char *env_paths;
	char *tmp_paths[100];
	char *par_paths[100][100];
	char *paths_tokenizer;
	int paths_counter = 0;

	env_paths = getenv("PATH");
	strcpy(tmp_paths, env_paths);
	paths_tokenizer = strtok(tmp_paths, ":");

	while(1)  // PATH tokenizing ":"
	{
		if(paths_tokenizer == NULL) break;
		strcpy(par_paths[paths_counter], paths_tokenizer);
		paths_tokenizer = strtok(NULL, ":");	
		paths_counter++;
//		printf("tokenizer is %s\n",paths_tokenizer);
	}

	while(1)  // Command 
	{
		fgets(tmp_command, sizeof(in_command), stdin);
		strcpy(par_command, strtok(tmp_command, "\n"));
		if(strcmp(par_command,"quit")==0)
			{
				printf("----------quit----------\n");
				break;
			}
		else
		{
			pid = fork();
			if(pid < 0)
			{
				printf("fork error");
				return 0;
			}
			else if(pid==0)
			{
				for(int i=1;i<paths_counter-1;i++)
				{
		//			strcat(par_paths[i],"/");
		//			strcat(par_paths[i],par_command);
				//	execve(par_paths[i],par_command, 0);
				//	execlp(par_command,par_command, 0);
		//			printf("pid is %d, i is %d\n", getpid(), i);
					printf("command is %s\n", par_command);
		//			printf("%s**\n", par_paths[i]);
		//			execlp(in_command, in_command, 0);
					printf("execute!!\n");
					execlp(par_command, par_command, 0);
				}
				exit(0);			
			}
			else 
			{
				wait(0);
			}
		}
	}
return 0;
}
