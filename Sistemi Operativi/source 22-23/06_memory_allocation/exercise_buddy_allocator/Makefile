CC=gcc
CCOPTS=--std=gnu99 -Wall -D_LIST_DEBUG_ -g #-D_VERBOSE_
AR=ar

OBJS=pool_allocator.o\
     linked_list.o\
     bit_map.o\
     buddy_allocator.o

HEADERS=linked_list.h  pool_allocator.h bit_map.h buddy_allocator.h

LIBS=libbuddy.a

BINS=test_exercise

.phony: clean all


all:	$(LIBS) $(BINS)

%.o:	%.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@  $<

libbuddy.a: $(OBJS) 
	$(AR) -rcs $@ $^
	$(RM) $(OBJS)

test_exercise: test_exercise.o $(LIBS)
	$(CC) $(CCOPTS) -o $@ $^ -lm

clean:
	rm -rf *.o *~ $(LIBS) $(BINS)
