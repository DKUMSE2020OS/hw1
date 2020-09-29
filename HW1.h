// functions for HW1

#include <stdio.h>

void ParsingCommand(char rawCommand[], char* restCommand, char* parsedCommand[], int cCount);
int ParsingPath(char* copyPath, char* rawPath, char* restPath, char* parsedPath[], char* Path[], int pCount, char* parsedCommand[]);
int CheckingQuit(char* parsedCommand[]);
