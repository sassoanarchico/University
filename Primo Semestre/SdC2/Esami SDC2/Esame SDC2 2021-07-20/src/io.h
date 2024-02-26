#ifndef __IO_H__
#define __IO_H__

int send_to_socket(int sd, const char *msg);

int recv_from_socket(int sd, char *msg, int max_len);

#endif
