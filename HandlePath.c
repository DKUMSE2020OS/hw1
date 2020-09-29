// HandlePath.c

#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "HW1.h"


int ParsingPath(char* copyPath, char* rawPath, char* restPath, char* parsedPath[], char* Path[], int pCount, char* parsedCommand[]) {

    copyPath = getenv("PATH");
    rawPath = strdup(copyPath);
    parsedPath[0] = strtok_r(rawPath, ":", &restPath);
    Path[0] = strdup(parsedPath[0]);
    strcat(Path[0], "/");
    strcat(Path[0], parsedCommand[0]);

    while(1) {
        parsedPath[pCount] = strtok_r(NULL, ":", &restPath);
        if(parsedPath[pCount] == NULL) break;
        Path[pCount] = strdup(parsedPath[pCount]);
        //strcpy(tempArrayPath[pCount], parsedPath[pCount]);
        strcat(Path[pCount], "/");
        strcat(Path[pCount], parsedCommand[0]);
        pCount++;
    }

    return pCount;
}

