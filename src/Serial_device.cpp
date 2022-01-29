#include "Serial_device.h"
#include "cWifi.h"
#include "GPIO.h"

#define LF 0x0A //ASCII
#define CR 0x0D //ASCII

extern GPIO message_line;

char data[10]; 
int idx;

/**
 * @brief "Protocol" to start communication with device
 * 
 */
void Serial_device::start_communication(){
    // wait for first incoming data
    message_line.on();
    while(Serial.parseInt() != 1234){
        while(Serial.available() == 0);
        delay(5);
    }
    message_line.off();
}

void Serial_device::send_time(){
    // TODO : send time via JSON
    Serial.println(String(wifi_get_epoch()));
}


// ====== NOT USED FOR NOW --> use ArduionJSON =======
/* void read_string(){
if (Serial.available() > 0) {
    data[idx] = Serial1.read();
    if (data[idx] == LF) {
        data[idx-1] = 0;
        action(angle_str);
        idx = -1;
        }
    idx++;
    }
}

String Serial_device::receive(){
    return Serial.readString();
}

uint8_t Serial_device::available(){
    return Serial.available();
}

void Serial_device::flush(){
    Serial.flush();
}

long Serial_device::parseNumber(){
    return Serial.parseInt();
} */