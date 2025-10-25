#include "main.h"
#include "http.h"

const int MAX_HTTP_REQ_LEN = 8192;

int read_http_request(int socket_fd, http_request* request){
    int16_t bytes_read;
    char buff[MAX_HTTP_REQ_LEN];
    read(socket_fd, buff, MAX_HTTP_REQ_LEN);
    buff[bytes_read] = '\0';

    if(bytes_read <= 0)
        return -1;
    
    if(sscanf(buff, "%7s %2047s %15s", request->method, request->path, request->protocol) != 3)
        return -1;
    
    return 0;
}