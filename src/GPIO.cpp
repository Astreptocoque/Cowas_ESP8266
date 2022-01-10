#include <Arduino.h>
#include "../include/GPIO.h"

void GPIO::begin(byte _pin, byte _mode)
{
    pin = _pin;
    mode = _mode;
    pinMode(pin, (_mode == input_mode ? INPUT:OUTPUT));
    off();
}

void GPIO::begin(byte _control_pin, byte _mode, String _ID)
{
    ID = _ID;
    pin = _control_pin;
    mode = _mode;
    pinMode(pin, (_mode == input_mode ? INPUT:OUTPUT));
    if(mode == output_mode)
        off();
}

void GPIO::on()
{
    digitalWrite(pin, HIGH);
    state = 1;
}

void GPIO::off()
{
    digitalWrite(pin, LOW);
    state = 0;
}

byte GPIO::read()
{
    state = digitalRead(pin);
    return state;
}