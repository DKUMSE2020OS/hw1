simple_shell_yh.exe : simple_shell.o info_and_initialize.o
	gcc -o simple_shell_yh.exe simple_shell.o info_and_initialize.o

simple_shell.o : simple_shell.c
	gcc -c -o simple_shell.o simple_shell.c

info_and_initialize.o : info_and_initialize.c
	gcc -c -o info_and_initialize.o info_and_initialize.c

clean :
	rm *.o simple_shell_yh.exe
