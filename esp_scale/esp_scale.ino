#include <ESP8266WiFi.h>

#include "HX711.h"

HX711 scale;

WiFiServer server(80);

void setup() {
    Serial.begin(115200);
    Serial.println();
        
    scale.begin(5, 4);

    WiFi.mode(WIFI_STA);
    WiFi.begin("newnham1_a", "bernardnewnham333");
    Serial.print("Connecting...");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("WiFi connected"); 
    server.begin();  // Starts the Server
    Serial.println("Server started");
}

void loop() {
  
  int value;
   value = scale.read_average(10);
   value = (113300 - value)/104.6;
    Serial.println(value);

 WiFiClient client = server.available();

  client.println("HTTP/1.1 200 OK"); //
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<style>");
  client.println("h1 {text-align: center;}");
  client.println("p {text-align: center;}");
  client.println("div {text-align: center;}");
  client.println("</style>");
  client.println("</head>");
  
  client.println("<br><br>");
  client.print("<p style=\"font-size:30px\", \"font-family:verdana;\">Current Weight: </p> ");
  client.print("<p style=\"font-size:30px\">  ");
  client.println(value);
 client.print("gm</p> ");

  client.println("</html>");

  return;

}
