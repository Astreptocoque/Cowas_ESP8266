/**
 * @file cWifi.cpp
 * @author Timothée Hirt
 * @brief Custom Wi-Fi class to handle all Internet related stuffs
 * @version 0.1
 * @date 2022-01-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "cWifi.h"
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
uint32_t currentEpoch; // seconds since 1 january 1970

// ============ WI-FI SETTINGS ================
const char *ssid = "AstreptoAccessPointPhone";
const char *password = "Astrepto";

// ============== NTP SETTINGS ================
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org");

// ============= SERVER SETTINGS ==============
const String serverCowas = "http://128.179.146.212:5000";

void wifi_begin()
{

    wifi_connection_led.on();

    WiFi.begin(ssid, password);
    uint32_t time1 = millis();
    while (WiFi.status() != WL_CONNECTED)
    {
        // sometimes (often) wifi is kinda blocked in a loop when connecting
        // this allows to reset the connection
        if (millis() - time1 > 5000)
        {
            WiFi.reconnect();
            time1 = millis();
        }
        delay(100);
    }
    wifi_connection_led.off();
}

void wifi_start_NTP()
{
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

/**
 * @brief Returne time in seconds since 01.01.1970
 *        TODO : return current time, use time librairy
 * 
 * @return uint32_t current time
 */
uint32_t wifi_get_epoch() { return currentEpoch; }

/**
 * @brief Send GET request
 *        Currently incompatible with ArduinoJson V6
 * 
 * @param URL 
 * @return String 
 */
String wifi_get_url(String URL)
{
    StaticJsonBuffer<300> JSONbuffer;

    // Check WiFi connection status
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
        JsonObject &myData = JSONbuffer.parseObject(payload);

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

/**
 * @brief Send POST requests
 *        Currently incompatible with ArduinoJson V6
 * 
 * @param URL 
 * @param data 
 */
void wifi_post_url(String URL, char *data)
{
    // https://arduinojson.org/v6/doc/upgrade/
    // With esp8266http use arduinojson v5

    // StaticJsonBuffer<300> JSONbuffer;

    // Check WiFi connection status
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
            Serial.println(payload); // Print request response payload
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
