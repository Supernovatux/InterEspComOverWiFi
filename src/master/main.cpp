#include "main.hpp"
AsyncWebServer server(80);
String message = "";
void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}
StaticJsonDocument<2048> doc;
void setup() {
  devices newdev;
  newdev.saneDefaults();
  newdev.devicesTojson(doc);
  serializeJson(doc, message);
  Serial.begin(BAUD_RATE);
  WiFi.softAP(ssid, password);
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "application/json", message);
  });

  // Send a GET request to <IP>/get?message=<message>
  server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hello, GET: " + message);
  });

  // Send a POST request to <IP>/post with a form field message set to <message>
  server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request) {
    if (request->hasParam(PARAM_MESSAGE, true)) {
      message = request->getParam(0)->value();
      Serial.println(message);
    }
    request->send(200, "text/plain", "Hello, POST: " + message);
  });

  server.onNotFound(notFound);

  server.begin();
}

void loop() {}