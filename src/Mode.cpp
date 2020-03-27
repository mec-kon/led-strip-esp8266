#include "Mode.h"


Mode::Mode(Data *data, bool *new_message) {
    this->new_message = new_message;
    this->data = data;
}

void Mode::one_color() {
    Color color = data->color_data.color_array[0];

    gpio.pwm_write(GPIO_RED, color.red);
    gpio.pwm_write(GPIO_GREEN, color.green);
    gpio.pwm_write(GPIO_BLUE, color.blue);
}

void Mode::fade() {
    uint8_t i = 0;
    Color color1;
    Color color2;

    while (!(*new_message)) {
        if (i == data->color_data.number_of_colors - 1) {
            color1 = data->color_data.color_array[data->color_data.number_of_colors - 1];
            color2 = data->color_data.color_array[0];
        }
        else {
            if (i == data->color_data.number_of_colors) {
                i = 0;
            }
            color1 = data->color_data.color_array[i];
            color2 = data->color_data.color_array[i + 1];
        }
        i++;
        while (color1.red != color2.red || color1.blue != color2.blue || color1.green != color2.green) {
            if (*new_message) {
                break;
            }

            if (color1.red > color2.red) {
                color1.red--;
            }
            else if (color1.red < color2.red) {
                color1.red++;
            }

            if (color1.green > color2.green) {
                color1.green--;
            }
            else if (color1.green < color2.green) {
                color1.green++;
            }

            if (color1.blue > color2.blue) {
                color1.blue--;
            }
            else if (color1.blue < color2.blue) {
                color1.blue++;
            }

            gpio.pwm_write(GPIO_RED, color1.red);
            gpio.pwm_write(GPIO_GREEN, color1.green);
            gpio.pwm_write(GPIO_BLUE, color1.blue);

            delay(data->color_data.time);
        }
    }
}

void Mode::changing_colors() {
    uint8_t i = 0;
    Color color;

    while (!(*new_message)) {
        if (i == data->color_data.number_of_colors) {
            i = 0;
        }
        color = data->color_data.color_array[i];
        i++;

        gpio.pwm_write(GPIO_RED, color.red);
        gpio.pwm_write(GPIO_GREEN, color.green);
        gpio.pwm_write(GPIO_BLUE, color.blue);

        delay(data->color_data.time * 10);
    }
}


void Mode::setup() {
}

void Mode::loop() {
    if(*new_message){
        *new_message = false;
        if (strcmp(data->color_data.mode, "fade") == 0) {
            Serial.println("mode started : fade");
            fade();
            Serial.println("mode stopped : fade");
        }
        else if (strcmp(data->color_data.mode, "changingColors") == 0) {
            Serial.println("mode started : changingColors");
            changing_colors();
            Serial.println("mode stopped: changingColors");
        }
        else {
            Serial.println("mode started : oneColor");
            one_color();
            Serial.println("mode stopped : oneColor");
        }
    }
}
