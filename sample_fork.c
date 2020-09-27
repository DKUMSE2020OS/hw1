#include <stdio.h>
#include <unistd.h>

int main(){

pid_t p;
int i;

for (i=0;i<10;i++){
p=fork();
execve();
if(p==-1){printf("fail");}
else if(p==0){printf("my child is make pid: %d, num:%d \n",getpid(),i);break;}

else{printf("parent: %d,%d \n",getpid(),i);}
}


return 0;
}
