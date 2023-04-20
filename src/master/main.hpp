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
#include "data_struct.hpp"
const char *ssid = USERNAME;
const char *password = PASSWORD;
static const char *PARAM_MESSAGE="message";
static const char *Header = "<!DOCTYPE html>\n"
"<html lang=\"en\">\n"
"\n"
"<head>\n"
"  \n"
"  <meta charset=\"UTF-8\" />\n"
"  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />\n"
"  <title>Browser</title>\n"
"  <style>\n"
"      body {\n"
"      margin: 20px;\n"
"    }\n"
"\t table,th,td{\n"
"\n"
"        text-align:center;\n"
"        border-radius: 10px;\n"
"        border: 2px solid;\n"
"        padding: 2px; \n"
"        width: 2px;\n"
"        height: 1px;\n"
"    \tbackground-colour:#71deec;\n"
"    }  \t\n"
"\n"
"    th{\n"
"        background-color: #1ecbe1;\n"
"        color: #052529;\n"
"    }\n"
"  </style>\n"
"</head>\n"
"\n"
"<body>\n"
" <table style=\"width:100%\">";
