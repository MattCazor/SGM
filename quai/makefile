mainquai : mainquai.o quai.o
	gcc -o mainquai mainquai.o quai.o

mainquai.o : mainquai.c
	gcc -g -Wall -c mainquai.c

quai.o : quai.c
	gcc -g -Wall -c quai.c

clean :
	rm mainquai *.o

