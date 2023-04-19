#include "data_struct.hpp"
void devices::saneDefaults() {
  this->nodes.push_back(device(1));
  this->nodes.push_back(device(2));
  for (device &i : this->nodes) {
    i.sensors.push_back(sensor(SERVO, 90));
    i.sensors.push_back(sensor(LED_BUILTIN_T, 90));
    i.sensors.push_back(sensor(LED1, 0));
    i.sensors.push_back(sensor(LED2, 0));
    i.sensors.push_back(sensor(LED3, 0));
  }
}
void devices::devicesTojson(StaticJsonDocument<2048> &doc) {
  JsonArray devices = doc.createNestedArray("devices");
  for (device &i : nodes) {
    JsonObject devices_0 = devices.createNestedObject();
    devices_0["id"] = i.id;
    JsonArray devices_0_sensors = devices_0.createNestedArray("sensors");
    for (sensor &j : i.sensors) {
      JsonObject devices_0_sensors_0 = devices_0_sensors.createNestedObject();
      devices_0_sensors_0["sensorID"] = j.id;
      devices_0_sensors_0["value"] = j.status;
    }
  }
}