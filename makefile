sish : sish.o pathfind.o cmdextract.o
	gcc -o sish sish.o pathfind.o cmdextract.o

sish.o : sish.c
	gcc -c -o sish.o sish.c

pathfind.o : pathfind.c
	gcc -c -o pathfind.o pathfind.c

cmdextract.o : cmdextract.c
	gcc -c -o cmdextract.o cmdextract.c

clean :
	rm *.o sish
