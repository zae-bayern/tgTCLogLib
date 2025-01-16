#include "tgLogLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

static int mqttSocket = -1;
static struct sockaddr_in mqttServerAddr;

int tgLog_MQTT_Init(const char *broker, int port, const char *clientID) {
    mqttSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (mqttSocket < 0) {
        perror("Socket erstellen fehlgeschlagen");
        return -1;
    }

    memset(&mqttServerAddr, 0, sizeof(mqttServerAddr));
    mqttServerAddr.sin_family = AF_INET;
    mqttServerAddr.sin_port = htons(port);
    if (inet_pton(AF_INET, broker, &mqttServerAddr.sin_addr) <= 0) {
        perror("Ungültige Broker-Adresse");
        close(mqttSocket);
        return -1;
    }

    if (connect(mqttSocket, (struct sockaddr *)&mqttServerAddr, sizeof(mqttServerAddr)) < 0) {
        perror("Verbindung zum Broker fehlgeschlagen");
        close(mqttSocket);
        return -1;
    }

    char connectPacket[64] = {0x10, 0x0E, 0x00, 0x04, 'M', 'Q', 'T', 'T', 0x04, 0x02, 0x00, 0x3C, 0x00, strlen(clientID)};
    strcat(connectPacket + 14, clientID);
    send(mqttSocket, connectPacket, 14 + strlen(clientID), 0);

    return 0;
}

int tgLog_MQTT_Log(const char *topic, const char *message) {
    if (mqttSocket < 0) {
        fprintf(stderr, "MQTT ist nicht initialisiert\n");
        return -1;
    }

    size_t topicLen = strlen(topic);
    size_t messageLen = strlen(message);
    size_t totalLen = 2 + topicLen + messageLen;
    char publishPacket[totalLen + 2];
    publishPacket[0] = 0x30; // PUBLISH Header
    publishPacket[1] = totalLen;
    publishPacket[2] = (topicLen >> 8) & 0xFF;
    publishPacket[3] = topicLen & 0xFF;
    memcpy(publishPacket + 4, topic, topicLen);
    memcpy(publishPacket + 4 + topicLen, message, messageLen);

    send(mqttSocket, publishPacket, totalLen + 2, 0);
    return 0;
}

void tgLog_MQTT_Close() {
    if (mqttSocket >= 0) {
        close(mqttSocket);
        mqttSocket = -1;
    }
}
