#ifndef ESP8266_HTTP_H
#define ESP8266_HTTP_H

#include <ESP8266WebServer.h>
#include "../.pio/libdeps/esp12e/ESP8266Scheduler_ID917/src/Scheduler.h"
#include "../.pio/libdeps/esp12e/ArduinoJson_ID64/src/ArduinoJson.h"

#include "config.h"
#include "Data.h"

class Http : public Task {
public:
    Http(Data *data, bool *new_message);

private:
    const char *ssid = WLAN_SSID;
    const char *password = PASSWORD;

    bool *new_message;
    Data *data;

    void handle_request();
    void handle_cors_request();
    void parse_json(String *message);

protected:
    void setup();
    void loop();
};


#endif //ESP8266_HTTP_H
