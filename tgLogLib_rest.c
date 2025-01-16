#include "tgLogLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h> 
#include <netdb.h> 

int tgLog_REST_Post(const char *url, const char *jsonPayload) {
    char host[128], path[256];
    int port = 80;
    sscanf(url, "http://%127[^:/]:%d/%255s", host, &port, path);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) return -1;

    struct hostent *server = gethostbyname(host);
    if (!server) return -1;

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    memcpy(&serverAddr.sin_addr.s_addr, server->h_addr, server->h_length);

    if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) return -1;

    char request[1024];
    snprintf(request, sizeof(request),
             "POST /%s HTTP/1.1\r\n"
             "Host: %s\r\n"
             "Content-Type: application/json\r\n"
             "Content-Length: %zu\r\n\r\n%s",
             path, host, strlen(jsonPayload), jsonPayload);

    send(sockfd, request, strlen(request), 0);
    close(sockfd);

    return 0;
}
