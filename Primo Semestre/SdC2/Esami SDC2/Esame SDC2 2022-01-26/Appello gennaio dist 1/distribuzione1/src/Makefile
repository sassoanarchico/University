CFLAGS=-m32 -g -Wall
all: server client

server: server.c common.h common.c
	gcc $(CFLAGS) -o server server.c common.c -pthread

client: client.c common.h common.c
	gcc $(CFLAGS) -o client client.c common.c

.PHONY: clean
clean:
	rm -f server client
