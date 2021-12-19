#ifndef CWIFI_H
#define CWIFI_H

#include <Arduino.h>

// const char *ssid = "AstreptoAccessPointPhone";
// const char *password = "Astrepto";




class cWifi
{
    public:
        void begin();
        void updateTime();
        String get(String URL);
        void post(String URL, char* data);
    private:

};


#endif