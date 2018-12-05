#ifndef ESP8266_GPIO_H
#define ESP8266_GPIO_H

#include "Arduino.h"
#include "config.h"

class GPIO {
public:
    GPIO();
    void pwm_write(uint8_t gpio, uint16_t value);
};


#endif //ESP8266_GPIO_H
