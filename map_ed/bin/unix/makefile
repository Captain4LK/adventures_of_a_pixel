CC = gcc
CFLAGS+=-lSDL2_mixer -lm -Wall

game: main.o 
	gcc -o aop_maped $^ -L../../SoftLK-lib/lib/unix/ -lSLK -lm -lSDL2 -lSDL2_mixer -lGL -Wall
	chmod +x aop_maped 
	mv aop_maped ../../../bin/

main.o: ../../src/main.c
	$(CC) -O3 -c $< $(CFLAGS) 

clean:
	rm *.o ../../../bin/aop_maped
