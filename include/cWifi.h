#ifndef CWIFI_H
#define CWIFI_H

#include <Arduino.h>

void wifi_begin();
void wifi_start_NTP();
void wifi_updateTime();
uint32_t wifi_get_epoch();
String wifi_get_url(String URL);
void wifi_post_url(String URL, char* data);

#endif