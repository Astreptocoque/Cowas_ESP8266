#ifndef GPIO_H
#define GPIO_H
#include <Arduino.h>

enum pin_mode{input_mode, output_mode};

class GPIO
{
    private:
    byte pin;
    byte mode;
    byte state;
    String ID = "no id";

  public:
    void begin(byte _pin, byte _mode);
    void begin(byte _pin, byte _mode, String _ID);
    void on();
    void off();
    byte read();
};
#endif