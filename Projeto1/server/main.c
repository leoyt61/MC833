#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <uuid/uuid.h>

char* genereta_uuid() {
    uuid_t uuid;
    uuid_generate(uuid);
    char* uuid_str = malloc(sizeof(char) * 37);
    uuid_unparse(uuid, uuid_str);
    return uuid_str;
}

int main() {
    int socket_fd, new_socket_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = (socklen_t) sizeof(client_addr);
    char input_buffer[50];

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_aton("127.0.0.1", &server_addr.sin_addr);

    if (bind(socket_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(1);
    }

    listen(socket_fd, 5);

    while (1) {
        new_socket_fd = accept(socket_fd, (struct sockaddr*) &client_addr, &client_addr_len);

        recv(new_socket_fd, input_buffer, 5, 0);

        printf("%s\n", input_buffer);
    
        char ip_client[INET_ADDRSTRLEN];

        inet_ntop(AF_INET, &client_addr.sin_addr, ip_client, INET_ADDRSTRLEN);

        if (send(new_socket_fd, "World", 5, 0) < 0) {
            perror("send");
            exit(1);
        }
    }

    close(socket_fd);

}