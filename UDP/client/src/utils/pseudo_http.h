#ifndef PSEUDO_HTTP_H
#define PSEUDO_HTTP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/mman.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "./object.h"
#include "./common.h"

#define OK 200
#define CREATED 201
#define NO_CONTENT 204
#define BAD_REQUEST 400
#define NOT_FOUND 404
#define SERVER_ERROR 500

typedef struct {
    int status;
    char *message;
    char *body;
} Response;

Response *pseudo_http(char *method, char *url, Object *headers, Object *query_params, Object *body_params);

char *get_ip_from_url(char *url);

char *get_port_from_url(char *url);

char *get_path_from_url(char *url);

char *build_request(char *method, char *url, Object *headers, Object *query_params, Object *body_params);

char *add_query_params(char *url, Object *query_params);

char *add_headers(char *request, char *url, Object *headers);

char *add_body_params(char *request, Object *body_params);

Response *get_response(char *response);

#endif
