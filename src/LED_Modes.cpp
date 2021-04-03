#include "LED_Modes.h"

Data *led_data;
uint8_t iterator = 0;

void dimm_leds(Color color){
    analogWrite(GPIO_RED, color.red*4);
    analogWrite(GPIO_GREEN, color.green*4);
    analogWrite(GPIO_BLUE, color.blue*4);
}


void one_color() {
    Color color = led_data->color_data.color_array[0];
    dimm_leds(color);
}


Color fade_color1;
Color fade_color2;
void fade() {

    if(fade_mode.isFirstIteration()){
        fade_color1 = led_data->color_data.color_array[0];
        fade_color2 = led_data->color_data.color_array[1];
    }

    if(fade_color1.red != fade_color2.red || fade_color1.blue != fade_color2.blue || fade_color1.green != fade_color2.green) {

        if (fade_color1.red > fade_color2.red) {
            fade_color1.red--;
        }
        else if (fade_color1.red < fade_color2.red) {
            fade_color1.red++;
        }

        if (fade_color1.green > fade_color2.green) {
            fade_color1.green--;
        }
        else if (fade_color1.green < fade_color2.green) {
            fade_color1.green++;
        }

        if (fade_color1.blue > fade_color2.blue) {
            fade_color1.blue--;
        }
        else if (fade_color1.blue < fade_color2.blue) {
            fade_color1.blue++;
        }

        dimm_leds(fade_color1);
    }
    else {
        iterator++;
        if (iterator == led_data->color_data.number_of_colors - 1) {
            fade_color1 = led_data->color_data.color_array[led_data->color_data.number_of_colors - 1];
            fade_color2 = led_data->color_data.color_array[0];
        }
        else {
            if (iterator == led_data->color_data.number_of_colors) {
                iterator = 0;
            }
            fade_color1 = led_data->color_data.color_array[iterator];
            fade_color2 = led_data->color_data.color_array[iterator + 1];
        }
    }
}
Task fade_mode(TASK_IMMEDIATE, TASK_FOREVER, &fade);


void changing_colors() {
    Color color;

    if (iterator == led_data->color_data.number_of_colors) {
        iterator = 0;
    }
    color = led_data->color_data.color_array[iterator];
    iterator++;

    dimm_leds(color);
}
Task changing_colors_mode(TASK_IMMEDIATE, TASK_FOREVER, &changing_colors);


void led_loop() {

    if(new_data()){
        Serial.println("new data");
        led_data = get_data();
        fade_mode.disable();
        changing_colors_mode.disable();

        if(strcmp(led_data->color_data.mode, "oneColor") == 0) {
            Serial.println("mode started : oneColor");
            one_color();
        }
        else if(strcmp(led_data->color_data.mode, "fade") == 0) {
            if(led_data->color_data.number_of_colors > 1){
                Serial.println("mode started : fade");
                fade_mode.setInterval(led_data->color_data.time);
                fade_mode.enable();
            }
        }
        else if(strcmp(led_data->color_data.mode, "changingColors") == 0) {
            if(led_data->color_data.number_of_colors > 1){
                Serial.println("mode started : changingColors");
                changing_colors_mode.setInterval(led_data->color_data.time*100);
                changing_colors_mode.enable();
            }
        }
    }
}

