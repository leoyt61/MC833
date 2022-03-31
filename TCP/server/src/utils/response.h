#ifndef RESPONSE_H
#define RESPONSE_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "request.h"

#define OK 200
#define CREATED 201
#define NO_CONTENT 204
#define BAD_REQUEST 400
#define NOT_FOUND 404
#define SERVER_ERROR 500

typedef struct
{
    unsigned int status;
    char *method;
    char *path;
    char *version;
    char *message;
    char *content_type;
    char *body;
} Response;

void set_response_message_by_status(Response *response);

Response *create_response(unsigned int status, char *content_type, char *body);

void set_response_header_from_request(Response *response, Request *request);

char *parse_response_to_text(Response *response);

#endif
