{attribute 'dllimport', 'tgLogLib.so'}
FUNCTION tgLog_MQTT_Init : DINT
    VAR_INPUT
        broker : STRING(255);
        port : DINT;
        clientID : STRING(255);
    END_VAR
END_FUNCTION

{attribute 'dllimport', 'tgLogLib.so'}
FUNCTION tgLog_MQTT_Log : DINT
    VAR_INPUT
        topic : STRING(255);
        message : STRING(255);
    END_VAR
END_FUNCTION

{attribute 'dllimport', 'tgLogLib.so'}
FUNCTION tgLog_MQTT_Close : VOID
END_FUNCTION

{attribute 'dllimport', 'tgLogLib.so'}
FUNCTION tgLog_REST_Post : DINT
    VAR_INPUT
        url : STRING(255);
        jsonPayload : STRING(1024);
    END_VAR
END_FUNCTION

{attribute 'dllimport', 'tgLogLib.so'}
FUNCTION tgLog_MySQL_Connect : DINT
    VAR_INPUT
        host : STRING(255);
        user : STRING(255);
        password : STRING(255);
        database : STRING(255);
    END_VAR
END_FUNCTION

{attribute 'dllimport', 'tgLogLib.so'}
FUNCTION tgLog_MySQL_Log : DINT
    VAR_INPUT
        table : STRING(255);
        columns : STRING(255);
        values : STRING(255);
    END_VAR
END_FUNCTION

{attribute 'dllimport', 'tgLogLib.so'}
FUNCTION tgLog_MySQL_Close : VOID
END_FUNCTION

{attribute 'dllimport', 'tgLogLib.so'}
FUNCTION tgLog_InfluxDB_Write : DINT
    VAR_INPUT
        host : STRING(255);
        port : DINT;
        database : STRING(255);
        measurement : STRING(255);
        fields : STRING(1024);
        tags : STRING(255);
    END_VAR
END_FUNCTION
