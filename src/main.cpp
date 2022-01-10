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
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include "cWifi.h"
#include "Serial_device.h"
#include "GPIO.h"


#define COMMUNICATION_PIN 12    // pin to engage conversation
#define WIFI_CONNECTION_LED 13

GPIO wifi_connection_led;       // led to indicate when connecting to wifi
GPIO message_line;              // output to signal presence to main board

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 1000;

Serial_device due;

StaticJsonBuffer<300> JSONbuffer;
JsonObject& JSONencoder = JSONbuffer.createObject();
String payload;

void setup()
{
    Serial.begin(115200);
    wifi_connection_led.begin(WIFI_CONNECTION_LED, OUTPUT);
    message_line.begin(COMMUNICATION_PIN, OUTPUT);

    
    wifi_begin();
    due.start_communication();
    wifi_updateTime();
    due.send_time();
    due.validation(); 
   
}

void loop()
{
    
    // wifi.updateTime();
    // serial.send()
   
    delay(500);
    // StaticJsonBuffer<300> JSONbuffer;
    // JsonObject& JSONencoder = JSONbuffer.createObject();
    // JSONencoder["sensor"] = "button";
    // JSONencoder["value"] = digitalRead(pin_button);
    // char JSONmessageBuffer[300];
    // JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    // Serial.println(JSONmessageBuffer);
    
    // wifi.post("/update", JSONmessageBuffer);
    // payload = wifi.get("/control/?query=led");
    // digitalWrite(pin_led, payload.toInt());
    // delay(2000);

}