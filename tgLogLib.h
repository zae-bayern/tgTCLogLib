#ifndef TGLOGLIB_H
#define TGLOGLIB_H

#ifdef __cplusplus
extern "C" {
#endif

// MQTT Funktionen
int tgLog_MQTT_Init(const char *broker, int port, const char *clientID);
int tgLog_MQTT_Log(const char *topic, const char *message);
void tgLog_MQTT_Close();

// REST API Funktionen
int tgLog_REST_Post(const char *url, const char *jsonPayload);

// InfluxDB Funktionen
int tgLog_InfluxDB_Write(const char *host, int port, const char *database, const char *measurement, const char *fields, const char *tags);

// MySQL Funktionen
int tgLog_MySQL_Connect(const char *host, const char *user, const char *password, const char *database);
int tgLog_MySQL_Log(const char *table, const char *columns, const char *values);
void tgLog_MySQL_Close();

#ifdef __cplusplus
}
#endif

#endif // TGLOGLIB_H
