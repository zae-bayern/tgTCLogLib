#include "tgLogLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

static int mysqlSocket = -1;

int tgLog_MySQL_Connect(const char *host, const char *user, const char *password, const char *database) {
    mysqlSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (mysqlSocket < 0) {
        perror("MySQL-Socket-Fehler");
        return -1;
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(3306);

    if (inet_pton(AF_INET, host, &serverAddr.sin_addr) <= 0) {
        perror("Ungültige MySQL-Adresse");
        close(mysqlSocket);
        return -1;
    }

    if (connect(mysqlSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("MySQL-Verbindung fehlgeschlagen");
        close(mysqlSocket);
        return -1;
    }

    // Login etc. folgt mit SQL-Befehlen
    return 0;
}

int tgLog_MySQL_Log(const char *table, const char *columns, const char *values) {
    if (mysqlSocket < 0) {
        fprintf(stderr, "MySQL ist nicht initialisiert\n");
        return -1;
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO %s (%s) VALUES (%s);", table, columns, values);
    send(mysqlSocket, query, strlen(query), 0);

    return 0;
}

void tgLog_MySQL_Close() {
    if (mysqlSocket >= 0) {
        close(mysqlSocket);
        mysqlSocket = -1;
    }
}
