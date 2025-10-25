#pragma once

typedef struct {
    char method[8];
    char path[2048];
    char protocol[16];
} http_request;

int read_http_request(int socket_fd, http_request* request);