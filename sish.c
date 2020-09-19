#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
//#include <readline/readline.h>#i want to make auto complete but im not sudo
//#include <readline/history.h>

char* head;
char* arg_1;
char* arg_2;
char* arg_3;
char* arg_4;
char* arg_5;


void p_pwd();
void p_time();
void tok_str(char text[]);
void run(char text[]);

int main(){
	pid_t pid;
	pid_t status;
	char string_shell[BUFSIZ];

	while(1){
		char* value = getenv("USER");
		char* now_dir = getcwd(NULL,BUFSIZ);

		printf("%s # [younghwan's shell] ",now_dir);

		fgets(string_shell,BUFSIZ,stdin);
		tok_str(string_shell);	

		if (strcmp(head,"cd")==0){chdir(arg_1);continue;}
		else if(strcmp(head,"pwd")==0){p_pwd();continue;}
		else if(strcmp(head,"users")==0){printf("%s = %s",head,value);continue;}
		else if(strcmp(head,"time")==0){p_time();continue;}
		else if(strcmp(head,"exit")==0){printf("bye\n");break;}

		pid = fork();

		if(pid == -1){printf("sorry fork error");break;}
		else if(pid == 0){execlp(head,head,arg_1,arg_2,arg_3,arg_4,arg_5,(char*)0);break;}
		else{waitpid(pid,&status,0);}




	}


return 0;
}


void p_pwd(){

char path[BUFSIZ];
getcwd(path,255);
printf("%s\n",path);
}

void p_time(){
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	printf("now time : %s ",asctime(timeinfo));

}

void tok_str(char text[]){
	
	text[strlen(text)-1]='\0';
	head = strtok(text," ");
	arg_1 = strtok(NULL," ");
	arg_2 = strtok(NULL," ");
	arg_3 = strtok(NULL," ");
	arg_4 = strtok(NULL," ");
	arg_5 = strtok(NULL," ");


}



