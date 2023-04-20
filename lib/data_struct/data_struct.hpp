#pragma once
#include <Arduino.h>
#include <StringSplitter.hpp>
#define SERVO 0
#define LED1 1
#define LED2 2
#define LED3 3
#define LED_BUILTIN_T 4
#ifndef NUM_DEV
#define NUM_DEV 2
#define NUM_SENSOR 5
#endif
class sensor {
public:
    sensor() { sensor(SERVO, 90); }
    sensor(long id, int status)
        : id(id)
        , status(status) {};
    long id;
    long status;
};

class device {
public:
    device() { device(DEVICE); }
    device(long id)
        : id(id) {};
    long id;
    sensor sensors[NUM_SENSOR];
};

class devices {
public:
    devices() { }
    void saneDefaults();
    device nodes[NUM_DEV];
    void devicesTotext(String& doc);
    void textTodevices(String& doc);
    void changeHardware();
};
