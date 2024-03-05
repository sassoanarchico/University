CC=gcc
CCOPTS=--std=gnu99 -g -Wall 
AR=ar


BINS=mmap_example

# OBJS=
# HEADERS=
# LIBS=

%.o:	%.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@  $<

.phony: clean all


all:	$(BINS) $(LIBS)

mmap_example: mmap_example.c $(OBJS)
	$(CC) $(CCOPTS) -o $@ $^

clean:
	rm -rf *.o *~ $(LIBS) $(BINS)
