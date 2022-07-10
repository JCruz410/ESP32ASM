#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>



const char* ssid = "ur wifi";
const char* password = "ur pass";



// setting pin for conveyor motor
const int DIR = 25;
const int STEP = 26;

// setting pins for pb dispenser motor
const int DIR2 = 12;
const int STEP2 = 14;

// setting pins for jelly dispenser motor
const int DIR3 = 19;
const int STEP3 = 18;

// setting pins for bread dispenser motor
const int DIR4 = 22;
const int STEP4 = 23;

// setting pins for led's
const int ledRED = 16;
const int ledGREEN = 17;

// how long motor will spend in direction (higher = longer)
const int  steps_per_rev = 1200;

// establishing connection to server for esp32
WiFiServer server(80);



void setup() 
{

   //setting pins for motor and baud rate for esp32
   Serial.begin(9600);

   // define motor pins
   pinMode(STEP, OUTPUT);
   pinMode(DIR, OUTPUT);
   pinMode(STEP2, OUTPUT);
   pinMode(DIR2, OUTPUT);
   pinMode(STEP3, OUTPUT);
   pinMode(DIR3, OUTPUT);
   pinMode(STEP4, OUTPUT);
   pinMode(DIR4, OUTPUT);

   // define LED pins
   pinMode(ledRED, OUTPUT);
   pinMode(ledGREEN, OUTPUT);

   delay(10);
 

   // connect to wifi
   WiFi.begin(ssid, password);

   // attempt to connect to ssid and password
   while (WiFi.status() != WL_CONNECTED)
   {
      delay(1000);
      Serial.println("Connecting to WiFi....");
   }

   // when connected, print ip address and begin server
   Serial.println(WiFi.localIP());
   server.begin();
}


void loop() 
{
   // keep client up as long as its available
   WiFiClient client = server.available();

   // if there is nothing connected, try again
   if (!client) 
   {
      return;
   }

   // print when android app is connected
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

        // set revolution for each pulse
         int pulse_delay = 2000;

       for(int i = 0; i<steps_per_rev; i++)
      {
         // control speed of motor by changing value of microseconds
         // Lower = faster
         digitalWrite(STEP, HIGH);
         delayMicroseconds(pulse_delay);
         digitalWrite(STEP, LOW);
         delayMicroseconds(pulse_delay);

         // if i = 300 revolutions, set speed of motor to 5500
          if (i == 300)
         {
            pulse_delay = 5500;
         } 

         // if revolutions == 600, set speed of motor to 2000
         if(i == 600)
         {
            pulse_delay = 2000;
         }

         // of revolutions == 800, set speed of motor to 5500
          if (i == 800)
         {
            pulse_delay = 5500;
         } 

         // if revolutions == 1100, set speed of motor to 2000
         if(i == 1100)
         {
            pulse_delay = 2000;
         }
      }

      // delay before spinning in the opposite direction
     delay(1500);

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
         delayMicroseconds(2000);
         digitalWrite(STEP, LOW);
         delayMicroseconds(2000);

      }
      delay(3000);

   }



   // motor 2 code (peanut butter dispenser)
   if (request.indexOf("STEP2") != -1)
   {

   }

   if(request.indexOf("DIR2") != -1)
   {

   }



 
   // motor 3 code (jelly dispenser)
   if (request.indexOf("STEP3") != -1)
   {

   }

   if (request.indexOf("DIR3") != -1)
   {

   }


   // motor 4 code (bread dispenser)
   if (request.indexOf("STEP4") != -1)
   {

   }

   if (request.indexOf("DIR4") != -1)
   {

   }


   
   // print every time action is done by android app
   client.println("HTTP/1.1 200 OK");
   client.println("Content-type:text/html");
   client.println("");
   delay(1);


}