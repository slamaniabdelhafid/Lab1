CC=g++
CFLAGS=-c -Wall
LFLAGS=-o

all: main

main: main.o bmp.o
	$(CC) $(LFLAGS) main main.o bmp.o

main.o: main.cpp bmp.h
	$(CC) $(CFLAGS) main.cpp

bmp.o: bmp.cpp bmp.h
	$(CC) $(CFLAGS) bmp.cpp

clean:
	rm -f *.o main