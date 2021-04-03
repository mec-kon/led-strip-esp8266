#include <TaskScheduler.h>
#include "Http.h"

const char *ssid = WLAN_SSID;
const char *password = PASSWORD;


ESP8266WebServer server(80);

// handle the http-post request
void handle_request() {
    if (server.hasArg("plain") == false) { //Check if body received
        server.sendHeader("Content-Type", "text/plain; charset=UTF-8");
        server.sendHeader("Content-Encoding", "UTF-8");
        server.sendHeader("Server", "mec-kon's C++Server/1.0 (Linux)");
        server.send(200, "text/plain", "body not received \n");

        Serial.println("data not received");
    }
    else {
        String message = server.arg("plain");

        server.sendHeader("Content-Type", "text/plain; charset=UTF-8");
        server.sendHeader("Content-Encoding", "UTF-8");
        server.sendHeader("Server", "mec-kon's C++Server/1.0 (Linux)");
        server.send(200, "text/plain", "data received \n");

        set_data(message);
        Serial.println("data received");
    }
}

// allow cross-origin resource sharing (https://developer.mozilla.org/en-US/docs/Web/HTTP/CORS)
void handle_cors_request() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Methods", "POST");
    server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
    server.sendHeader("Content-Type", "text/plain; charset=UTF-8");
    server.sendHeader("Content-Encoding", "UTF-8");
    server.sendHeader("Server", "mec-kon's C++Server/1.0 (Linux)");

    server.send(200, "text/plain", "");
    Serial.println("options received");
}

void handleRootPath() {
   server.send(200, "text/plain", "ESP8266 LED-Server");
}

// set up the wifi connection and start the webserver
void http_setup() {
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

    server.on("/colors.json", HTTP_POST, handle_request);
    server.on("/colors.json", HTTP_OPTIONS, handle_cors_request);
    server.on("/", handleRootPath);
    server.begin(); //Start the server
    Serial.println("Server listening");
}



// main thread that is called in a loop
void http_thread() {
    if(http.isFirstIteration()){
        http_setup();
    }
    server.handleClient(); //Handling of incoming requests
}
