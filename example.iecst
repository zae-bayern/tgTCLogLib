PROGRAM MAIN
VAR
    result : DINT;
END_VAR

// MQTT-Logging
result := tgLog_MQTT_Init('broker.example.com', 1883, 'TwinCATClient');
result := tgLog_MQTT_Log('test/topic', 'Hello MQTT');
tgLog_MQTT_Close();

// REST API Logging
result := tgLog_REST_Post('http://example.com/api/log', '{"key": "value"}');

// InfluxDB Logging
result := tgLog_InfluxDB_Write('127.0.0.1', 8086, 'myDatabase', 'temperature', 'value=25.3', 'sensor=1');

// MySQL Logging
result := tgLog_MySQL_Connect('127.0.0.1', 'user', 'password', 'myDatabase');
result := tgLog_MySQL_Log('measurements', 'timestamp, value', '"2025-01-15 12:00:00", 42');
tgLog_MySQL_Close();
