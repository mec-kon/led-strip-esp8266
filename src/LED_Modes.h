#ifndef ESP8266_MODE_H
#define ESP8266_MODE_H

#include "Data.h"
#include "SchedulerDefinitions.h"

void led_loop();
extern Task fade_mode;
extern Task changing_colors_mode;

#endif //ESP8266_MODE_H
