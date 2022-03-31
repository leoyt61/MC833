#include "./server.h"

char *get_current_ip()
{
    char hostbuffer[256];
    char *IPbuffer;
    struct hostent *host_entry;
    int hostname;

    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    if (hostname == -1)
    {
        perror("gethostname");
        exit(1);
    }

    host_entry = gethostbyname(hostbuffer);
    if (host_entry == NULL)
    {
        perror("gethostbyname");
        exit(1);
    }

    int last_ip_index = -1;
    while (host_entry->h_addr_list[last_ip_index + 1] != NULL)
    {
        last_ip_index++;
    };

    IPbuffer = inet_ntoa(*((struct in_addr *)
                               host_entry->h_addr_list[last_ip_index]));
    if (IPbuffer == NULL)
    {
        perror("inet_ntoa");
        exit(1);
    }

    return IPbuffer;
};

void create_server(int port)
{
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    port = port;
    ip = get_current_ip();

    client_addr_len = (socklen_t)sizeof(client_addr);

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_aton(ip, &server_addr.sin_addr);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_addr.sin_zero), 8);

    if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind");
        exit(1);
    }

    printf("Server running on http://%s:%d\n", ip, port);
};

int match_endpoint(char *method, char *endpoint, Request *request)
{
    if (strcmp(method, request->method) != 0)
    {
        return 0;
    }

    char endpoint_path_copy[MAX_CHARS];
    strcpy(endpoint_path_copy, endpoint);
    char request_path_copy[MAX_CHARS];
    strcpy(request_path_copy, request->path);

    char **endpoint_array = malloc(sizeof(char *) * 100);
    char *token = strtok(endpoint_path_copy, "/");
    int endpoint_path_count = 0;
    while (token != NULL)
    {
        endpoint_array[endpoint_path_count] = token;
        token = strtok(NULL, "/");
        endpoint_path_count++;
    }

    char **request_path_array = malloc(sizeof(char *) * 100);
    ;
    token = strtok(request_path_copy, "/");
    int request_path_count = 0;
    while (token != NULL)
    {
        request_path_array[request_path_count] = token;
        token = strtok(NULL, "/");
        request_path_count++;
    }

    if (endpoint_path_count != request_path_count)
    {
        return 0;
    }

    for (int i = 0; i < endpoint_path_count; i++)
    {
        if (endpoint_array[i][0] != ':' && strcmp(endpoint_array[i], request_path_array[i]) != 0)
        {
            return 0;
        }
        else if (endpoint_array[i][0] == ':')
        {
            char *variable_name = malloc(sizeof(char) * strlen(endpoint_array[i]));
            strcpy(variable_name, endpoint_array[i] + 1);
            char *variable_value = malloc(sizeof(char) * strlen(request_path_array[i]));
            strcpy(variable_value, request_path_array[i]);

            char *variable_pair = malloc(sizeof(char) * (strlen(variable_name) + strlen(variable_value) + 2));
            strcpy(variable_pair, variable_name);
            strcat(variable_pair, ": ");
            strcat(variable_pair, variable_value);
            strcat(variable_pair, "\n");

            request->path_variables = append_to_string(request->path_variables, variable_pair);
        }
    }

    return 1;
};

char *get_response(char *request_message)
{
    printf("\n################################\n");
    printf("Request:\n%s", request_message);
    Request *request = parse_request_message(request_message);

    Response *response;
    response = create_response(NOT_FOUND, "text/plain", "Path not found");
    set_response_header_from_request(response, request);

    printf("\n");
    printf("Request method: %s\n", request->method);
    printf("Request path: %s\n", request->path);

    if (match_endpoint("GET", "/movies", request))
    {
        response = find_movies(request);
    }
    else if (match_endpoint("GET", "/movies/:id", request))
    {
        response = find_movie_by_id(request);
    }
    else if (match_endpoint("POST", "/movies", request))
    {
        response = register_movie(request);
    }
    else if (match_endpoint("PATCH", "/movies/:id/add-genre", request))
    {
        response = append_genre_to_movie(request);
    }
    else if (match_endpoint("DELETE", "/movies/:id", request))
    {
        response = delete_movie(request);
    }

    return parse_response_to_text(response);
};

void run_server()
{
    init_movies_repository("./data/movies");
    while (1)
    {
        int pid = fork();
        if (pid == 0)
        {
            char request_message[MAX_CHARS];

            int n = recvfrom(socket_fd, (char *)request_message, MAX_CHARS, MSG_WAITALL, (struct sockaddr *)&client_addr, &client_addr_len);
            if (n < 0)
                continue;

            request_message[n] = '\0';

            char *response_message = get_response(request_message);

            response_message[strlen(response_message)] = '\0';

            sendto(socket_fd, response_message, strlen(response_message), 0, (struct sockaddr *)&client_addr, client_addr_len);
        }
        waitpid(pid, NULL, 0);
    }
};
