#include "main.h"
#include "http.h"

http_parse_e parse_http_headers(char* raw_request, http_request* request){
    const char *line_start = strstr(raw_request, "\r\n");
    if(!line_start) return HTTP_PARSE_INVALID;

    line_start += 2;
    while(line_start && *line_start && *line_start != '\r' && *line_start != '\n'){
        const char* line_end = strstr(line_start, "\r\n");
        if(!line_end) break;

        size_t line_length = line_end - line_start;
        char line[1024] = {0};
        strncpy(line, line_start, line_length);
        
        char* colon_pos = strstr(line, ":");
        if(colon_pos){
            *colon_pos = '\0';
            const char *key = line;
            const char *value = colon_pos+1;

            while(*value == ' ') value++;

            http_header_t** tmp = realloc(request->headers, sizeof(http_header_t*) * (request->header_count + 1));
            if (!tmp) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
            request->headers = tmp;

            request->headers[request->header_count] = malloc(sizeof(http_header_t));
            if (!request->headers[request->header_count]) {
                perror("malloc");
                exit(EXIT_FAILURE);
            }

            strncpy(request->headers[request->header_count]->key, key, sizeof(request->headers[request->header_count]->key) - 1);
            request->headers[request->header_count]->key[sizeof(request->headers[request->header_count]->key) - 1] = '\0';

            strncpy(request->headers[request->header_count]->value, value, sizeof(request->headers[request->header_count]->value) - 1);
            request->headers[request->header_count]->value[sizeof(request->headers[request->header_count]->value) - 1] = '\0';

            request->header_count++;
        }
        line_start = line_end + 2;
    }
    return HTTP_PARSE_OK;
}

int free_http_headers(http_request *request){
    for (size_t i = 0; i < request->header_count; i++) {
        free(request->headers[i]);
    }
    free(request->headers);
    request->headers = NULL;
    request->header_count = 0;
    return 0;
}

int read_http_request(int socket_fd, http_request* request){
    int16_t bytes_read;
    bytes_read = read(socket_fd, request->buffer, sizeof(request->buffer));
    request->buffer[bytes_read] = '\0';

    if(bytes_read <= 0)
        return -1;
    
    if(sscanf(request->buffer, "%7s %2047s %15s", request->method, request->path, request->protocol) != 3)
        return -1;
    
    return 0;
}