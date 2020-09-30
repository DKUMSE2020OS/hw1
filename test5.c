//
//
//  Created by 변상운 on 2020/09/19.
//  Copyright © 2020 sangun. All rights reserved.
//

#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "HW1.h"



int main(int argc, char * argv[]) {
    
    pid_t pid;
    int cCount;         		// loop count for parsing input command
    int pCount;	        		// loop count for parsing PATH value
    int result;				// 1 when input is "quit", 0 when input is anything except "quit" 
    char rawCommand[50];            	// input command string
    char *restCommand = NULL;       	// rest command for strtok_r
    char *parsedCommand[50];        	// parsed string from rawCommand
    
    char *copyPath;    
    char *rawPath;                  	// raw PATH value
    char *restPath;          	    	// rest PATH value
    char *parsedPath[2000];          	// parsed string from PATH
    char *Path[200];		// location where executable file exist  ex) "/bin/ls" 




    printf("*******************************************************************\n");
    printf("*                     Simeple MyShell HW1                         *\n");
    printf("*                                           32162066 변상운       *\n");
    printf("*                                                                 *\n");
    printf("*******************************************************************\n");



    while(1)  {

        cCount = 1;
        pCount = 1;    

        //when there is NO input command
        if(argc <= 1) {

            fgets(rawCommand, sizeof(rawCommand), stdin); 
                
                // check whether input is "\n"
                if(strcmp(rawCommand, "\n") == 0) {			
		while(1) {
                    printf("please type proper command! \n");
                    fgets(rawCommand, sizeof(rawCommand), stdin);
                    if(strcmp(rawCommand, "\n") != 0) break;
                }
            }

            rawCommand[strlen(rawCommand) - 1] = '\0';
            ParsingCommand(rawCommand, restCommand, parsedCommand, cCount);    // Parsing rawCommand to parsedCommand
        }
        
        //when there are input command
        else {
            for (int i = 0; i < argc-1; i++) {
                parsedCommand[i] = argv[i + 1];
            }       
                argc = 1;
        }
    

        //Parseing rawPath to parsedPath and make tempArrayPath  
        pCount = ParsingPath(copyPath, rawPath, restPath, parsedPath,Path, pCount, parsedCommand);     

        //Checking input command is "quit"
        result = CheckingQuit(parsedCommand);
        if(result == 1) break;    


        pid = fork();

        if(pid < 0) {
            perror("fork error occur!");
            return -1;
        }
        
        else if (pid == 0) {      // child case
            for(int i = 1; i<pCount; i++) {
                execve(Path[i], parsedCommand, NULL);
             }
            exit(0);
        }
        
        else {                   // parent case
            wait(NULL);
            printf("--------------------------------------------------------------\n");
        }
    }
    return 0;
}
