#pragma once

#include <stddef.h>

typedef enum {
    HTTP_OK,
    HTTP_BAD_REQUEST,
    HTTP_NOT_IMPLEMENTED,
    HTTP_VERSION_NOT_SUPORTED
} http_status_e;

typedef enum {
    HTTP_PARSE_INVALID = -1,
    HTTP_PARSE_OK = 0,
} http_parse_e;

typedef struct {
    char key[255];
    char value[512];
} http_header_t;

#define MAX_REQUEST_LEN 8192*4

typedef struct {
    char method[8];
    char path[2048];
    char protocol[16];
    http_header_t** headers;
    size_t header_count;
    char buffer[MAX_REQUEST_LEN];
} http_request;

int read_http_request(int socket_fd, http_request* request);
http_parse_e parse_http_headers(char* raw_headers, http_request*);
int free_http_headers(http_request*);