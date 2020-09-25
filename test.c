//Modified 0921
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int res;
	
	for(int i = 0; i < 10; i++)
	{
		res = fork();
		
		if(res < 0)
		{
			printf("Fork failed\n");
			return 0;
		}
		else if (res == 0)
		{	//Child Work
			printf("c[%d}\n", getpid());
			return 0;
		}
		else
		{	//Parent Work
			printf("p[%d] -> c[%d]\n", getpid(), res);
		}
	}
	
	return 0;
}
