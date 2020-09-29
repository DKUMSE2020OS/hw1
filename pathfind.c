#include "sish.h"
//$PATH 를 받아와 strtok로 나눠준다.
int pathfind() {
	char* path;
	char* token;
	char pathtemp2[100] = { 0, };

	path = getenv("PATH");
	token = strtok(path, ":");
	pathpart[0] = token;

	int i = 1;
	while (token != NULL) {
		token = strtok(NULL, ":");
		pathpart[i] = token;
		i++;
	}

	return i-1;
}
