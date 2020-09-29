#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int spacecount(char *a, char b);

int main() {
	// Variables
	struct stat statbuf; 		
	pid_t pid; 			
	char input[1000], temp[1000];
	char *env, *tok, *inputtok1, *inputtok2, *inputtok3, *inputtok4;			
	char newtok[100][100];	
	int i, j, k, space;
	
	while(1) {
		// Getting the Input & Shell Prompt Printing
		memset(input, 0, sizeof(input));
		printf("[%s@%s]# ", getenv("USER"), getenv("PWD"));
		fgets(input, sizeof(input) - 1, stdin);
		input[strlen(input) - 1] = '\0';
		
		if(!strncmp(input, "quit", strlen(input))) {
			return -1;
			break;
		}

		// PATH Tokenizing
		env = getenv("PATH");
		strcpy(temp, env);
		tok = strtok(temp, ":");
		i = 0;
		while (tok != NULL) {
			strcpy(newtok[i], tok);
			strcat(newtok[i], "/");
			tok = strtok(NULL, ":");
			i++;
		}

		// Combining with Input Array
		for(j = 0; j<11; j++) {
			strcat(newtok[j], input);

			// Finding the Space for Multiple Input Parameters
			if(strstr(newtok[j], " ") != NULL) {
				strtok(newtok[j], " ");
			}

			//  Detecting Directories & PATH
			if (stat(newtok[j], &statbuf) != -1) {
				k = j;
				break;
			}
		}

		space = spacecount(input, ' ');

		// fork() for generating child process
		pid = fork();

		if (pid == -1) {
			perror("fork error\n");
			return -1;
		} else if (pid != 0) {
			pid = wait(NULL); 
		} else {
			switch (space) {
				case 0: 
					execle(newtok[k], input, (char *)0, NULL);
					exit(0);
					break;
				case 1: 
					inputtok1 = strtok(input, " ");
					inputtok2 = strtok(NULL, " ");
					execle(newtok[k], inputtok1, inputtok2, (char *)0, NULL);
					exit(0);
					break;
				case 2:
					inputtok1 = strtok(input, " ");
					inputtok2 = strtok(NULL, " ");
					inputtok3 = strtok(NULL, " ");
					execle(newtok[k], inputtok1, inputtok2, inputtok3, (char *)0, NULL);
					exit(0);
					break;
				case 3:
					inputtok1 = strtok(input, " ");
					inputtok2 = strtok(NULL, " ");
					inputtok3 = strtok(NULL, " ");
					inputtok4 = strtok(NULL, " ");
					execle(newtok[k], inputtok1, inputtok2, inputtok3, inputtok4, (char *)0, NULL);
					exit(0);
					break;
				default:
					printf("Nothing!\n");
			}
		}
	}
}

int spacecount(char *a, char b)
{
 	int count=0;

	for(int i = 0; a[i] != '\0'; i++) {
		if(a[i] == b) {
			count++;
		} else {
			continue;
		}
	}
	return count;
}
