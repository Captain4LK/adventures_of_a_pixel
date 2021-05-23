CC = gcc
CFLAGS+=-lSDL2_mixer -lm -Wall

game: main.o player.o map.o mode.o util.o
	gcc -o adventuresofapixel $^ -L../../SoftLK-lib/lib/unix/ -lSLK -lm -lSDL2 -lSDL2_mixer -lGL -Wall
	chmod +x adventuresofapixel
	mv adventuresofapixel ../../../bin/

main.o: ../../src/main.c ../../src/config.h ../../src/player.h ../../src/map.h ../../src/mode.h ../../src/sound.h ../../src/util.h
	$(CC) -O3 -c $< $(CFLAGS) 

player.o: ../../src/player.c ../../src/config.h ../../src/player.h ../../src/map.h ../../src/mode.h ../../src/sound.h ../../src/util.h
	$(CC) -O3 -c $< $(CFLAGS) 

map.o: ../../src/map.c ../../src/config.h ../../src/player.h ../../src/map.h ../../src/mode.h ../../src/sound.h ../../src/util.h
	$(CC) -O3 -c $< $(CFLAGS) 

mode.o: ../../src/mode.c ../../src/config.h ../../src/player.h ../../src/map.h ../../src/mode.h ../../src/sound.h ../../src/util.h
	$(CC) -O3 -c $< $(CFLAGS) 

util.o: ../../src/util.c ../../src/config.h ../../src/player.h ../../src/map.h ../../src/mode.h ../../src/sound.h ../../src/util.h
	$(CC) -O3 -c $< $(CFLAGS) 

clean:
	rm *.o ../../../bin/adventuresofapixel
