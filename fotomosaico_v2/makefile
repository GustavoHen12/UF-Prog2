#GRR20190485 Gustavo Henrique da Silva Barbosa
 
CFLAGS = -Wall
LDFLAGS = -lm

all: mosaico

mosaico: mosaico.o image.o directory.o
	gcc -o mosaico mosaico.o image.o directory.o $(CFLAGS) $(LDFLAGS)

mosaico.o: mosaico.c image.h directory.h
	gcc -c mosaico.c -o mosaico.o $(CFLAGS)

image.o: image.c image.h
	gcc -c image.c $(CFLAGS)

directory.o: directory.c directory.h
	gcc -c directory.c $(CFLAGS)

clean:
	-rm -f *~ *.o
	
purge: clean
	-rm -f mosaico
