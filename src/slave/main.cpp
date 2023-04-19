#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncTCP.h>
#include <WiFiClient.h>

const char *ssid = USERNAME;
const char *password = PASSWORD;
const char *serverName = "http://192.168.4.1/";
String serialInp = "";
unsigned long lastTime = 0;
unsigned long timerDelay = 2000;

void setup() {
  Serial.begin(BAUD_RATE);
  WiFi.begin(ssid, password);
  WiFi.softAPConfig(IPAddress(192, 168, DEVICE+1, 1), IPAddress(192, 168, DEVICE+1, 1),
                    IPAddress(255, 255, 255, 0));
  WiFi.softAP(String("NodeMCU") + String(DEVICE), "12345678",DEVICE);
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
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      http.end();
    } else
      Serial.println("WiFi Disconnected");
    lastTime = millis();
  }
}