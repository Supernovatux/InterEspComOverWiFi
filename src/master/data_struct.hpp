#pragma once
#include <Arduino.h>
#define ARDUINOJSON_USE_LONG_LONG 0
#define ARDUINOJSON_USE_DOUBLE 0
#include <ArduinoJson.h>
#include <Vector.h>
#define SERVO 0
#define LED1 1
#define LED2 2
#define LED3 3
#define LED_BUILTIN_T 4

class sensor {
public:
  sensor() { sensor(SERVO, 90); }
  sensor(long id, int status) : id(id), status(status){};
  long id;
  long status;
};

class device {
public:
  device() { device(DEVICE); }
  device(long id) : id(id) {};
  long id;
  sensor sensors[NUM_SENSOR];
};

class devices {
public:
  devices() {}
  void saneDefaults();
  device nodes[NUM_DEV];
  void devicesTojson(DynamicJsonDocument &doc);
};