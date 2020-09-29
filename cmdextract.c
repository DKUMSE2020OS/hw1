#include "sish.h"

const char* cmdextract(int num, char* cmd) {
	struct stat buf;
	int ret = 0;
	static char pathtemp[100] = { 0, };

	for (int i = 0; i < num; i++) {
		strcpy(pathtemp, pathpart[i]);
		strcat(strcat(pathtemp, "/"), cmd);
		ret = stat(pathtemp, &buf);
		if (ret == 0) {
			printf("Real Path :\t%s\n\n", pathtemp);
			break;
		}
	}

	return pathtemp;
}
