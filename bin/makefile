CC = gcc
CFLAGS+=-lm -Wall

game: main.o player.o map.o modes.o
	gcc -o game $^ -L../SoftLK-lib/lib/ -lSLK -lm -lSDL2 -lGL -Wall
	chmod +x game

main.o: ../src/main.c ../src/config.h ../src/player.h ../src/map.h ../src/modes.h
	$(CC) -O3 -c $< $(CFLAGS) 

player.o: ../src/player.c ../src/config.h ../src/player.h ../src/map.h ../src/modes.h
	$(CC) -O3 -c $< $(CFLAGS) 

map.o: ../src/map.c ../src/config.h ../src/player.h ../src/map.h ../src/modes.h
	$(CC) -O3 -c $< $(CFLAGS) 

modes.o: ../src/modes.c ../src/config.h ../src/player.h ../src/map.h ../src/modes.h
	$(CC) -O3 -c $< $(CFLAGS) 

clean:
	rm *.o game
