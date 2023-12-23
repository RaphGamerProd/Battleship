# Seek for files in folders
vpath
vpath %.c src
vpath %.h include

CC = gcc

all: game clean doxy

boat.o: boat.c boat.h
	$(CC) -c $< -o $@

plate.o: plate.c plate.h
	$(CC) -c $< -o $@

game.o: game.c masterlib.h
	$(CC) -c $< -o $@

main.o: main.c
	$(CC) -c $< -o $@

# Création de la librairie statique
lib.a: boat.o plate.o game.o
	ar r lib.a $^
	
game: main.o lib.a
	$(CC) -fsanitize=address $^ -o $@

doxy:
	doxygen Doxyfile

# Delete all the object files
clean:
	rm -f *.o
