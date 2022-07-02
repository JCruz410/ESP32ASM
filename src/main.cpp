#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>



const char* ssid = "ur wifi";
const char* password = "ur pass";

const int DIR = 12;
const int STEP = 14;
const int  steps_per_rev = 200;

WiFiServer server(80);


void setup() 
{
 Serial.begin(9600);
 pinMode(STEP, OUTPUT);
 pinMode(DIR, OUTPUT);
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
 /*server.on("", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Hello World");

 }); */


 server.begin();


}


int value = 0;

void loop() 
{
   WiFiClient client = server.available();

   if (!client) 
   {
      return;
   }

   Serial.println("New Client."); 

  while(!client.available()) 
   {
      delay(1);
   }

   String request = client.readStringUntil('\r');
   Serial.print(request);

   // motor code

   if(request.indexOf("STEP") != -1)
   {
      digitalWrite(STEP, !digitalRead(STEP));
   }

   if(request.indexOf("DIR") != -1)
   {
      digitalWrite(DIR, !digitalRead(DIR));
   }

 

   client.println("HTTP/1.1 200 OK");
   client.println("Content-type:text/html");
   client.println("");
   delay(1);


}