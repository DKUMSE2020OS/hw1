#include "sish.h"

int main() {
	printf("\nStarting Simple Shell\n");
	char commandline[50] = { 0, };
	char realpath[100] = { 0, };
	char* command;
	char* option;
	int pathnum;
	int pid;

	printf("Shell's Working Directory : \t%s\n", getenv("PWD"));
	printf("Shell's Execution Time : \t%s\n", getenv("TIME"));
	printf("Shell's User Name : \t\t%s\n", getenv("USER"));

	//PATH 받아와서 쪼개놓기
	pathnum = pathfind();

	//SiSH while loop
	while (1) {
		printf("\n\nInput Command line : ");
		scanf(" %[^\n]s", commandline);

		//입력이 quit이면 프로그램 종료
		if (strcmp(commandline, "quit") == 0) {
			printf("End of Simple Shell. ByeBye.\n\n");
			break;
		}

		//입력받은 command line 분리
		command = strtok(commandline, " ");
		printf("Command :\t%s\n", commandline);
		option = strtok(NULL, " ");
		printf("Option :\t%s\n", option);

		//환경변수의 실제 경로 추출 및 저장
		strcpy(realpath, cmdextract(pathnum, command));

		pid = fork();

		//Parent process
		if (pid > 0)
			wait(NULL);

		//Child process
		else if (pid == 0) {
			if (option == '\0')
				execve(realpath, &command, NULL);
			else
				execl(realpath, command, option, NULL);
			printf("\n");
			exit(0);
		}

		else if (pid == -1) {
			perror("fork error : ");
			exit(0);
		}
	}
	return 0;
}