CC=gcc
INC_DIR= include/
LIBS=-Llib/MODULE_IMAGE/
CFLAGS= -Wall -pedantic -g

install: all clean

all: test_table

invertion: arbre.o table.o
	$(CC) arbre.o table.o -o invertion

test_arbre: arbre.o test_arbre.o
	$(CC) arbre.o test_arbre.o -o test_arbre

test_table: table.o test_table.o
	$(CC) table.o test_table.o -o test_table $(LIBS) -limage

arbre.o: arbre.c arbre.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -c arbre.c

test_arbre.o: test_arbre.c arbre.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -c test_arbre.c

table.o: table.c table.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -c table.c

test_table.o: test_table.c table.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -c test_table.c

clean:
	rm -f *.o
