

mainquai.o : mainquai.c
	gcc -g -Wall -c mainquai.c

quai.o : quai.c
	gcc -g -Wall -c quai.c

bateau.o : bateau.c
	gcc -g -Wall -c bateau.c

sauvegarde.o : sauvegarde.c
	gcc -g -Wall -c sauvegarde.c

mainquai : mainquai.o quai.o bateau.o sauvegarde.o
	gcc -o mainquai mainquai.o quai.o bateau.o sauvegarde.o


clean :
	rm -rf *.o

