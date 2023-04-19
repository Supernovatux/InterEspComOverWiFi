//
// A simple server implementation showing how to:
//  * serve static messages
//  * read GET and POST parameters
//  * handle missing pages / 404s
//

#include <Arduino.h>
#include <ArduinoJson.h>
#ifdef ESP32
#include <AsyncTCP.h>
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#ifndef BAUD_RATE
#define BAUD_RATE 9600
#endif
#ifndef USERNAME
#define USERNAME "admin"
#endif
#ifndef PASSWORD
#define PASSWORD "qwerty123"
#endif
AsyncWebServer server(80);
const char *ssid = USERNAME;
const char *password = PASSWORD;
String message = "";
const char *PARAM_MESSAGE = "body";
void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}
StaticJsonDocument<512> doc;
void setup() {
  JsonArray devices = doc.createNestedArray("devices");
  JsonObject devices_0 = devices.createNestedObject();
  devices_0["id"] = 0;

  JsonArray devices_0_sensors = devices_0.createNestedArray("sensors");

  JsonObject devices_0_sensors_0 = devices_0_sensors.createNestedObject();
  devices_0_sensors_0["sensorID"] = 0;
  devices_0_sensors_0["value"] = 45;

  JsonObject devices_0_sensors_1 = devices_0_sensors.createNestedObject();
  devices_0_sensors_1["sensorID"] = 1;
  devices_0_sensors_1["value"] = 60;

  JsonObject devices_0_sensors_2 = devices_0_sensors.createNestedObject();
  devices_0_sensors_2["sensorID"] = 2;
  devices_0_sensors_2["value"] = 45;

  JsonObject devices_0_sensors_3 = devices_0_sensors.createNestedObject();
  devices_0_sensors_3["sensorID"] = 3;
  devices_0_sensors_3["value"] = 45;

  JsonObject devices_1 = devices.createNestedObject();
  devices_1["id"] = 1;

  JsonArray devices_1_sensors = devices_1.createNestedArray("sensors");

  JsonObject devices_1_sensors_0 = devices_1_sensors.createNestedObject();
  devices_1_sensors_0["sensorID"] = 0;
  devices_1_sensors_0["value"] = 45;

  JsonObject devices_1_sensors_1 = devices_1_sensors.createNestedObject();
  devices_1_sensors_1["sensorID"] = 1;
  devices_1_sensors_1["value"] = 60;

  JsonObject devices_1_sensors_2 = devices_1_sensors.createNestedObject();
  devices_1_sensors_2["sensorID"] = 2;
  devices_1_sensors_2["value"] = 45;

  JsonObject devices_1_sensors_3 = devices_1_sensors.createNestedObject();
  devices_1_sensors_3["sensorID"] = 3;
  devices_1_sensors_3["value"] = 45;

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