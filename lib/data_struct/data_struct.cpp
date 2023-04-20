#include "data_struct.hpp"
void devices::saneDefaults() {
  for (int i = 0; i < NUM_DEV; i++) {
    this->nodes[i] = device(i);
    for (int j = 0; j < NUM_SENSOR; j++) {
      this->nodes[i].sensors[j] = sensor(j, 1);
    }
  }
}
void devices::devicesTotext(String &doc) {
  doc = "";
  for (int i = 0; i < NUM_DEV; i++) {
    doc += String(nodes[i].id) + "S";
    for (int j = 0; j < NUM_SENSOR; j++) {
      doc += String(nodes[i].sensors[j].id) + "," + String(nodes[i].sensors[j].status) + ";";
    }
    doc += "|";
  }
}
void devices::textTodevices(String &doc) {
  StringSplitter *nodesSP = new StringSplitter(doc, '|', NUM_DEV);
  for(int i =0;i< NUM_DEV;i++) {
    StringSplitter *deviceSP = new StringSplitter(nodesSP->getItemAtIndex(i), 'S',2);
    this->nodes[i].id = deviceSP->getItemAtIndex(0).toInt();
    StringSplitter *sensorsSP = new StringSplitter(deviceSP->getItemAtIndex(1), ';', NUM_SENSOR);
    for(int j =0;j< NUM_SENSOR;j++) {
      StringSplitter *sensorSP = new StringSplitter(sensorsSP->getItemAtIndex(j), ',', 2);
      this->nodes[i].sensors[j].id = sensorSP->getItemAtIndex(0).toInt();
      this->nodes[i].sensors[j].status = sensorSP->getItemAtIndex(1).toInt();
      delete sensorSP;
    }
    delete sensorsSP;
  }
  delete nodesSP;
}
void devices::changeHardware() {
  digitalWrite(D0, this->nodes[DEVICE].sensors[0].status);
  digitalWrite(D1, this->nodes[DEVICE].sensors[1].status);
  digitalWrite(D2, this->nodes[DEVICE].sensors[2].status);
  digitalWrite(D3, this->nodes[DEVICE].sensors[3].status);
  digitalWrite(D4, this->nodes[DEVICE].sensors[4].status);
}