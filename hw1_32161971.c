//현재까지 구현
//fork, while에서 quit으로 마무리
//ls같은거 실행 시, 주소 하나씩 합쳐서 실행 가능한지 확인해보기
//현재 주소 파악

//구현이 필요한 내용
//현재 directory 옮기기
//vi print.c


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

void IntroComment();
void OutroComment();
int PathDiv(char* pathVar, char pathVarDiv[][1000]);
char* Parameter(char* inputStr);
void printCurDir(char* currentDir);
void InputOneLine(char* inputStr);
void Exit(char* inputStr);

void Fork(char* inputArgv, int count, char pathVarDiv[][1000], char* inputStr, char* currentDir);
void ForkError();
void ForkChild(char* inputArgv, int count, char pathVarDiv[][1000], char* inputStr, char* currentDir);
void ForkParent();
void RunProgram(char* currentDir, char* inputStr, char* inputArgv, int count, char pathVarDiv[][1000]);

int main(int argc, char* argv[])
{
    char currentDir[1000];
    char pathVar[1000];
    char inputStr[100];
    char pathVarDiv[100][1000];
    char* inputArgv;

    IntroComment();

    int count = PathDiv(pathVar, pathVarDiv);

    RunProgram(currentDir, inputStr, inputArgv, count, pathVarDiv);

    return 0;
}

int PathDiv(char* pathVar, char pathVarDiv[][1000]) {
    char* pathVarTemp = getenv("PATH");
    strcpy(pathVar, pathVarTemp);
    int count = 0;
    char* ptr = strtok(pathVar, ":");
    while (ptr != NULL)
    {
        strcpy(pathVarDiv[count], ptr);
        ptr = strtok(NULL, ":");
        count++;
    }
    return count;
}
char* Parameter(char* inputStr) {
    if (strchr(inputStr, ' ') != NULL) {
        char* temp = strtok(inputStr, " ");
        strcpy(inputStr, temp);
        return strtok(NULL, " ");
    }
    else {
        return NULL;
    }
}
void printCurDir(char* currentDir) {
    char buf[255];
    getcwd(buf, 255);
    strcpy(currentDir, buf);
    printf("%s>> ", currentDir);
}
void InputOneLine(char* inputStr) {
    char* line = NULL;
    size_t size = 0;
    ssize_t ret;
    if ((ret = getline(&line, &size, stdin)) != -1) {
        strcpy(inputStr, strtok(line, "\n"));
    }
}
void Exit(char* inputStr) {
    if (strcmp(inputStr, "quit") == 0) {
        OutroComment();
        exit(1);
    }
}

void Fork(char* inputArgv, int count, char pathVarDiv[][1000], char* inputStr, char* currentDir) {
    int pid = fork();
    if (pid < 0)
    {
        ForkError();
    }
    else if (pid == 0)
    {
        ForkChild(inputArgv, count, pathVarDiv, inputStr, currentDir);
    }
    else
    {
        ForkParent();
    }
}
void ForkError() {
    fprintf(stderr, "Fork Failed");
    exit(-1);
}
void ForkChild(char* inputArgv, int count, char pathVarDiv[][1000], char* inputStr, char* currentDir) {
    struct stat sb;
    char* data[] = { "/bin/sh", inputArgv, 0 };

    for (int i = 0; i <= count; i++)
    {
        char* a;
        if (i != count) {
            a = strcat(strcat(pathVarDiv[i], "/"), inputStr);
        }
        else {
            a = strcat(strcat(currentDir, "/"), inputStr);
        }

        if (stat(a, &sb) != -1) {
            execve(a, data, NULL);
            printf("EXECVE NO\n");
        }
    }
    printf("NO!!\n");
}
void ForkParent() {
    wait(NULL);
}
void RunProgram(char* currentDir, char* inputStr, char* inputArgv, int count, char pathVarDiv[][1000]) {
    while (1) {
        printCurDir(currentDir);

        InputOneLine(inputStr);

        Exit(inputStr);

        inputArgv = Parameter(inputStr);

        Fork(inputArgv, count, pathVarDiv, inputStr, currentDir);
    }
}
void IntroComment() {
    printf("2020 Operating Systems\n");
    printf("Homework #1. Simple MyShell\n\n");
}
void OutroComment() {
    printf("\nThank you!");
    printf("\nHeejo Park, 32161971\nMobile Systems Engineering.\n");

    return;
}
