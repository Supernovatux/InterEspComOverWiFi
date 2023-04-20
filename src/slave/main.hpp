#pragma once
#include <Arduino.h>
#define ARDUINOJSON_USE_LONG_LONG 0
#define ARDUINOJSON_USE_DOUBLE 0
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFiClient.h>
#include <data_struct.hpp>
DynamicJsonDocument doc(2048);
const char *ssid = USERNAME;
const char *password = PASSWORD;
#include <webpage.h>