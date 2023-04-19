#include "main.hpp"
AsyncWebServer server(80);
String webpage = "";
char JsonTxt[2046];
void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}
DynamicJsonDocument doc(2048);
devices newdev;
void setup() {
  Serial.begin(BAUD_RATE);
  newdev.saneDefaults();
  newdev.devicesTojson(doc);
  serializeJson(doc, JsonTxt);
  WiFi.softAPConfig(IPAddress(192, 168, DEVICE+1, 1), IPAddress(192, 168, DEVICE+1, 1),
                    IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);

  server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "application/json", JsonTxt);
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", webpage);
  });

  server.onNotFound(notFound);

  server.begin();
}

void loop() {
}