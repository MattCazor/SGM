mainquai : mainquai.o menuquai.o quai.o
	gcc -o mainquai mainquai.o menuquai.o quai.o

mainquai.o : mainquai.c
	gcc -g -Wall -c mainquai.c

menuquai.o : menuquai.c
	gcc -g -Wall -c menuquai.c

quai.o : quai.c
	gcc -g -Wall -c quai.c

clean :
	rm mainquai *.o

