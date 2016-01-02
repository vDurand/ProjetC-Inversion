# Durand Valentin
# Decembre 2015

CC=gcc
CFLAGS= -Wall -pedantic -g

# Folders
REF=./
SRC=$(REF)src/
INC=$(REF)include/
LIB=$(REF)lib/
BIN=$(REF)bin/
DOC=$(REF)doc/

install: all clean

all: libimage test_arbre

# Compilation library image
libimage: 
	$(CC) -I$(INC) -o image.o $(SRC)image.c -c
	ar -rv $(LIB)libimage.a image.o

# Compilation methode trivial
trivial: table.o trivial.o
	$(CC) table.o trivial.o -o $(BIN)trivial -L$(LIB) -limage -lm

# Compilation des tests
test_table: table.o test_table.o
	$(CC) table.o test_table.o -o $(BIN)test_table -L$(LIB) -limage

test_arbre: table.o arbre.o test_arbre.o
	$(CC) table.o arbre.o test_arbre.o -o $(BIN)test_arbre -L$(LIB) -limage -lm

# Compilation des objets
table.o: $(SRC)table.c
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)table.c

test_table.o: $(SRC)test_table.c
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)test_table.c

trivial.o: $(SRC)trivial.c
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)trivial.c -lm

arbre.o: $(SRC)arbre.c
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)arbre.c

test_arbre.o: $(SRC)test_arbre.c
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)test_arbre.c -lm

clean:
	rm -f *.o
