CC = gcc
CFLAGS = -no-pie -fno-stack-protector

SRC = draconophobia.c
BIN = draconophobia

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(BIN)

clean:
	rm -f $(BIN)
