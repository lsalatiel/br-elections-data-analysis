CC =g++
CFLAGS = -Wall -g
EXEC = main
CPP = src/*.cpp src/electionslib/*.cpp
CPPFLAGS = -std=c++17

all:
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $(EXEC) $(CPP) 
clean:
	rm -rf $(EXEC)
