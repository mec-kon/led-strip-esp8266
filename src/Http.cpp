#include "Http.h"


ESP8266WebServer server(80);

Http::Http(Data *data, bool *new_message) {
    this->new_message = new_message;
    this->data = data;
}

void Http::parse_json(String *message) {
    StaticJsonDocument<800> JSONDocument;

    deserializeJson(JSONDocument, *message);

    JsonObject parsed = JSONDocument.as<JsonObject>();


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

void Http::handle_request() {
    if (server.hasArg("plain") == false) { //Check if body received
        server.sendHeader("Content-Type", "text/plain; charset=UTF-8");
        server.sendHeader("Content-Encoding", "UTF-8");
        server.sendHeader("Server", "mec-kon's C++Server/1.0 (Linux)");
        server.send(200, "text/plain", "body not received");

        Serial.println("data not received");
    }
    else {
        String message = server.arg("plain");

        server.sendHeader("Content-Type", "text/plain; charset=UTF-8");
        server.sendHeader("Content-Encoding", "UTF-8");
        server.sendHeader("Server", "mec-kon's C++Server/1.0 (Linux)");
        server.send(200, "text/plain", "data received");

        parse_json(&message);
        Serial.println("data received");
    }
}

void Http::handle_cors_request() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Methods", "POST");
    server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
    server.sendHeader("Content-Type", "text/plain; charset=UTF-8");
    server.sendHeader("Content-Encoding", "UTF-8");
    server.sendHeader("Server", "mec-kon's C++Server/1.0 (Linux)");

    server.send(200, "text/plain", "");
    Serial.println("options received");
}

void Http::setup() {
    Serial.println("http init");

    Serial.println("Wifi init");

    Serial.print("ESP Board MAC Address:  ");
    Serial.println(WiFi.macAddress());

    WiFi.begin(ssid, password);  //Connect to the WiFi network
    while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
        delay(500);
        Serial.println("Waiting to connect...");
    }

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  //Print the local IP

    server.on("/colors.json", HTTP_POST, std::bind(&Http::handle_request, this));
    server.on("/colors.json", HTTP_OPTIONS, std::bind(&Http::handle_cors_request, this));
    server.begin(); //Start the server
    Serial.println("Server listening");
}

void Http::loop() {
    server.handleClient(); //Handling of incoming requests
}
