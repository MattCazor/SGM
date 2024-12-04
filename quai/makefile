<<<<<<< HEAD
mainquai : mainquai.o quai.o
	gcc -o mainquai mainquai.o quai.o
=======
>>>>>>> cf781ca6bbe3038ec4aa8bcc0a5288d677fa3a34

mainquai.o : mainquai.c
	gcc -g -Wall -c mainquai.c

quai.o : quai.c
	gcc -g -Wall -c quai.c

bateau.o : bateau.c
	gcc -g -Wall -c bateau.c

sauvegarde.o : sauvegarde.c
	gcc -g -Wall -c sauvegarde.c

mainquai : mainquai.o menuquai.o quai.o bateau.o sauvegarde.o
	gcc -o mainquai mainquai.o menuquai.o quai.o bateau.o sauvegarde.o


clean :
	rm mainquai *.o

