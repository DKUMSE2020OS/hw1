dongho_simple_shell : sish.o
	gcc -o dongho_simple_shell sish.o

sish.o : sish.c
	gcc -c -o sish.o sish.c

clean :
	rm *.o dongho_simple_shell
