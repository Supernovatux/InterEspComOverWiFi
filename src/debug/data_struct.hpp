#pragma once
#include <Arduino.h>
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
private:
  sensor storage_array[6];

public:
  device() { device(DEVICE); }
  device(long id) : id(id) { sensors = Vector<sensor>(storage_array); }
  long id;
  Vector<sensor> sensors;
};

class devices {
private:
  device storage_array[3];
public:
  devices() { nodes = Vector<device>(storage_array); }
  void saneDefaults();
  Vector<device> nodes;
  void devicesTojson(StaticJsonDocument<2048> &doc);
};