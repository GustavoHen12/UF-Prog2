all: ortografia.c dicionario.c dicionario.h
	gcc ortografia.c dicionario.c -o ortografia -lm -Wall

clean:
	-rm -f *~ *.o
	
purge: clean
	-rm -f ortografia
