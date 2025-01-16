#include "tgLogLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int tgLog_InfluxDB_Write(const char *host, int port, const char *database, const char *measurement, const char *fields, const char *tags) {
    int sockfd;
    struct sockaddr_in serverAddr;
    char buffer[1024];
    char lineProtocol[512];
    char httpRequest[1024];
    int bytesSent, bytesReceived;

    // Line-Protokoll erstellen
    if (tags && strlen(tags) > 0) {
        snprintf(lineProtocol, sizeof(lineProtocol), "%s,%s %s\n", measurement, tags, fields);
    } else {
        snprintf(lineProtocol, sizeof(lineProtocol), "%s %s\n", measurement, fields);
    }

    // Socket erstellen
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket erstellen fehlgeschlagen");
        return -1;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    if (inet_pton(AF_INET, host, &serverAddr.sin_addr) <= 0) {
        perror("Ungültige InfluxDB-Adresse");
        close(sockfd);
        return -1;
    }

    // Verbindung zur InfluxDB herstellen
    if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Verbindung zur InfluxDB fehlgeschlagen");
        close(sockfd);
        return -1;
    }

    // HTTP POST-Anfrage erstellen
    snprintf(httpRequest, sizeof(httpRequest),
             "POST /write?db=%s HTTP/1.1\r\n"
             "Host: %s\r\n"
             "Content-Type: text/plain\r\n"
             "Content-Length: %zu\r\n\r\n%s",
             database, host, strlen(lineProtocol), lineProtocol);

    // HTTP-Anfrage senden
    bytesSent = send(sockfd, httpRequest, strlen(httpRequest), 0);
    if (bytesSent < 0) {
        perror("Fehler beim Senden der HTTP-Anfrage");
        close(sockfd);
        return -1;
    }

    // Antwort von InfluxDB lesen
    bytesReceived = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived < 0) {
        perror("Fehler beim Lesen der Antwort von InfluxDB");
        close(sockfd);
        return -1;
    }

    buffer[bytesReceived] = '\0'; // Null-terminieren für sichere Ausgabe
    printf("Antwort von InfluxDB:\n%s\n", buffer);

    // Verbindung schließen
    close(sockfd);
    return 0;
}
