/*
OS
HW#1 Simple MyShell
MSE
32161570
Park Kitae
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

void c_handler(int sig)
{

    #ifdef DEBUG
        printf("Ctrl+c is disabled.\n");
    #endif
        printf("\n");
}

int main(int argc, char* argv[]){


    int i; 


    char line[255]; //Save  Line
    char command[100];  //Save Command
    char* n_command[255];
 
    char *env_path = getenv("PATH");    //getenv()
    
    char tmp_path[255];//PATH
    char* path;     
    char n_path[255]; 
 
    int n_arg = argc;
    

    printf("\n-----------------32161570 Park Kitae----------------\n\n");
    printf("\n-------------------Simple Myshell-------------------\n\n");
    printf("\n---------------------Start Now!---------------------\n\n");
    
    (void) signal(SIGINT,c_handler); //Ignore Ctrl+c
    
    while(1){	//Loop Start

        
        printf("Simple My Shell>>%s$ ",getenv("PWD"));	//Shell Prompt + Current Location

        //Read Command
        if((fgets(line,sizeof(line), stdin)) == NULL){
            perror("ERROR OCCURRED");
            exit(1);
        } 
        line[(sizeof(line)) - 1] = '\0'; //Delete '\n'

        //Parsing Arguments in Line
        n_command[0] = strtok(line, " "); 

        for(i=1; ;i++){
            if(!(n_command[i] = strtok(NULL, " ")))
                break;
                n_arg++;
            }
            //printf("argc = %d\n\n", n_arg);
            n_command[n_arg-1] = strtok(n_command[n_arg-1],"\n");
            n_command[n_arg] = (char*) NULL; //Delete '\n'

            strcpy(command, n_command[0]);    //Copy Command

            if(strcmp(command,"quit")==0){   //Quit
                printf("----------Simple MyShell quit.----------\n");
                return 0;
            }

        //PATH Parsing
        strcpy(tmp_path, env_path); // Add '/bin/'
        path = strtok(tmp_path, ":");

        //Attaching
        strcpy(n_path, path);
        strcat(n_path, "/");
        strcat(n_path, command);
        strcat(n_path, "");
       
        //FORK
        pid_t pid = fork();
         
        if(pid == -1){  //Fork Failed
            perror("Fork Failed.\n");
            return -1;
        } else if(pid == 0){    //Child Process 
            
            while(execve(n_path,n_command, NULL)== -1){
                
                if(!(path = strtok(NULL, ":")))
                    break;
                
                strcpy(n_path, path);
                strcat(n_path, "/");
                strcat(n_path, command);
                strcat(n_path, "");
                 
            }
            exit(0); 
        } else{       //Parent Process
            wait(0); 
        }
        
        n_arg = 1;
    }
    return 0;
}
