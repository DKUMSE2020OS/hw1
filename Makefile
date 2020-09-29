Myshell : Myshell.o
	gcc -o Myshell Myshell.o

Myshell.o : Myshell.c
	gcc -c -o Myshell.o Myshell.c

clean :
	rm *.o Myshell
