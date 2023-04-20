#include "data_struct.hpp"
void devices::saneDefaults() {
  for (int i = 0; i < NUM_DEV; i++) {
    this->nodes[i] = device(i);
    for (int j = 0; j < NUM_SENSOR; j++) {
      this->nodes[i].sensors[j] = sensor(j, 90);
    }
  }
}
void devices::devicesTojson(DynamicJsonDocument &doc) {
  JsonArray devices = doc.createNestedArray("devices");
  for (auto i = this->nodes; i < this->nodes + NUM_DEV; i++) {
    JsonObject devices_0 = devices.createNestedObject();
    devices_0["id"] = i->id;
    JsonArray devices_0_sensors = devices_0.createNestedArray("sensors");
    for (sensor *j = i->sensors; j < i->sensors + NUM_SENSOR; j++) {
      JsonObject devices_0_sensors_0 = devices_0_sensors.createNestedObject();
      devices_0_sensors_0["sensorID"] = j->id;
      devices_0_sensors_0["value"] = j->status;
    }
  }
}