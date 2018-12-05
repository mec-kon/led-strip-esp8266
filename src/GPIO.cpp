#include "GPIO.h"

GPIO::GPIO() {
    pinMode(GPIO_RED, OUTPUT);
    pinMode(GPIO_GREEN, OUTPUT);
    pinMode(GPIO_BLUE, OUTPUT);
}

void GPIO::pwm_write(uint8_t gpio, uint16_t value) {
    analogWrite(gpio, PWMRANGE -(value*4));
}
