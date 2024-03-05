CC=gcc
LIBS=-lglut -lGLU -lGL -lm
INCLUDES=-I/usr/include/GL

CCOPTS= -Wall -O3 -std=gnu99 $(INCLUDES)

.phony: clean all

all: 	so_game


vec3.o:		vec3.c vec3.h
	gcc $(CCOPTS) -c -o vec3.o vec3.c

surface.o:	surface.c surface.h vec3.h image.h
	gcc $(CCOPTS) -c -o surface.o surface.c

image.o:	image.c image.h
	gcc $(CCOPTS) -c -o image.o image.c

vehicle.o:	vehicle.c vehicle.h surface.h vec3.h image.h
	gcc $(CCOPTS) -c -o vehicle.o vehicle.c

world.o:	world.c world.h image.h surface.h vec3.h vehicle.h helpers.h
	gcc $(CCOPTS) -c -o world.o world.c

helpers.o:	helpers.c helpers.h
	gcc $(CCOPTS) -c -o helpers.o helpers.c

so_game.o:	so_game.c world.h image.h surface.h vec3.h vehicle.h helpers.h
	gcc $(CCOPTS) -c -o so_game.o so_game.c

OBJS=vec3.o surface.o image.o vehicle.o world.o helpers.o so_game.o

so_game:	vec3.o surface.o image.o vehicle.o world.o helpers.o so_game.o
		$(CC) $(CCOPTS) -o so_game vec3.o surface.o image.o vehicle.o world.o helpers.o so_game.o $(LIBS)

clean:	
	rm -rf *.o *~ cube main so_game
