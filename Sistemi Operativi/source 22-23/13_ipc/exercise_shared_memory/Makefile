CC=gcc
CCOPTS=--std=gnu99 -g -Wall 
LDOPTS=-lrt -lpthread
BINS=producer consumer

.phony: clean all

all:	$(BINS)

producer: producer.c $(LIBS)
	$(CC) $(CCOPTS) -o $@ $^ $(LDOPTS)
consumer: consumer.c $(LIBS)
	$(CC) $(CCOPTS) -o $@ $^ $(LDOPTS)

clean:
	rm -rf *.o *~ $(LIBS) $(BINS)
