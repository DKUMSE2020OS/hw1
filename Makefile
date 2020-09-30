Sish: HW1.o
	gcc -o Sish HW1.o

HW1.o: HW1.c
	gcc -c -o HW1.o HW1.c

clean:
	rm *.o Sish 
