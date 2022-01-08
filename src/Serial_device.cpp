#include "Serial_device.h"
#include "cWifi.h"


#define LF          0x0A 
#define CR          0x0D

char data[10]; 
int idx;

void Serial_device::start_communication(){
    // wait for first incoming data
    digitalWrite(12, HIGH);
    while(Serial.parseInt() != 1234){
        while(Serial.available() == 0);
        delay(5);
    }
}

void Serial_device::send_time(){
    Serial.println(String(wifi_get_hour()));
    Serial.println(String(wifi_get_minute()));
    Serial.println(String(wifi_get_day()));
}

void Serial_device::validation(){
    while(Serial.available() == 0);
    if(Serial.parseInt() != 1){
        // turn led on
    }
    Serial.print("1");
}

// void read_string(){
// if (Serial.available() > 0) {
//     data[idx] = Serial1.read();
//     if (data[idx] == LF) {
//         data[idx-1] = 0;
//         action(angle_str);
//         idx = -1;
//         }
//     idx++;
//     }
// }

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