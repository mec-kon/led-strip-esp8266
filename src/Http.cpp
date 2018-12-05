#include "Http.h"
#include "../../../.platformio/packages/framework-arduinoespressif8266/cores/esp8266/HardwareSerial.h"


ESP8266WebServer server(80);

Http::Http(Data *data, bool *new_message) {
    this->new_message = new_message;
    this->data = data;
}

void Http::parse_json(String *message){
    StaticJsonBuffer<800> JSONBuffer;
    JsonObject &parsed = JSONBuffer.parseObject(*message);
    if (!parsed.success()) {   //Check for errors in parsing
        Serial.println("JSON parsing failed");
        delay(5000);
    }
    else {
        Serial.println("parsing array");
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

        strcpy(data->color_data.mode, mode1);

        *new_message = true;

    }
}

void Http::handle_request(){
    if (server.hasArg("plain") == false && server.hasArg("json") == false) { //Check if body received
        server.send(200, "text/plain", "Body not received");
        Serial.println("data not received");
        Serial.println(server.arg("plain"));
    }
    else {
        String message = server.arg("json");
        if(message == ""){
            message = server.arg("plain");
        }
        server.send(200, "text/plain", message);
        parse_json(&message);
        Serial.println("data received");
    }
}

void Http::setup() {
    Serial.println("http init");

    Serial.println("Wifi init");
    WiFi.begin(ssid, password);  //Connect to the WiFi network
    while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
        delay(500);
        Serial.println("Waiting to connect...");
    }
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  //Print the local IP
    server.on("/colors.json", std::bind(&Http::handle_request, this)); //Associate the handler function to the path
    server.begin(); //Start the server
    Serial.println("Server listening");
}

void Http::loop() {
    server.handleClient(); //Handling of incoming requests
}