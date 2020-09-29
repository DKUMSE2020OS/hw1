CC = gcc
TARGET = HW1_exe 
OBJECTS = test5.o HandleCommand.o HandlePath.o HandleQuit.o



all : $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

clean :
	rm *.o HW1_exe


