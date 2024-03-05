#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
  //ia check that we have the cmd line arg that indicates the joy device file
  if (argc < 2) {
    printf("usage: %s <joy_device>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  //ia open the device as a file and get the file descriptor -
  //ia note that this is an INPUT device, therefore we use the flag [ O_RDONLY ]
  //ia in the open
  printf("opening device [ %s ]\n", argv[1]);
  int fd = open(argv[1], O_RDONLY);

  //ia check that open was successful
  if (fd < 0) {
    printf("cannot open device [ %s ]\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  //ia let's read! each time a button is pressed on the joystick,
  //ia Linux will generate for us an event of type js_event
  struct js_event e;
  while(1) {
    
    //ia hence, we only need to check that there is something to read and
    //ia read a chunck of data as big as the size of a single js_event
    while (read (fd, &e, sizeof(e)) > 0 ){

      //ia now you can "consume" your joystick event
      //ia for example you can generate robot commands or send
      //ia stuff to your videogame :)
      printf ("EVENT time: %u, axis: %d, type: %d, value: %d\n",
	      e.time,
	      e.number,
	      e.type,
	      e.value);
    }
  }
}
