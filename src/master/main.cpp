#include "main.hpp"
#include "StringSplitter.hpp"
AsyncWebServer server(80);
String webpage = "";
char JsonTxt[2046];
void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
};
DynamicJsonDocument doc(2048);
devices newdev;
void setup()
{
  Serial.begin(BAUD_RATE);
  newdev.saneDefaults();
  newdev.devicesTojson(doc);
  serializeJson(doc, JsonTxt);
  WiFi.softAPConfig(IPAddress(192, 168, DEVICE + 1, 1), IPAddress(192, 168, DEVICE + 1, 1),
                    IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);

  server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "application/json", JsonTxt); });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/html", webpage); });
  server.on("/ledoff", HTTP_ANY, [](AsyncWebServerRequest *request)
            {
    String message;
        if (request->hasParam(PARAM_MESSAGE)) {
            message = request->getParam(PARAM_MESSAGE)->value();
        } else {
            message = "No message sent";
        }
        StringSplitter* msg=new StringSplitter(message,',',2);
        int i=msg->getItemAtIndex(0).toInt();
        int j=msg->getItemAtIndex(1).toInt();
        newdev.nodes[i].sensors[j].status=0;
      request->redirect("/"); });
  server.on("/ledon", HTTP_ANY, [](AsyncWebServerRequest *request)
            {
    String message;
        if (request->hasParam(PARAM_MESSAGE)) {
            message = request->getParam(PARAM_MESSAGE)->value();
        } else {
            message = "No message sent";
        }
        StringSplitter* msg=new StringSplitter(message,',',2);
        int i=msg->getItemAtIndex(0).toInt();
        int j=msg->getItemAtIndex(1).toInt();
        newdev.nodes[i].sensors[j].status=1;
      request->redirect("/"); });

  server.onNotFound(notFound);

  server.begin();
}

void loop()
{
  webpage = Header;
  webpage += "<tr>";
  for (int i = 0; i < 2; i++)
  {
    webpage += "<th>";
    webpage += String("<p> Device ") + String(i) + String("</p></th>");
  }
  webpage += "</tr>";

  for (int j = 0; j < 5; j++)
  {
    webpage += "<tr>";
    for (int i = 0; i < 2; i++)
    {
      webpage += "<td>";
      if (newdev.nodes[i].sensors[j].status)
      {
        webpage += String("<p> LED: ON</p><a class=\"button button-off\" href=\"/ledoff?message=") + String(i) + String(",") + String(j) + String("\">OFF</a>\n");
      }
      else
      {
        webpage += String("<p> LED: OFF</p><a class=\"button button-on\" href=\"/ledon?message=") + String(i) + String(",") + String(j) + String("\">ON</a>\n");
      }
      webpage += "</td>";
    }
  }
  webpage += "</tr></table>";
delay(1000);
newdev.devicesTojson(doc);
serializeJson(doc, JsonTxt);
}