#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "info_and_initialize.h"
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <readline/readline.h>#i want to make auto complete but im not sudo
//#include <readline/history.h>

#define WRITE_END 1
#define READ_END 0


char* head;
char* arg_1;
char* arg_2;
char* arg_3;
char* arg_4;
char* arg_5;

////make pipe
char* first_cmd=NULL;
char* second_cmd=NULL;
char* frarg=NULL;
char* secarg=NULL;
char* pip_arg=NULL;
char history[100][100];


//function name
void p_pwd();
void p_time();
void tok_str(char text[]);


//main function
void main(){
	pid_t pid;
	pid_t status;
	//local var
	char string_shell[BUFSIZ];
	int fd[2];
	int his_num=0;
	int i=0;

//print manual and ignore interrupt signal
	info();
	signal(SIGINT,SIG_IGN);
	signal(SIGQUIT,SIG_IGN);
	signal(SIGTSTP,SIG_IGN);

	//run while roop
	while(1){
		char* value = getenv("USER");
		char* now_dir = getcwd(NULL,BUFSIZ);

		printf("%s # [younghwan's shell] ",now_dir);
////////////////////////////////////////////////init and print
		fgets(string_shell,BUFSIZ,stdin);
		strcpy(history[his_num],string_shell);
		tok_str(string_shell);
		///tokenizing input string

		if (head == NULL){continue;}
////////////////////////////////if only enter ignore


///////////////////////////////make pipe signal preprocessing

		if(arg_1 != NULL && strcmp(arg_1,"|")==0){
			first_cmd = head;
			second_cmd = arg_2;
			secarg = arg_3;	
			pip_arg = arg_1;
		}
		if(arg_2 != NULL && strcmp(arg_2,"|")==0){
			first_cmd = head;
			frarg = arg_1;
			second_cmd = arg_3;
			secarg = arg_4;	
			pip_arg = arg_2;
		}
////////////////////////////////////////////////////

//////////////////////////////////////////////////outer signal
		if (strcmp(head,"cd")==0){chdir(arg_1);his_num++;continue;}
		else if(strcmp(head,"pwd")==0){p_pwd();his_num++;continue;}
		else if(strcmp(head,"users")==0){printf("%s = %s\n",head,value);his_num++;continue;}
		else if(strcmp(head,"time")==0){p_time();his_num++;continue;}
		else if(strcmp(head,"quit")==0){printf("Thank you This is younghwan's shell Bye~\n");break;}
		else if(strcmp(head,"history")==0){
			for(i=0;i<his_num;i++){
			printf("%s\n",history[i]);
			}
		
		}
//////////////////////////////////////////////////////////make pipe
		else if(pip_arg!=NULL && strcmp(pip_arg,"|")==0){
			pipe(fd);
			pid = fork();

			if (pid==0){
				dup2(fd[WRITE_END],STDOUT_FILENO);
				close(fd[READ_END]);////must close input and output
				close(fd[WRITE_END]);
				execlp(first_cmd,first_cmd,frarg,(char*)NULL);
				printf("fail exe '%s'\n",first_cmd);
				exit(1);
			}
			else{
				pid=fork();

				if(pid==0){
					dup2(fd[READ_END],STDIN_FILENO);
					close(fd[WRITE_END]);//must!!!
					close(fd[READ_END]);
					execlp(second_cmd,second_cmd,secarg,(char*)NULL);
					printf("fail  exe '%s'\n",second_cmd);
					exit(1);
				}
				else{
					int stat;
					close(fd[READ_END]);
					close(fd[WRITE_END]);
					waitpid(pid,&stat,0);
				}
			
			}
		
		}
//////////////////////////////////////////////////////////////another command		
		else{
			
			pid = fork();
			if(pid == -1){printf("sorry fork error");break;}
			else if(pid == 0){execlp(head,head,arg_1,arg_2,arg_3,arg_4,arg_5,(char*)0);break;}
			else{waitpid(pid,&status,0);}

}

his_num++;
	}
//////////////////////////////////////////////////////////////////////

return;
}

///////////////////////////////////////////////return pwd
void p_pwd(){

char path[BUFSIZ];
getcwd(path,255);
printf("%s\n",path);
}
/////////////////////////////////////////////return time
void p_time(){
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	printf("now time : %s ",asctime(timeinfo));

}
/////////////////////////////////////////////////return token input
void tok_str(char text[]){
	
	text[strlen(text)-1]='\0';
	head = strtok(text," ");
	arg_1 = strtok(NULL," ");
	arg_2 = strtok(NULL," ");
	arg_3 = strtok(NULL," ");
	arg_4 = strtok(NULL," ");
	arg_5 = strtok(NULL," ");

}



