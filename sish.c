#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>

struct input{
	char str[200];
	char inputdel[1];
	char buf[1024];
	time_t time_now;
};
struct input input;

struct path{
	char *path;
	char pathdel[1];
	char fullpath[100][200];
};
struct path path;

char strdiv[100][100];
char* argv[100];
struct passwd *user_pw;

void GetInput(){

	//Get user name.
	uid_t uid = geteuid();	
	struct passwd *pw = getpwuid(uid);

	//Get current date and time.
	time(&input.time_now);

	//Get current directory.
	if(getcwd(input.buf,1024) == NULL)
		printf("Error : Failed to get current directory");

	//Get hostname
	char host_name[80];
	if(gethostname(host_name, sizeof(host_name))){
		printf("Error : Failed to get hostname!\n");
	}
	printf("\nHost name : %s", host_name);

	//shell prompt
	if(pw)
        	printf("\ncurrent time : %s username : %s,    current dir : %s,    input : ", ctime(&input.time_now), pw->pw_name, input.buf);

	//Get user input.
	fgets(input.str, sizeof(input.str), stdin);
	
}

void GetPath(){
	
	//Save all environment paths into path variable.
	path.path = getenv("PATH");
	
}

void DivideInput(){

	//Divide user input with " " -> "ls -a -l" can be divided with blank.
	//Use string tokenizer.

	strcpy(input.inputdel, " ");
	char *token = strtok(input.str, input.inputdel);
	int i = 0;

	while(token != NULL){

		strcpy(strdiv[i], token);
		token = strtok(NULL, " ");
		i++;
	}
}

void FillFullPath(char *ProgName){

	//Divide environment pathes.
	strcpy(path.pathdel, ":");
	char *token = strtok(path.path, path.pathdel);
	int i = 0;

	while(token != NULL){

		//Copy path into fullpath array.
		strcpy(path.fullpath[i], token);
		//Put "/" at the back of path.
		strcat(path.fullpath[i], "/");
		//Put program name at the back of "/".
		strcat(path.fullpath[i], ProgName);

		token = strtok(NULL, ":");
		i++;
	}
}

int CheckStat(){

	struct stat fstat_buf;
	int ret;
	int valid = 0;
	
	//Check all paths to know where is the program.
	for(int i=0; i<100; i++){

		if(path.fullpath[i][0] == 0){
			break;
		}

		ret = stat(path.fullpath[i], &fstat_buf);
		
		if(ret == 0){
		//If found, return the index of the array.
			valid = 1;
			return i;
		}
	}
	if(valid == 0){
		printf("Error : There is no such program!");
	}
}

void CopyStrdiv(){
	
	//Copy divided input data to pointer string.
	//-> Because execve's argument vector can read only pointer type string array.

	for(int i=0; i<100; i++){
		argv[i] = strdiv[i];
		
                if(strdiv[i][0] == 0){
                        argv[i] = 0;
			
                        for(int j=0; argv[i-1][j] != 0; j++){
				
				//If newline char is found at the back, change it to null.
                                if(argv[i-1][j] == '\n'){
                                        argv[i-1][j] = '\0';
                                        break;
                                }
                        }
                        break;
                }
        }
}

int main(void){

	int res;
	int status;
	int pid;

	while(1){

		res = fork();
		
		//if fork's return value is 0, it is child process.
		if(res == 0){

			GetInput();
		
			if(input.str[0] == '\n'){
				printf("Error : User typed nothing!\n");
				exit(0);
			}		

			//If the user input "quit", child process terminates with returing 1 to parent process.
			if(strcmp(input.str, "quit\n") == 0)
                       		
				exit(1);
		
			GetPath();
			
			if(path.path[0] == 0){
				printf("Error : Failed to get environment path!");
				
				exit(0);
			}
	
			DivideInput();
	
			CopyStrdiv();

			FillFullPath(argv[0]);
			
			execve(path.fullpath[CheckStat()], argv, NULL);
			
			//If child process successfully terminates, return 0 to parent process.
			return 0;
		}

		//If fork's return value is bigger than 0, it is child process's pid -> parent process
		else if(res > 0){

			//Parent process waits until child process terminates.
			wait(&status);

			//WSTOPSIG can know what child process returned.
			if(WSTOPSIG(status) != 0)
				return 0;
		
		//If fork's return value is -1, it means fork is failed.
		}
		else{
			printf("Error : fork failed!\n");
		}
	}
}
