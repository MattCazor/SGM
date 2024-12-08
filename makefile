SGM : mainquai.o quai.o bateau.o sauvegarde.o libisentlib.a
	gcc -Wall -o SGM mainquai.o quai.o bateau.o sauvegarde.o libisentlib.a -lm -lglut -lGL -lX11

mainquai.o : quai/mainquai.c
	gcc -g -Wall -c quai/mainquai.c

quai.o : quai/quai.c
	gcc -g -Wall -c quai/quai.c

bateau.o : quai/bateau.c
	gcc -g -Wall -c quai/bateau.c

sauvegarde.o : quai/sauvegarde.c
	gcc -g -Wall -c quai/sauvegarde.c

# mainquai : mainquai.o quai.o bateau.o sauvegarde.o
# 	gcc -o mainquai mainquai.o quai.o bateau.o sauvegarde.o

libisentlib.a: BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o 
	ar rcs libisentlib.a BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o

BmpLib.o: menu/BmpLib.c menu/BmpLib.h menu/OutilsLib.h
	gcc -Wall -O2 -c menu/BmpLib.c

ESLib.o: menu/ESLib.c menu/ESLib.h menu/ErreurLib.h
	gcc -Wall -O2 -c menu/ESLib.c

ErreurLib.o: menu/ErreurLib.c menu/ErreurLib.h
	gcc -Wall -O2 -c menu/ErreurLib.c

GfxLib.o: menu/GfxLib.c menu/GfxLib.h menu/ESLib.h
	gcc -Wall -O2 -c menu/GfxLib.c -I/usr/include/GL

OutilsLib.o: menu/OutilsLib.c menu/OutilsLib.h
	gcc -Wall -O2 -c menu/OutilsLib.c

SocketLib.o: menu/SocketLib.c menu/SocketLib.h
	gcc -Wall -O2 -c menu/SocketLib.c

ThreadLib.o: menu/ThreadLib.c menu/ThreadLib.h
	gcc -Wall -O2 -c menu/ThreadLib.c

WavLib.o: menu/WavLib.c menu/WavLib.h menu/OutilsLib.h
	gcc -Wall -O2 -c menu/WavLib.c -Wno-unused-result


clean:
	rm -f *~ *.o
	

	
