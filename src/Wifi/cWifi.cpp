
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "cWifi.h" // custom Wifi¨
#include <ArduinoJson.h>

#define NB_KNOWN_WIFI

using namespace std;

void cWifi::begin()
{

    // time before connecting to another network
    int lastTime = millis();
    int timerDelay = 10000;
    bool connection_failed = 0;
    uint8_t i;

    for (i = 0; i < size(WifiDatabase); i++)
    {
        char *ssid = WifiDatabase[i][0];
        char *password = WifiDatabase[i][1];
        connection_failed = 0;
        WiFi.begin(ssid, password);
        Serial.println("Connecting to network " + String(i) + " (" + WifiDatabase[i][0] + ")");
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");

            if (millis() - lastTime > timerDelay)
            {
                connection_failed = 1;
                break;
            }
        }

        if (!connection_failed)
        {
            Serial.println("");
            Serial.print("Connected to WiFi network with IP Address: ");
            Serial.println(WiFi.localIP());
            break;
        }
    }

    // if no network connected
    if (i == size(WifiDatabase) - 1 && connection_failed)
    {
        Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        Serial.println("Connection to network failed");
        // retry in 5 minutes
    }
};

String cWifi::get(String URL)
{
    //Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED)
    {
        WiFiClient client;
        HTTPClient http;

        String serverPath = serverName + URL; //"control/?query=led";

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
            Serial.println("HTTP error code -  bad query");
            return "error";
        }
    }
};

void cWifi::post(String URL, String data){

     //Check WiFi connection status
        if (WiFi.status() == WL_CONNECTED)
        {
                  // ======================================================
            // ======================================================
            WiFiClient client;
            HTTPClient http;
            
            String serverPath = serverName + URL;

            // Your Domain name with URL path or IP address with path
            http.begin(client, serverPath.c_str());

            // Send HTTP GET request
            http.addHeader("Content-Type", "application/x-www-form-urlencoded");
            String postData = "button_state=" + data +"&";
            int httpResponseCode = http.POST(postData);
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
        lastTime = millis();
    
};
