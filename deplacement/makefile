portGFX: portGFX.o libisentlib.a quai.o bateau.o sauvegarde.o
#	gcc -Wall portGFX.o -o portGFX libisentlib.a -lm -lglut -lGL -lX11
# Sous macOS, commenter la ligne de commande ci-dessus (en mettant un # au debut)
# et de-commenter la ligne de commande ci-apres :
	gcc -Wall portGFX.o -o portGFX quai.o bateau.o sauvegarde.o libisentlib.a -lm -framework OpenGL -framework GLUT

portGFX.o: portGFX.c GfxLib.h BmpLib.h ESLib.h
	gcc -Wall -c portGFX.c

libisentlib.a: BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o VectorLib.o WavLib.o
	ar r libisentlib.a BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o VectorLib.o WavLib.o
	ranlib libisentlib.a

BmpLib.o: BmpLib.c BmpLib.h OutilsLib.h
	gcc -Wall -O2 -c BmpLib.c

ESLib.o: ESLib.c ESLib.h ErreurLib.h
	gcc -Wall -O2 -c ESLib.c

ErreurLib.o: ErreurLib.c ErreurLib.h
	gcc -Wall -O2 -c ErreurLib.c

GfxLib.o: GfxLib.c GfxLib.h ESLib.h
#	gcc -Wall -O2 -c GfxLib.c -I/usr/include/GL
# Sous macOS, commenter la ligne de commande ci-dessus (en mettant un # au debut)
# et de-commenter la ligne de commande ci-apres :
	gcc -Wall -O2 -c GfxLib.c -Wno-deprecated-declarations

OutilsLib.o: OutilsLib.c OutilsLib.h
	gcc -Wall -O2 -c OutilsLib.c

SocketLib.o: SocketLib.c SocketLib.h
	gcc -Wall -O2 -c SocketLib.c

ThreadLib.o: ThreadLib.c ThreadLib.h
	gcc -Wall -O2 -c ThreadLib.c


# Source specifique CPU x86/x86-64 fourni uniquement pour information
#VectorLib.o: VectorLib.c VectorLib.h
#	gcc -Wall -O2 -c VectorLib.c -msse3

WavLib.o: WavLib.c WavLib.h OutilsLib.h
#	gcc -Wall -O2 -c WavLib.c -Wno-unused-result
# Sous macOS, commenter la ligne de commande ci-dessus (en mettant un # au debut)
# et de-commenter la ligne de commande ci-apres :
	gcc -Wall -O2 -c WavLib.c

zip:
	zip libisentlib.zip *.[ch] *.bmp *.pdf makefile
#	tar -cvzf libisentlib.tgz *.[ch] *.bmp *.pdf makefile

clean:
	rm -f *~ *.o

deepclean: clean
	rm -f portGFX portGFXTortue libisentlib.a

quai.o : ../quai.c
	gcc -g -Wall -c ../quai.c

bateau.o : ../bateau.c
	gcc -g -Wall -c ../bateau.c

sauvegarde.o : ../sauvegarde.c
	gcc -g -Wall -c ../sauvegarde.c
