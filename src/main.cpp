#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>



const char* ssid = "ur wifi";
const char* password = "ur pass";



// setting pin for direction on esp32
const int DIR = 12;

// setting pin for speed on esp32
const int STEP = 14;

// how long motor will spend in direction (higher = longer)
const int  steps_per_rev = 1500;

// establishing connection to server for esp32
WiFiServer server(80);


void setup() 
{
   //setting pins for motor and baud rate for esp32
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
   server.begin();
}


int value = 0;

void loop() 
{
   // print if app connections to esp32
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
        // clockwise direction = HIGH
        digitalWrite(DIR, HIGH);

       for(int i = 0; i<steps_per_rev; i++)
      {
         // control speed of motor by changing value of microseconds
         // Lower = faster
         digitalWrite(STEP, HIGH);
         delayMicroseconds(600);
         digitalWrite(STEP, LOW);
         delayMicroseconds(600);

         // stop motor halfway into turning clockwise
         /* if (i == 750)
         {
            delay(3000);
         } */
      }
      // delay before spinning in the opposite direction
     delay(3000);

   }
    
   if(request.indexOf("DIR") != -1)
   {
      // counter clockwise direction = LOW
      digitalWrite(DIR, LOW);

      for(int i = 0; i<steps_per_rev; i++)
      {  
         // control speed of motor by changing value of microseconds
         // Lower = faster
         digitalWrite(STEP, HIGH);
         delayMicroseconds(600);
         digitalWrite(STEP, LOW);
         delayMicroseconds(600);

      }
      delay(3000);
       digitalWrite(DIR, HIGH);
       for (int i = 0; i < steps_per_rev; i++)
       {
          digitalWrite(STEP, HIGH);
         delayMicroseconds(600);
         digitalWrite(STEP, LOW);
         delayMicroseconds(600);
       }
   }


 

   client.println("HTTP/1.1 200 OK");
   client.println("Content-type:text/html");
   client.println("");
   delay(1);


}