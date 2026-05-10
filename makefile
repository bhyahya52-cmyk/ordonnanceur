all: clean ordonnanceur

ordonnanceur: main.o processus.o
	gcc -Wall -Wextra -std=c99 -o ordonnanceur main.o processus.o

main.o: main.c processus.h scheduler.h
	gcc -Wall -Wextra -std=c99 -I. -c main.c -o main.o

processus.o: processus.c processus.h
	gcc -Wall -Wextra -std=c99 -I. -c processus.c -o processus.o

clean:
	del /F *.o ordonnanceur.exe 2>nul || rm -f *.o ordonnanceur

run: ordonnanceur
	./ordonnanceur config.txt
