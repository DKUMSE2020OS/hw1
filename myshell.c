#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#define DEL1 " "
#define DEL2 ":"
#define slash "/"
#define q  "quit"
#define BUFSIZE 100

int main(){
	// stat function struct
	struct stat fstat_buf;

	// get command
	char input[100];
	int ret;

	// variavle for fork
	pid_t pid;

	// variable for get args
	char *token;
	char *next_ptr;
	char *args[20];
	int k =0;

	// variable for pipe
	int fd1[2];
	int fd2[2];
	char pipe_buf[BUFSIZE];        
	char pipe_buf2[BUFSIZE];
	char PWD_buf[BUFSIZE];

	// variable for get  path
	char *path[30];
	char path_file_name[100];
	char *path_buf = getenv("PATH");
	char *p_token;
	char *p_next_ptr;
	int p_num=0;

	// get paths
	p_token = strtok_r(path_buf,DEL2,&p_next_ptr);
	while(p_token){
		path[p_num] = p_token;
		p_token = strtok_r(NULL,DEL2,&p_next_ptr);
		p_num++;}
	path[p_num] = "/home/jaeseo16/info";
	path[p_num+1] = "/home/jaeseo16/test_prog";

        //start simple shell 
	printf("Let's start simple shell\n");
	while(1){
                
		printf("%s$ ",getenv("PWD"));	

		//get command
		input[0]='\0';
		fgets(input, sizeof(input)-1,stdin);
		input[strlen(input) -1] = '\0';


		if(strcmp(q,input)==0) break;

		//make pipe and fork
		pipe(fd1);
		pipe(fd2);
		pid= fork();

		//fork error
		if(pid == -1){
			perror("fork error");
			return 0;}
		//child process
		else if(pid ==0){

			close(fd2[0]);
			close(fd1[0]);

			token = strtok_r(input,DEL1,&next_ptr);    

			while(token){
				args[k] = token;
				token = strtok_r(NULL,DEL1,&next_ptr);
				k++;}

			args[k]=NULL;
			// command cd
			if(strcmp("cd",args[0])==0){
				if(k==1){
					write(fd1[1],getenv("HOME"),BUFSIZE);
					write(fd2[1],"1",BUFSIZE); 
					exit(0);}  
				else if(k==2){  
					write(fd1[1],args[1],BUFSIZE);
					write(fd2[1],"2",BUFSIZE);
					exit(0);
				}
				else{printf("ERROR INPUT\n");
					exit(0);}     
			}
			// command clear
			else if(strcmp("clear",args[0])==0){
				write (1, "\033[2J\033[1;1H", 11);
				exit(0);
			}
			else{  
			// execute most of commands
				for(int i =0; i<p_num+2;i++){
					path_file_name[0] ='\0';
					strcat(path_file_name,path[i]);
					strcat(path_file_name,slash);
					strcat(path_file_name,args[0]);


					if(stat(path_file_name,&fstat_buf)==0){
						if(execve(path_file_name, args, NULL)==-1){
                                                printf("Error execute\n");}
					}
				}
                                printf("command [%s] not exist\n",args[0]);
                                exit(0);
                               
			}
		}
		// parent process
		else{

			close(fd2[1]);
			close(fd1[1]);
			wait(0);     

			// change PWD
			read(fd2[0],pipe_buf2,BUFSIZE);
			read(fd1[0],pipe_buf,BUFSIZE);
			if(pipe_buf2[0] =='1'){
				setenv("PWD",pipe_buf,1);
				chdir(pipe_buf);
			}
			else if(pipe_buf2[0] == '2'){
				if(chdir(pipe_buf)==0){
					PWD_buf[0] ='\0';
					strcat(PWD_buf,getenv("PWD"));
					strcat(PWD_buf,slash);
					strcat(PWD_buf,pipe_buf);
					setenv("PWD",PWD_buf,1);}
			}      
		}

	} 
	return 0;
}
