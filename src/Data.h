#ifndef ESP8266_DATA_H
#define ESP8266_DATA_H

#include "Arduino.h"
#include "config.h"

struct Color{
    uint8_t red;
    uint8_t green;
    uint8_t blue;

};

struct Data {
    
    Color color;

    struct ColorData{
        Color color_array[DATA_SIZE];
        uint16_t time;
        char mode[15];
        uint8_t number_of_colors;

    }color_data;
};


#endif //ESP8266_DATA_H
