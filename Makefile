CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99

OBJ = main.o
HDR = ./lib/kmp.h ./lib/shiftand.h ./lib/bruta.h

all: tp3

tp3: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o tp3

main.o: main.c $(HDR)
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm -f $(OBJ) tp3 input.out