#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "HW1.h"



int CheckingQuit(char* parsedCommand[]) {

    int result = 0;

    if(strcmp(parsedCommand[0], "quit") == 0) {
            result = 1;
            printf("Goodbye...\n");
    }

    return result;
}
