#include <main.hpp>
const char* serverName = "http://192.168.1.1/get";
devices* devicesHAL;
String serialInp = "";
void setup()
{
    initNodeMCU();
    serialInp.reserve(100);
    devicesHAL = new devices;
    WiFi.begin(ssid, password);
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

void loop()
{
    // Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("WiFi Connected");
        WiFiClient client;
        HTTPClient http;
        Serial.println("connecting to " + String(serverName));
        http.begin(client, serverName);
        Serial.println("requesting URL: ");
        delay(1000);
        int httpResponseCode = http.GET();
        Serial.println("HTTP Response code: " + String(httpResponseCode));
        if (httpResponseCode > 0) {
            serialInp = http.getString();
            Serial.println("HTTP Response: ");
        }
        http.end();
    } else
        Serial.println("WiFi Disconnected");
    devicesHAL->textTodevices(serialInp);
    Serial.println(serialInp);
    devicesHAL->changeHardware();
}