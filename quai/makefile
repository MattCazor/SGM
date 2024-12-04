
mainquai.o : mainquai.c
	gcc -g -Wall -c mainquai.c

menuquai.o : menuquai.c
	gcc -g -Wall -c menuquai.c

quai.o : quai.c
	gcc -g -Wall -c quai.c

bateau.o : bateau.c
	gcc -g -Wall -c bateau.c

mainquai : mainquai.o menuquai.o quai.o bateau.o
	gcc -o mainquai mainquai.o menuquai.o quai.o bateau.o


clean :
	rm mainquai *.o

