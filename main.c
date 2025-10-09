#include "main.h"
#include "tcp.h"

int main(int argc, char *argv[]){
    (void)argc;
    (void)argv;
    tcp_server server = {0};
    server_status_e status = bind_tcp_port(&server, 8080);
    if(status != SERVER_OK){
        debug_log("Server initialization failed\n");
        exit(EXIT_FAILURE);
    }
    int client_fd = accept_client(server.socket_fd);
    if(client_fd == -1){
        debug_log("Failed to accept client connection\n");
        exit(EXIT_FAILURE);
    }
    debug_log("Client connected\n");
    
    close(client_fd);
    close(server.socket_fd);

    return EXIT_SUCCESS;
}