CC = gcc -Wall -g

all: server client

server: common.h server.c io.c
	$(CC) -o server server.c io.c

client: common.h client.c io.c
	$(CC) -o client client.c io.c

.PHONY: clean

clean:
	rm -f server client
