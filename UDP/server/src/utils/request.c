#include "./request.h"

Request *parse_request_message(char *request_message)
{
    Request *request = malloc(sizeof(Request));
    char *first_line = strtok(request_message, "\n");
    char *rest_of_message = strtok(NULL, "\0");

    char *method = strtok(first_line, " ");
    char *path = strtok(NULL, " ");
    char *version = strtok(NULL, " ");

    char *query = tail(path, "?");

    request->method = method;
    request->query = query;
    request->path = path;
    request->version = version;
    request->path_variables = malloc(sizeof(char) * MAX_CHARS);

    char *headers = malloc(sizeof(char) * strlen(rest_of_message));
    strcpy(headers, rest_of_message);
    char *body = tail(headers, "\n\r");

    request->headers = headers;
    request->body = body;

    return request;
};
