#ifndef REQUEST_H
#define REQUEST_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "./common.h"

typedef struct
{
    char *method;
    char *path;
    char *path_variables;
    char *version;
    char *query;
    char *headers;
    char *body;
} Request;

Request *parse_request_message(char *request_message);

#endif
