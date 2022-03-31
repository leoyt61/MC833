#include "./pseudo_http.h"

Response *pseudo_http(char *method, char *url, Object *headers, Object *query_params, Object *body_params)
{
    char *url_copy = copy_string(url);
    char *ip = get_ip_from_url(url_copy);
    int port = atoi(get_port_from_url(url_copy));

    int socket_fd; 
    char buffer[MAX_CHARS]; 
    struct sockaddr_in target; 
    
    if ( (socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    }
            
    target.sin_family = AF_INET; 
    target.sin_port = htons(port); 
    target.sin_addr.s_addr = INADDR_ANY; 
    inet_aton(ip, &(target.sin_addr));

    socklen_t len; 

    char *request = build_request(method, url_copy, headers, query_params, body_params);

    Response *res= malloc(sizeof(Response));
    res->status = SERVER_ERROR;
    res->body = "TRY_AGAIN";

    len = sendto(socket_fd, request, strlen(request), 0, (struct sockaddr *)&target, (socklen_t) sizeof(target));
    if (len < 0)
    {
        res->message = "Error sending request";
        return res;
    }

    struct timeval tv;
    tv.tv_sec = 10;
    tv.tv_usec = 0;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
        res->message = "Error sending request";
        return res;
    }

    char *response = malloc(sizeof(char) * MAX_CHARS); 
    len = recvfrom(socket_fd, response, MAX_CHARS, MSG_WAITALL, (struct sockaddr *)&target, &len);
    if (len < 0)
    {
        res->message = "Error receiving response";
        return res;
    }

    close(socket_fd);

    res = get_response(response);

    return res;
};

char *get_ip_from_url(char *url)
{
    char *url_copy = malloc(sizeof(char) * (strlen(url) + 1));
    strcpy(url_copy, url);
    char *ip = head(tail(url_copy, "//"), ":");
    return ip;
};

char *get_port_from_url(char *url)
{
    char *port = head(tail(tail(url, "//"), ":"), "/");
    return port;
};

char *get_path_from_url(char *url)
{
    char *path = tail(tail(url, "//"), "/");
    char *path_with_slash = malloc(sizeof(char) * (strlen(path) + 2));
    strcpy(path_with_slash, "/");
    strcat(path_with_slash, path);
    return path_with_slash;
};

char *build_request(char *method, char *url, Object *headers, Object *query_params, Object *body_params)
{
    char *url_with_query_params = add_query_params(url, query_params);

    char *path = get_path_from_url(url_with_query_params);

    char *request = (char *)malloc(sizeof(char) * MAX_CHARS);
    sprintf(request, "%s %s HTTP/1.1\n\r", method, path);

    request = add_headers(request, url, headers);
    request = add_body_params(request, body_params);
    return request;
};

char *add_query_params(char *url, Object *query_params)
{
    if (query_params == NULL)
        return url;

    char *query_string = (char *)malloc(sizeof(char) * MAX_CHARS);
    query_string[0] = '\0';
    for (int i = 0; i < query_params->size; i++)
    {
        strcat(query_string, query_params->key_value_pairs[i][0]);
        strcat(query_string, "=");
        strcat(query_string, query_params->key_value_pairs[i][1]);
        strcat(query_string, "&");
    }
    if (query_string[strlen(query_string) - 1] == '&')
    {
        query_string[strlen(query_string) - 1] = '\0';
    }

    char *url_with_query_params = (char *)malloc(sizeof(char) * MAX_CHARS);
    sprintf(url_with_query_params, "%s?%s", url, query_string);
    return url_with_query_params;
};

char *add_headers(char *request, char *url, Object *headers)
{
    if (headers == NULL)
        headers = new_object();

    char *ip = get_ip_from_url(url);
    char *port = get_port_from_url(url);

    char *ip_with_port = (char *)malloc(sizeof(char) * MAX_CHARS);
    sprintf(ip_with_port, "%s:%s", ip, port);

    set_value(headers, "user-agent", "201330-mc833-client");
    set_value(headers, "Host", ip_with_port);
    set_value(headers, "Connection", "open");
    set_value(headers, "content-type", "text/plain");
    set_value(headers, "Access-Control-Allow-Origin", "*");

    char *header = (char *)malloc(sizeof(char) * MAX_CHARS);
    for (int i = 0; i < headers->size; i++)
    {
        sprintf(header, "%s%s: %s\n\r", header, headers->key_value_pairs[i][0], headers->key_value_pairs[i][1]);
    }
    sprintf(request, "%s%s", request, header);
    return request;
};

char *add_body_params(char *request, Object *body_params)
{
    if (body_params == NULL)
        return request;

    strcat(request, "\n");

    char *body_param = (char *)malloc(sizeof(char) * MAX_CHARS);
    for (int i = 0; i < body_params->size; i++)
    {
        sprintf(body_param, "%s%s: %s\n\r", body_param, body_params->key_value_pairs[i][0], body_params->key_value_pairs[i][1]);
    }
    sprintf(request, "%s%s", request, body_param);
    return request;
};

Response *get_response(char *response)
{
    Response *r = (Response *)malloc(sizeof(Response));
    char *status_and_message = head(tail(response, " "), "\n");
    char *status = head(status_and_message, " ");
    r->status = atoi(status);
    r->message = tail(status_and_message, " ");
    r->body = tail(response, "\n\n");
    return r;
};
