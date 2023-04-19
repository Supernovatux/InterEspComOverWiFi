#include "main.hpp"
AsyncWebServer server(80);
String webpage = "";
char JsonTxt[2046];
void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}
DynamicJsonDocument doc(2048);
devices newdev;
void setup() {
  Serial.begin(BAUD_RATE);
  newdev.saneDefaults();
  newdev.devicesTojson(doc);
  serializeJson(doc, JsonTxt);
  WiFi.softAPConfig(IPAddress(192, 168, DEVICE+1, 1), IPAddress(192, 168, DEVICE+1, 1),
                    IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);

  server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "application/json", JsonTxt);
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", webpage);
  });

  server.onNotFound(notFound);

  server.begin();
}

void loop() {
  webpage="";
  webpage+=Header;
  for(int i=0;i<2;i++){
     webpage+="<tr>";
     webpage+="<th>";
     webpage+=String("<p> Device ")+String(i)+String("</p></th>");
     for(int j=0;j<5;j++){
       
      webpage+="<th> \n";       
        if(newdev.nodes[i].sensors[j].status){
        webpage +=String("<p> LED: ON</p><a class=\"button button-off\" href=\"/ledoff?message=")+String(i)+String(",")+String(j)+String("\">OFF</a>\n");
        }else{
        webpage +=String("<p> LED: OFF</p><a class=\"button button-on\" href=\"/ledon?message=")+String(i)+String(",")+String(j)+String("\">ON</a>\n");
        } 
      webpage+="</th>";
      
     }
  webpage+="</tr>"; 
  
  }
  delay(3000);
  newdev.devicesTojson(doc);
  serializeJson(doc, JsonTxt);


}