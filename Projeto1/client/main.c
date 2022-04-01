#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <uuid/uuid.h>

int main() {
    int socket_fd;
    struct sockaddr_in server_addr;

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);

    inet_aton("127.0.0.1", &server_addr.sin_addr);

    if (connect(socket_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) != 0) {
        perror("connect");
        exit(1);
    }

    send(socket_fd, "Hello", 5, 0);

    char reply[5];
    recv(socket_fd, reply, 5, 0);

    printf("%s\n", reply);

    close(socket_fd);
}