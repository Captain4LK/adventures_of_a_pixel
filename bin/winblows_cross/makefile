CC = i686-w64-mingw32-gcc
CFLAGS+=-lSDL2_mixer -lmingw32 -lSDL2main -lSDL2 -lopengl32 -mwindows -Wall

game: main.o player.o map.o modes.o
	$(CC) -o adventuresofapixel $^ -L../../SoftLK-lib/lib/winblows_cross -lSLK $(CFLAGS)
	mv adventuresofapixel.exe ../

main.o: ../../src/main.c ../../src/config.h ../../src/player.h ../../src/map.h ../../src/modes.h ../../src/sound.h
	$(CC) -O3 -c $< $(CFLAGS) 

player.o: ../../src/player.c ../../src/config.h ../../src/player.h ../../src/map.h ../../src/modes.h ../../src/sound.h
	$(CC) -O3 -c $< $(CFLAGS) 

map.o: ../../src/map.c ../../src/config.h ../../src/player.h ../../src/map.h ../../src/modes.h ../../src/sound.h
	$(CC) -O3 -c $< $(CFLAGS) 

modes.o: ../../src/modes.c ../../src/config.h ../../src/player.h ../../src/map.h ../../src/modes.h ../../src/sound.h
	$(CC) -O3 -c $< $(CFLAGS) 

clean:
	rm *.o game
