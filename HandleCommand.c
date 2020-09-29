// HandleCommand

#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "HW1.h"

void ParsingCommand(char rawCommand[], char* restCommand, char* parsedCommand[], int cCount) {

    parsedCommand[0] = strtok_r(rawCommand, " ", &restCommand);
    while(1) {
        parsedCommand[cCount] = strtok_r(NULL, " ", &restCommand);
        if(parsedCommand[cCount] == '\0') break;
        cCount++;
    }

}
