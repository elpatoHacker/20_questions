tq.o: tq.c
	gcc -Wall -Werror -std=c11 -c tq.c
game: game.c
	gcc -Wall -Werror -std=c11 tq.o game.c -o game
clean: 
	rm -f game tq.o