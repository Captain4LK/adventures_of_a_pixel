CC = gcc -O3 -s -flto
CFLAGS+=-lSDL2_mixer -lm -Wall
HEADERS = ../../src/config.h ../../src/util.h
DEPENDENCIES = main.o util.o ressource.o config.o assets.o mode.o map_list.o map.o game.o

game: $(DEPENDENCIES)
	gcc -o adventuresofapixel $^ -L../../SoftLK-lib/lib/unix/ -lSLK -lm -lSDL2 -lSDL2_mixer -lGL -Wall
	chmod +x adventuresofapixel
	mv adventuresofapixel ../../../bin/

main.o: ../../src/main.c ../../src/ressource.h ../../src/assets.h ../../src/mode.h ../../src/map_list.h $(HEADERS)
	$(CC) -c $< $(CFLAGS) 

util.o: ../../src/util.c $(HEADERS)
	$(CC) -c $< $(CFLAGS) 

config.o: ../../src/config.c $(HEADERS)
	$(CC) -c $< $(CFLAGS) 

game.o: ../../src/game.c ../../src/game.h $(HEADERS)
	$(CC) -c $< $(CFLAGS) 

map.o: ../../src/map.c ../../src/map.h ../../src/ressource.h ../../src/assets.h $(HEADERS)
	$(CC) -c $< $(CFLAGS) 

mode.o: ../../src/mode.c ../../src/mode.h ../../src/map_list.h ../../src/map.h ../../src/assets.h $(HEADERS)
	$(CC) -c $< $(CFLAGS) 

ressource.o: ../../src/ressource.c ../../src/ressource.h $(HEADERS)
	$(CC) -c $< $(CFLAGS) 

map_list.o: ../../src/map_list.c ../../src/map_list.h ../../src/ressource.h ../../src/assets.h $(HEADERS)
	$(CC) -c $< $(CFLAGS) 

assets.o: ../../src/assets.c ../../src/assets.h ../../src/ressource.h $(HEADERS)
	$(CC) -c $< $(CFLAGS) 

clean:
	rm *.o ../../../bin/adventuresofapixel
