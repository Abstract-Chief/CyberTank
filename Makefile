GCC=gcc
FLAGS=-Wall -g -Werror
LIBS=-lncurses
MODULE_FILE=game_module.c

game: main.c $(MODULE_FILE)
	gcc -Wall -g main.c $(MODULE_FILE) $(FLAGS) -o game $(LIBS)
	./game
