CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lncurses

SRC = magic_maze.c draw.c
BIN = magic_maze

$(BIN): $(SRC)
	$(CC) $(SRC) $(LDFLAGS) -o $(BIN)

clean:
	rm -f $(BIN)
