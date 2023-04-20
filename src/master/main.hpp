#pragma once
#include <Arduino.h>
#define ARDUINOJSON_USE_LONG_LONG 0
#define ARDUINOJSON_USE_DOUBLE 0
#include <ArduinoJson.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <data_struct.hpp>
#include <StringSplitter.hpp>
#include <webpage.h>
const char *ssid = USERNAME;
const char *password = PASSWORD;
static const char *PARAM_MESSAGE="message";
