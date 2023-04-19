#include "main.hpp"
const char *serverName = "http://192.168.1.1/get";
String serialInp = "";
unsigned long lastTime = 0;
unsigned long timerDelay = 2000;

void setup()
{
  Serial.begin(BAUD_RATE);
  WiFi.begin(ssid, password);
  WiFi.softAPConfig(IPAddress(192, 168, DEVICE + 1, 1), IPAddress(192, 168, DEVICE + 1, 1),
                    IPAddress(255, 255, 255, 0));
  WiFi.softAP(String("NodeMCU") + String(DEVICE), "12345678", DEVICE);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  if ((millis() - lastTime) > timerDelay)
  {
    // Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED)
    {
      WiFiClient client;
      HTTPClient http;
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
      int httpResponseCode = http.GET();
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      if (httpResponseCode > 0)
      {
        serialInp = http.getString();
      }
      http.end();
    }
    else
      Serial.println("WiFi Disconnected");
    DeserializationError error = deserializeJson(doc, serialInp);

    if (error)
    {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
    }
    else
    {
      for (JsonObject device : doc["devices"].as<JsonArray>())
      {

        if (device["id"]!=DEVICE) {
          Serial.println("Not this device");
          continue;
        }

        for (JsonObject device_sensor : device["sensors"].as<JsonArray>())
        {
          int device_sensor_sensorID = device_sensor["sensorID"];
          int device_sensor_value = device_sensor["value"];
          if(device_sensor_sensorID==LED_BUILTIN_T){
            digitalWrite(LED_BUILTIN, device_sensor_value);
          }else if (device_sensor_sensorID==LED1){
            digitalWrite(D1, device_sensor_value);
          }else if (device_sensor_sensorID==LED2){
            digitalWrite(D2, device_sensor_value);
          }else if (device_sensor_sensorID==LED3){
            digitalWrite(D3, device_sensor_value);
          }else if (device_sensor_sensorID==SERVO){
          }
        }
      }
    }

    lastTime = millis();
  }
}