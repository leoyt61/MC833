#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "./utils/request.h"
#include "./utils/response.h"
#include "./use-cases.h"

char *ip;
int socket_fd;
struct sockaddr_in server_addr, client_addr;
socklen_t client_addr_len;
pid_t pid;

char *get_current_ip();

void create_server(int port);

int match_endpoint(char *method, char *endpoint, Request *request);

char *get_response(char *request_message);

void run_server();

#endif
