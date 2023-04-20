#include "main.hpp"
AsyncWebServer server(80);
String webpage = "";
char JsonTxt[4096];
void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
};
DynamicJsonDocument doc(2048);
devices newdev;
void changeHardware(int devId, int pin, int value) {
  if (devId == DEVICE) {
    if (pin == LED_BUILTIN_T) {
      digitalWrite(LED_BUILTIN, value);
    } else if (pin == LED1) {
      digitalWrite(D1, value);
    } else if (pin == LED2) {
      digitalWrite(D2, value);
    } else if (pin == LED3) {
      digitalWrite(D3, value);
    } else if (pin == SERVO) {
    }
  }
}
void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  Serial.begin(BAUD_RATE);
  newdev.saneDefaults();
  newdev.devicesTojson(doc);
  serializeJson(doc, JsonTxt);
  WiFi.softAPConfig(IPAddress(192, 168, DEVICE + 1, 1),
                    IPAddress(192, 168, DEVICE + 1, 1),
                    IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);

  server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "application/json", JsonTxt);
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", webpage);
  });
  server.on("/ledoff", HTTP_ANY, [](AsyncWebServerRequest *request) {
    String message;
    if (request->hasParam(PARAM_MESSAGE)) {
      message = request->getParam(PARAM_MESSAGE)->value();
    } else {
      message = "No message sent";
    }
    Serial.println(message);
    StringSplitter *msg = new StringSplitter(message, ',', 2);
    int i = msg->getItemAtIndex(0).toInt();
    int j = msg->getItemAtIndex(1).toInt();
    newdev.nodes[i].sensors[j].status = 0;
    changeHardware(i,j,0);
    request->redirect("/");
  });
  server.on("/ledon", HTTP_ANY, [](AsyncWebServerRequest *request) {
    String message;
    if (request->hasParam(PARAM_MESSAGE)) {
      message = request->getParam(PARAM_MESSAGE)->value();
    } else {
      message = "No message sent";
    }
    Serial.println(message);
    StringSplitter *msg = new StringSplitter(message, ',', 2);
    int i = msg->getItemAtIndex(0).toInt();
    int j = msg->getItemAtIndex(1).toInt();
    changeHardware(i,j,1);
    newdev.nodes[i].sensors[j].status = 1;

    request->redirect("/");
  });

  server.onNotFound(notFound);

  server.begin();
}

void loop() {
  
  webpage = Header;
  for (int i = 0; i < 2; i++) {
    webpage += "<th>";
    webpage += String("<p> Device ") + String(i) + String("</p></th>");
  }
  webpage += "</tr>";

  for (int j = 0; j < 5; j++) {
    webpage += "<tr>";
    for (int i = 0; i < 2; i++) {
      webpage += "<td>";
      if (newdev.nodes[i].sensors[j].status) {
        webpage += String("<p> LED: ON</p><a class=\"button button-off\" "
                          "href=\"/ledoff?message=") +
                   String(i) + String(",") + String(j) + String("\">OFF</a>\n");
      } else {
        webpage += String("<p> LED: OFF</p><a class=\"button button-on\" "
                          "href=\"/ledon?message=") +
                   String(i) + String(",") + String(j) + String("\">ON</a>\n");
      }
      webpage += "</td>";
    }
  }
  webpage += "</tr></table>";
  newdev.devicesTojson(doc);
  serializeJson(doc, JsonTxt);
  for (JsonObject device : doc["devices"].as<JsonArray>()) {

    if (device["id"] != DEVICE) {
      Serial.println("Not this device");
      continue;
    }

    for (JsonObject device_sensor : device["sensors"].as<JsonArray>()) {
      int device_sensor_sensorID = device_sensor["sensorID"];
      int device_sensor_value = device_sensor["value"];
      Serial.print("Device: ");
      Serial.print(DEVICE);
      Serial.print(", SensorID: ");
      Serial.print(device_sensor_sensorID);
      Serial.print(" Value ");
      Serial.println(device_sensor_value);
      changeHardware(DEVICE,device_sensor_sensorID,device_sensor_value);
    }
  }
}