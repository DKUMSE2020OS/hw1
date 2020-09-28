Myshell.exe : myshell.o
	gcc -o Myshell.exe myshell.o

myshell.o : myshell.c
	   gcc -c -o myshell.o myshell.c

clean :
	rm *.o Myshell.exe
