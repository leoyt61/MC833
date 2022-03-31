#include "response.h"

void set_response_message_by_status(Response *response)
{
    switch (response->status)
    {
    case OK:
        response->message = "OK";
        break;
    case CREATED:
        response->message = "Created";
        break;
    case NO_CONTENT:
        response->message = "No Content";
        break;
    case BAD_REQUEST:
        response->message = "Bad Request";
        break;
    case NOT_FOUND:
        response->message = "Not Found";
        break;
    case SERVER_ERROR:
        response->message = "Internal Server Error";
        break;
    default:
        break;
    }
};

Response *create_response(unsigned int status, char *content_type, char *body)
{
    Response *response = malloc(sizeof(Response));
    response->status = status;
    set_response_message_by_status(response);
    response->content_type = content_type;
    response->body = body ? body : "";
    return response;
};

void set_response_header_from_request(Response *response, Request *request)
{
    response->method = request->method;
    response->path = request->path;
    response->version = request->version;
};

char *parse_response_to_text(Response *response)
{
    char *response_text = malloc(sizeof(char) * MAX_CHARS);
    sprintf(response_text, "HTTP/1.1 %d %s\n", response->status, response->message);
    sprintf(response_text, "%sContent-Type: %s\n", response_text, response->content_type);
    sprintf(response_text, "%sAccess-Control-Allow-Origin: *\n", response_text);
    if (response->body) sprintf(response_text, "%sContent-Length: %lu\n", response_text, strlen(response->body));
    sprintf(response_text, "%s\n", response_text);
    sprintf(response_text, "%s%s", response_text, response->body);
    return response_text;
};
