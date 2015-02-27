all:
	gcc item.c bstree.c main.c -o prog -g -Wall

gdb:
	gdb prog -silent

valgrind:
	valgrind ./prog --leak-check=full	

run:
	./prog

debug:
	gcc item.c bstree.c main.c -o prog -g -Wall -D NDEBUG
