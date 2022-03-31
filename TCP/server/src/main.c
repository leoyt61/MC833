#include "server.h"

int main(int argc, char *argv[]) {
    
    char *port = argv[1];

    create_server(atoi(port));
    run_server();

    return 0;
};
