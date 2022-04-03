all: rpg

rpg: Player.o Game.o Lab08_main.o Player.h Game.h UNIXBOARD.h
	gcc Player.o Game.o Lab08_main.o -o rpg

Player.o: Player.c
	gcc -Wall -c Player.c

Game.o: Game.c
	gcc -Wall -c Game.c

Lab08_main.o: Lab08_main.c
	gcc -Wall -c Lab08_main.c

clean:
	rm -f *.o
