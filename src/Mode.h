#ifndef ESP8266_MODE_H
#define ESP8266_MODE_H

#include "../.pio/libdeps/esp12e/ESP8266Scheduler_ID917/src/Scheduler.h"
#include "GPIO.h"
#include "Data.h"

class Mode : public Task {
public:
    Mode(Data *data, bool *new_message);

private:
    bool *new_message;
    Data *data;
    GPIO gpio;

    void one_color();
    void fade();
    void changing_colors();


protected:
    void setup();
    void loop();
};


#endif //ESP8266_MODE_H
