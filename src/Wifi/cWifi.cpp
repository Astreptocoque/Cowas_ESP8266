
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "cWifi.h" // custom Wifi¨
#include <ArduinoJson.h>

#define NB_KNOWN_WIFI

using namespace std;

// Write here wifi settings
const char *ssid = "AstreptoAccessPointPhone";
const char *password = "Astrepto";

//Your Domain name with URL path or IP address with path
const String serverName = "http://128.179.146.212:5000";
// StaticJsonBuffer<300> JSONbuffer;
// JsonObject& JSONencoder = JSONbuffer.createObject();

void cWifi::begin()
{

    WiFi.begin(ssid, password);
    Serial.println("Connecting to network " + String(ssid));
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to local Wifi");
    Serial.println(WiFi.localIP());
};

String cWifi::get(String URL)
{
    //Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED)
    {
        WiFiClient client;
        HTTPClient http;

        String serverPath = serverName + URL; //"control/?query=led";
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
};

void cWifi::post(String URL, char* data)
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

        String serverPath = serverName + URL;
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
};
