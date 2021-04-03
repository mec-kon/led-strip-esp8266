#include <Arduino.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <ElegantOTA.h>

#include "config.h"
#include "Http.h"
#include "SchedulerDefinitions.h"
#include "LED_Modes.h"

Scheduler runner;

void mqtt_loop(){
    //Serial.println(".");
}

Task http(TASK_IMMEDIATE, TASK_FOREVER, &http_thread);
Task mqtt(1000, TASK_FOREVER, &mqtt_loop);
Task led(TASK_IMMEDIATE, TASK_FOREVER, &led_loop);


void setup() {
    Serial.begin(115200);
    Serial.println("program started");

    pinMode(GPIO_RED, OUTPUT);
    pinMode(GPIO_GREEN, OUTPUT);
    pinMode(GPIO_BLUE, OUTPUT);

    runner.init();

    runner.addTask(http);
    runner.addTask(mqtt);
    runner.addTask(led);
    runner.addTask(fade_mode);
    runner.addTask(changing_colors_mode);

    http.enable();
    mqtt.enable();
    led.enable();

}

void loop() {
    runner.execute();
}
