#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>


const char* ssid = "wifi";
const char* password = "pass";

AsyncWebServer server(80);


void setup() 
{
 Serial.begin(9600);
 delay(10);

// connect to wifi
 WiFi.begin(ssid, password);

 while (WiFi.status() != WL_CONNECTED)
 {
    delay(1000);
    Serial.println("Connecting to WiFi....");
 }

// serial monitor prints ip address
 Serial.println(WiFi.localIP());

 // type ip address into web browser to confirm "hello world" print connection
 server.on("", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Hello World");

 });

 server.begin();


}




void loop() {

}