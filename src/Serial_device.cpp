#include "Serial_device.h"
#include "cWifi.h"

void Serial_device::start_communication(){
    // wait for first incoming data
    while(Serial.available() == 0);
    if(Serial.parseInt() != 1){
        // turn led on
    }
    Serial.print("2");
    while(Serial.available() == 0);
    if(Serial.parseInt() != 3){
        // turn led on
    }
}

void Serial_device::send_time(){
    Serial.print(String(wifi_get_hour()) + " ");
    Serial.print(String(wifi_get_minute()) + " ");
    Serial.print(String(wifi_get_day()) + " ");
}

void Serial_device::validation(){
    while(Serial.available() == 0);
    if(Serial.parseInt() != 1){
        // turn led on
    }
    Serial.print("1");
}

// String Serial_device::receive(){
//     return Serial.readString();
// }

// uint8_t Serial_device::available(){
//     return Serial.available();
// }

// void Serial_device::flush(){
//     Serial.flush();
// }

// long Serial_device::parseNumber(){
//     return Serial.parseInt();
// }