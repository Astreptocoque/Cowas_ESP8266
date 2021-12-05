#ifndef CWIFI_H
#define CWIFI_H

#include <Arduino.h>

// const char *ssid = "AstreptoAccessPointPhone";
// const char *password = "Astrepto";

// Write here all knows Wifi networks
char *WifiDatabase[2][2] = {
    {"test", "salut"},
    {"AstreptoAccessPointPhone", "Astrepto"}
    };

//Your Domain name with URL path or IP address with path
const String serverName = "http://128.179.145.245:5000/";


class cWifi
{
    public:
        void begin();
        String get(String URL);
        void post(String URL, String data);
    private:

};


#endif