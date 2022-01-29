/*
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-http-get-post-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  
  Code compatible with ESP8266 Boards Version 3.0.0 or above 
  (see in Tools > Boards > Boards Manager > ESP8266)
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "cWifi.h"
#include "Serial_device.h"
#include "GPIO.h"

// ========== PINS DEFINITIONS ============
#define COMMUNICATION_PIN 12
#define WIFI_CONNECTION_LED 13

// ========== GPIO DEFINITIONS ============
GPIO wifi_connection_led;       // led to indicate when connecting to wifi
GPIO message_line;              // output to signal new message to main board

Serial_device due;

uint32_t lastTime = 0;
uint32_t timerDelay = 1000;

// ======== ArduinoJSON V5 object =========
StaticJsonBuffer<300> JSONbuffer;
JsonObject& JSONencoder = JSONbuffer.createObject();
String payload;


void setup()
{
    Serial.begin(115200); // beware to have same speed on other device
    wifi_connection_led.begin(WIFI_CONNECTION_LED, OUTPUT);
    message_line.begin(COMMUNICATION_PIN, OUTPUT);
    
    // connect to Wi-Fi network
    wifi_begin();
    // start NTP librairie
    wifi_start_NTP();

    // init communication with DUE and send time
    due.start_communication();
    wifi_get_epoch();
    due.send_time();
}

void loop()
{
    
    // TODO : manage messages from other device, send message, get info from server

    // wifi.updateTime();
    // serial.send()
   
    // delay(500);
    // StaticJsonBuffer<300> JSONbuffer;
    // JsonObject& JSONencoder = JSONbuffer.createObject();
    // JSONencoder["sensor"] = "button";
    // JSONencoder["value"] = digitalRead(pin_button);
    // char JSONmessageBuffer[300];
    // JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    // Serial.println(JSONmessageBuffer);
    
    // wifi_get_url("/sample/");
    delay(2000);

}