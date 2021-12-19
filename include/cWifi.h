#ifndef CWIFI_H
#define CWIFI_H

#include <Arduino.h>

// const char *ssid = "AstreptoAccessPointPhone";
// const char *password = "Astrepto";

void wifi_begin();
void wifi_updateTime();
int wifi_get_minute();
int wifi_get_hour();
int wifi_get_day();
String wifi_get_url(String URL);
void wifi_post_url(String URL, char* data);



#endif