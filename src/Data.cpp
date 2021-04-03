#include "Data.h"

bool new_message;
Data *data;

bool new_data(){
    return new_message;
}

Data* get_data(){
    new_message = false;
    return data;
}

// create data struct from json or openHAB string
void set_data(String message){
    new_message = true;
    delete data;

    data = new Data;
    // string must be in json format
    // create data struct from json
    if(message[0] == '{'){
        StaticJsonDocument<800> JSONDocument;
        DeserializationError err = deserializeJson(JSONDocument, message);
        if(err == DeserializationError::Ok){
            JsonObject parsed = JSONDocument.as<JsonObject>();

            const char *mode1;
            uint8_t number_of_colors = parsed["number_of_colors"];
            for (uint8_t i = 0; i < number_of_colors; i++) {
                data->color_data.color_array[i].red = parsed["color_array"][i]["color_red"];
                data->color_data.color_array[i].green = parsed["color_array"][i]["color_green"];
                data->color_data.color_array[i].blue = parsed["color_array"][i]["color_blue"];
            }
            data->color_data.time = parsed["time"];
            mode1 = parsed["mode"];
            data->color_data.number_of_colors = number_of_colors;
            if(mode1 != nullptr && number_of_colors != 0){
                strcpy(data->color_data.mode, mode1);
            }
            else {
                new_message = false;
                Serial.println("error parsing json");
            }

        }
        else{
            Serial.println("error deserialising json");
        }
    }
    // create struct from openHAB mqtt color format, e.g. "112,54,123"
    else{
        char buffer[12];
        message.toCharArray(buffer, 12);
        char delimiter[] = ",";

        String ptr = strtok(buffer, delimiter);
        data->color_data.color_array[0].red = ptr.toInt();

        ptr = strtok(NULL, delimiter);
        data->color_data.color_array[0].green = ptr.toInt();

        ptr = strtok(NULL, delimiter);
        data->color_data.color_array[0].blue = ptr.toInt();

        strcpy(data->color_data.mode, "oneColor");
    }

}
