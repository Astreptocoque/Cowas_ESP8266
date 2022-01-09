
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "cWifi.h" // custom Wifi¨
#include <ArduinoJson.h>
#include <NTPClient.h>
#include "WiFiUdp.h"
#include "Serial_device.h"
#include "GPIO.h"


using namespace std;
extern Serial_device serial;
extern GPIO wifi_connection_led;

int currentMinute;
int currentHour;
int currentWeekday;
uint32_t currentEpoch;          // seconds since 1 january 1970

// Write here wifi settings
const char *ssid = "AstreptoAccessPointPhone";
const char *password = "Astrepto";

// define ntp client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org");

//Your Domain name with URL path or IP address with path
const String serverCowas = "http://128.179.146.212:5000";
const String serverTime = "http://www.google.com";
// StaticJsonBuffer<300> JSONbuffer;
// JsonObject& JSONencoder = JSONbuffer.createObject();

void wifi_begin(){

    wifi_connection_led.on();

    WiFi.begin(ssid, password);
    // Serial.println("Connecting to network " + String(ssid));
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        // Serial.print(".");
    }
    // Serial.println("Connected to local Wifi");
    // Serial.println(WiFi.localIP());

    wifi_connection_led.off();

    // init ntp
    timeClient.begin();
    timeClient.setTimeOffset(3600);
}

void wifi_updateTime()
{
    timeClient.update();
    currentHour = timeClient.getHours();
    currentMinute = timeClient.getMinutes();
    currentWeekday = timeClient.getDay();
    currentEpoch = timeClient.getEpochTime();
}

int wifi_get_minute(){
    return currentMinute;
}
int wifi_get_hour(){
    return currentHour;
}
int wifi_get_day(){
    return currentWeekday;
}

uint32_t wifi_get_epoch(){
    return currentEpoch;
}

String wifi_get_url(String URL)
{
    //Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED)
    {
        WiFiClient client;
        HTTPClient http;

        String serverPath = serverCowas + URL; //"control/?query=led";
        Serial.println(serverPath);

        // Your Domain name with URL path or IP address with path
        http.begin(client, serverPath.c_str());

        // Send HTTP GET request
        int httpResponseCode = http.GET();
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
        // Free resources
        http.end();
        if (httpResponseCode == 200)
        {
            return payload;
        }
        else
        {
            Serial.println("HTTP error code -  bad get");
            return "error";
        }
    }
    else
    {
        return "error";
    }
}

void wifi_post_url(String URL, char *data)
{
    //https://arduinojson.org/v6/doc/upgrade/
    //With esp8266http use arduinojson v5

    // StaticJsonBuffer<300> JSONbuffer;

    //Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED)
    {
        // ======================================================
        // ======================================================
        WiFiClient client;
        HTTPClient http;

        String serverPath = serverCowas + URL;
        Serial.println(serverPath);

        // Your Domain name with URL path or IP address with path
        http.begin(client, serverPath.c_str());

        // Send HTTP GET request
        http.addHeader("Content-Type", "application/json");
        // String postData = "button_state=" + data + "&";
        int httpResponseCode = http.POST(data);
        String payload = http.getString();
        if (httpResponseCode == 200)
        {
            Serial.println(payload); //Print request response payload
        }
        else
        {
            Serial.println("HTTP error code -  bad post");
        }
        // Free resources
        http.end();
    }
    else
    {
        Serial.println("WiFi Disconnected");
    }
}
