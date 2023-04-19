#include "main.hpp"
StaticJsonDocument<2048> doc;
String message = "";
void setup() {
  devices newdev;
  newdev.saneDefaults();
  newdev.devicesTojson(doc);
  serializeJson(doc, message);
  Serial.begin(9600);
  Serial.print("IP Address: ");
  Serial.println(message);
}

void loop() {}