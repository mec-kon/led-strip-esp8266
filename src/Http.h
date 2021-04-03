#ifndef ESP8266_HTTP_H
#define ESP8266_HTTP_H

#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

#include "config.h"
#include "Data.h"
#include "SchedulerDefinitions.h"


void http_thread();

#endif //ESP8266_HTTP_H
