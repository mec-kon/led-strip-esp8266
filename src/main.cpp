#include <Arduino.h>
#include <../.pio/libdeps/esp12e/ESP8266Scheduler_ID917/src/Scheduler.h>

#include "config.h"
#include "Data.h"
#include "Http.h"

#include "GPIO.h"
#include "Mode.h"

bool new_message = false;
Data data;

Http http(&data, &new_message);
Mode mode(&data, &new_message);




void setup() {
    Serial.begin(115200);

    /**
     * ESP01

    pinMode(1, FUNCTION_3);
    pinMode(3, FUNCTION_3);

     */

    Scheduler.start(&mode);
    Scheduler.start(&http);
    Scheduler.begin();
}

void loop() {
    Serial.println("test");
}
