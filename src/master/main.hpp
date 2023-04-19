#pragma once
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
#include "data_struct.hpp"
const char *ssid = USERNAME;
const char *password = PASSWORD;
const char *PARAM_MESSAGE = "body";