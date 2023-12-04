CC =g++
CFLAGS = -Wall -g
EXEC = main
CPP = src/*.cpp
CPPFLAGS = -std=c++20

all:
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $(EXEC) $(CPP) 
clean:
	rm -rf $(EXEC)
