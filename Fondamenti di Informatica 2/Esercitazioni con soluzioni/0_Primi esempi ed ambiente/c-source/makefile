CC = gcc
CFLAGS = -Wall -g
SRCS = bubblesort.c
OBJS = $(SRCS:.c=.o)
HEADERS = $(SRCS:.c=.h)
MAIN = main

all:    $(MAIN); chmod u+x $(MAIN)

	

$(MAIN): $(OBJS) $(MAIN).c
	$(CC) $(CFLAGS) -o $(MAIN) $(MAIN).c $(OBJS)

%.o: %.c %.h
	gcc -c $(CFLAGS) $*.c -o $*.o

clean:
	$(RM) *.o $(MAIN)
