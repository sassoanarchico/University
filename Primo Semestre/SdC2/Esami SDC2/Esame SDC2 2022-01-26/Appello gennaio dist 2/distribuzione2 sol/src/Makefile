CFLAGS=-m32 -g -Wall
all: producer consumer

producer: producer.c common.h common.c
	gcc $(CFLAGS) -o producer producer.c common.c -lpthread -lrt

consumer: elaborator.c common.h common.c
	gcc $(CFLAGS) -o elaborator elaborator.c common.c -lpthread -lrt

.PHONY: clean
clean:
	rm -f producer elaborator
