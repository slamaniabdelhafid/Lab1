CC = g++
CFLAGS = -Wall -Wextra -O2

all: bmp_lab

bmp_lab: main.cpp
	$(CC) $(CFLAGS) -o bmp_lab main.cpp

clean:
	rm -f bmp_lab
	rm -f rotated_clockwise.bmp rotated_counterclockwise.bmp blurred.bmp
