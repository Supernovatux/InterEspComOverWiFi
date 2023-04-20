#include <main.hpp>
AsyncWebServer server(80);
String webpage = "";
String TxtDoc;
void notFound(AsyncWebServerRequest* request)
{
    request->send(404, "text/plain", "Not found");
};
devices* devicesHAL;
void setup()
{
    initNodeMCU();
    devicesHAL = new devices();
    devicesHAL->saneDefaults();
    devicesHAL->devicesTotext(TxtDoc);
    WiFi.softAP(ssid, password);
    server.on("/get", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send(200, "text/plain", TxtDoc);
    });
    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send(200, "text/html", webpage);
    });
    server.on("/ledoff", HTTP_ANY, [](AsyncWebServerRequest* request) {
        String message;
        if (request->hasParam(PARAM_MESSAGE)) {
            message = request->getParam(PARAM_MESSAGE)->value();
        } else {
            message = "No message sent";
        }
        StringSplitter *msg = new StringSplitter(message, ',', 2);
        int i = msg->getItemAtIndex(0).toInt();
        int j = msg->getItemAtIndex(1).toInt();
        devicesHAL->nodes[i].sensors[j].status = 0;
        request->redirect("/");
        delete msg;
    });
    server.on("/ledon", HTTP_ANY, [](AsyncWebServerRequest* request) {
        String message;
        if (request->hasParam(PARAM_MESSAGE)) {
            message = request->getParam(PARAM_MESSAGE)->value();
        } else {
            message = "No message sent";
        }
        StringSplitter* msg = new StringSplitter(message, ',', 2);
        int i = msg->getItemAtIndex(0).toInt();
        int j = msg->getItemAtIndex(1).toInt();
        devicesHAL->nodes[i].sensors[j].status = 1;
        delete msg;
        request->redirect("/");
    });

    server.onNotFound(notFound);

    server.begin();
}

void loop()
{
    build_webpage(webpage, devicesHAL);
    devicesHAL->devicesTotext(TxtDoc);
    devicesHAL->changeHardware();
}