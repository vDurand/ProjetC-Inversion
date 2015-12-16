CC=gcc
INC_DIR= include/
CFLAGS= -Wall -pedantic -g

install: all clean

all: invertion

invertion: arbre.o table.o
	$(CC) arbre.o table.o -o invertion

arbre.o: arbre.c arbre.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -c arbre.c

table.o: table.c table.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -c table.c

clean:
	rm -f *.o
