CC=gcc
CFLAGS=-Wall -g

SRC=dictionary.c
EXE=dictionary

build:
	$(CC) $(CFLAGS) $(SRC) -o $(EXE)

run: build
	./$(EXE)

check-memory-leaks: build
	valgrind --leak-check=full -v ./$(EXE)

clean:
	rm $(EXE) *.txt
