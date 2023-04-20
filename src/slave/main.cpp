#include "main.hpp"
const char *serverName = "http://192.168.1.1/get";
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;
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
String serialInp = "";
void setup() {
  serialInp.reserve(4096);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  Serial.begin(BAUD_RATE);
  WiFi.begin(ssid, password);
  WiFi.softAPConfig(IPAddress(192, 168, DEVICE + 1, 1),
                    IPAddress(192, 168, DEVICE + 1, 1),
                    IPAddress(255, 255, 255, 0));
  WiFi.softAP(String("NodeMCU") + String(DEVICE), "12345678", DEVICE);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    // Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
      int httpResponseCode = http.GET();
      if (httpResponseCode > 0) {
        serialInp = "";
        serialInp = http.getString();
      }
      http.end();
    } else
      Serial.println("WiFi Disconnected");
    DeserializationError error = deserializeJson(doc, serialInp);
    Serial.println(serialInp);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
    } else {
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
          changeHardware(DEVICE, device_sensor_sensorID, device_sensor_value);
        }
      }
    }

    lastTime = millis();
  }
}