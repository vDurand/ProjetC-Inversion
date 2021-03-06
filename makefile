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

all: libimage inversion trivial graphdata

# Compilation library image
libimage: 
	$(CC) -I$(INC) -o image.o $(SRC)image.c -c
	ar -rv $(LIB)libimage.a image.o

# Compilation methode trivial
trivial: table.o trivial.o
	$(CC) table.o trivial.o -o $(BIN)trivial -L$(LIB) -limage -lm

# Compilation inversion avec arbre
inversion: table.o arbre.o inversion.o
	$(CC) table.o arbre.o inversion.o -o $(BIN)inversion -L$(LIB) -limage -lm

# Compilation temps d execution
graphdata: table.o arbre.o graphdata.o
	$(CC) table.o arbre.o graphdata.o -o $(BIN)graphdata -L$(LIB) -limage -lm

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

inversion.o: $(SRC)inversion.c
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)inversion.c

graphdata.o: $(SRC)graphdata.c
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)graphdata.c

arbre.o: $(SRC)arbre.c
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)arbre.c

test_arbre.o: $(SRC)test_arbre.c
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)test_arbre.c -lm

clean:
	rm -f *.o
