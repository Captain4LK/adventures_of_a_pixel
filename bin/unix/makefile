CC = gcc
CFLAGS+=-lSDL2_mixer -lm -Wall

game: main.o player.o map.o modes.o
	gcc -o adventuresofapixel $^ -L../../SoftLK-lib/lib/unix/ -lSLK -lm -lSDL2 -lSDL2_mixer -lGL -Wall
	chmod +x adventuresofapixel
	mv adventuresofapixel ../

main.o: ../../src/main.c ../../src/config.h ../../src/player.h ../../src/map.h ../../src/modes.h ../../src/sound.h
	$(CC) -O3 -c $< $(CFLAGS) 

player.o: ../../src/player.c ../../src/config.h ../../src/player.h ../../src/map.h ../../src/modes.h ../../src/sound.h
	$(CC) -O3 -c $< $(CFLAGS) 

map.o: ../../src/map.c ../../src/config.h ../../src/player.h ../../src/map.h ../../src/modes.h ../../src/sound.h
	$(CC) -O3 -c $< $(CFLAGS) 

modes.o: ../../src/modes.c ../../src/config.h ../../src/player.h ../../src/map.h ../../src/modes.h ../../src/sound.h
	$(CC) -O3 -c $< $(CFLAGS) 

clean:
	rm *.o ../adventuresofapixel
