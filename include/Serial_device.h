#ifndef SERIAL_DEVICE_H
#define SERIAL_DEVICE_H

#include <Arduino.h>

class Serial_device{
    private:

    public:
        void start_communication();
        void send_time();

    // ====== not used for now ======
/*         String receive();
        uint8_t available();
        void flush();
        long parseNumber(); */
};


#endif