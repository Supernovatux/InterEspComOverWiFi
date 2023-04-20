#pragma once
#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <StringSplitter.hpp>
#include <WiFiClient.h>
#include <data_struct.hpp>
#include <webpage_builder.hpp>
const char* ssid = USERNAME;
const char* password = PASSWORD;
static const char* PARAM_MESSAGE = "message";
void initNodeMCU()
{
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(D4, OUTPUT);
    Serial.begin(BAUD_RATE);
    WiFi.softAPConfig(IPAddress(192, 168, DEVICE + 1, 1),
        IPAddress(192, 168, DEVICE + 1, 1),
        IPAddress(255, 255, 255, 0));
}
