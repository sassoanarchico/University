CC=gcc
CCOPTS=-std=gnu99
BINS=capture_camera capture_joystick serial_example

.phony: clean all

all: $(BINS)

capture_camera:	capture_camera.c
	$(CC) -$(CCOPTS) -o $@ $^  

capture_joystick:	capture_joystick.c
	$(CC) -$(CCOPTS) -o $@ $^  

serial_example:	serial_example.c serial_linux.c 
	$(CC) -$(CCOPTS) -o $@ $^

clean:
	rm -rf *~ $(BINS) *.pgm

