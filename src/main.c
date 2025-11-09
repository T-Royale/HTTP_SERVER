#include "main.h"
#include "tcp.h"
#include "http.h"

int main(int argc, char *argv[]){
    uint16_t port = 8080;
    char c;
    while((c = getopt(argc, argv, "p:")) != -1){
        switch(c){
            case 'p':
                port = atoi(optarg);
                break;
            case '?':
            default:
                printf("Invalid option\n");
                printf("USAGE: %s -p <port>\n", argv[0]);
                break;
        }
    }
    tcp_server server = {0};
    server_status_e status = bind_tcp_port(&server, port);
    if(status != SERVER_OK){
        debug_log("Server initialization failed\n");
        exit(EXIT_FAILURE);
    } else printf("Server initialized on port %d\n", port);
    while(status == SERVER_OK){
        int16_t client_fd = accept_client(server.socket_fd);
        if(client_fd == -1){
            debug_log("Failed to accept client connection\n");
            exit(EXIT_FAILURE);
        }
        debug_log("Client connected\n");

        http_request req = {0};
        if(read_http_request(client_fd, &req) == -1){
            printf("Invalid http request received\n");
            return 0;
        }

        if(parse_http_headers(req.buffer, &req) != HTTP_PARSE_OK){
            debug_log("Failed to read or parse HTTP_HEADERS\n");
            close(client_fd);
            return 0;
        }

        printf("Parsed HTTP headers:\n");
        for(size_t i = 0; i < req.header_count; i++){
            printf("\t%s: %s\n", req.headers[i]->key, req.headers[i]->value);
        }

        free_http_headers(&req);

        close(client_fd);
    }
    close(server.socket_fd);

    return EXIT_SUCCESS;
}