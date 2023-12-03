CC =g++
CFLAGS = -Wall -g
EXEC = main
CPP = src/*.cpp

all:
	$(CC) $(CFLAGS) -o $(EXEC) $(CPP) 
clean:
	rm -rf $(EXEC)
