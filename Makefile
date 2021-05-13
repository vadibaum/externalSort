CC=g++

CFLAGS=-c -Wall -std=c++11

all: main.o exsorting.o randomstrings.o
	$(CC) main.o exsorting.o randomstrings.o -o ./externalSort

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

exsorting.o: exsorting.cpp
	$(CC) $(CFLAGS) exsorting.cpp

randomstrings.o: randomstrings.cpp
	$(CC) $(CFLAGS) randomstrings.cpp

clean:
	rm -rf *.o externalSort
