#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>



const char* ssid = "ur wifi";
const char* password = "ur pass";



// setting pin for conveyor motor, 12 and 14 are temporary pins for a motor
const int DIR = 12;
const int cow = 14;

// setting pins for pb dispenser motor
const int DIPB = 25;
const int STEB = 26;

// setting pins for jelly dispenser motor
const int DJELLY = 19;
const int STJELLY = 18;

// setting pins for bread dispenser motor
const int DEEBREAD = 22;
const int SBREAD = 23;

// setting pins for led's
const int ledRED = 16;  
const int ledGREEN = 17;   

// how long motor will spend in direction (higher = longer)
const int  steps_per_rev = 1300;
const int pb_motor = 1200;
const int jelly_motor = 1200;
const int bread_motor = 1200;

// establishing connection to server for esp32
WiFiServer server(80);

void setup() 
{

   //setting pins for motor and baud rate for esp32
   Serial.begin(9600);

   // define motor pins
   pinMode(cow, OUTPUT);
   pinMode(DIR, OUTPUT);
   pinMode(STEB, OUTPUT);
   pinMode(DIPB, OUTPUT);
   pinMode(STJELLY, OUTPUT);
   pinMode(DJELLY, OUTPUT);
   pinMode(SBREAD, OUTPUT);
   pinMode(DEEBREAD, OUTPUT);

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
   
   // FULL SANDWICH CODE
   if(request.indexOf("cow") != -1)
   {

       int pulse_delay = 2000;

        // turn ledRED on when conveyor starts
        digitalWrite(ledRED, HIGH);

      // set direction of bread dispenser HIGH = Clockwise
      digitalWrite(DEEBREAD, HIGH);

      for(int i = 0; i<bread_motor; i++)
      {
         // control speed of motor by changing value of microseconds
         // Lower = faster
         digitalWrite(SBREAD, HIGH);
         delayMicroseconds(pulse_delay);
         digitalWrite(SBREAD, LOW);
         delayMicroseconds(pulse_delay);
         
      }

      delay(3000);

      // change direction of bread motor to CClockwise to bring back
      digitalWrite(DEEBREAD, LOW);

       for(int i = 0; i<bread_motor; i++)
      {
         // control speed of motor by changing value of microseconds
         // Lower = faster
         digitalWrite(SBREAD, HIGH);
         delayMicroseconds(pulse_delay);
         digitalWrite(SBREAD, LOW);
         delayMicroseconds(pulse_delay);
         
      }

      /* delay(2000);
         
        // start the conveyor belt motor after bread is dropped
        // clockwise direction = HIGH
        digitalWrite(DIR, HIGH);

       for(int i = 0; i<steps_per_rev; i++)
      {
         // control speed of motor by changing value of microseconds
         // Lower = faster
         digitalWrite(cow, HIGH);
         delayMicroseconds(pulse_delay);
         digitalWrite(cow, LOW);
         delayMicroseconds(pulse_delay);

         // if i = 300 revolutions, set speed of motor to 5500
          if (i == 300)
         {
            pulse_delay = 6000;

            // set direction for PB dispenser
            digitalWrite(DIPB, LOW);

            for(int i = 0; i < pb_motor; i++)
            {
            // control speed of motor by changing value of microseconds
            // Lower = faster
            digitalWrite(STEB, HIGH);
            delayMicroseconds(pulse_delay);
            digitalWrite(STEB, LOW);
            delayMicroseconds(pulse_delay);

            }
         }

            delay(1000);

            // clockwise direction = HIGH
            digitalWrite(DIPB, HIGH);

            for(int i = 0; i < pb_motor; i++)
            {  
               // control speed of motor by changing value of microseconds
               // Lower = faster
               digitalWrite(STEB, HIGH);
               delayMicroseconds(pulse_delay);
               digitalWrite(STEB, LOW);
               delayMicroseconds(pulse_delay);
            }
          

         // if revolutions == 600, set speed of motor to 2000
         if(i == 600)
         {
            pulse_delay = 2000;
         }
         
         // of revolutions == 800, set speed of motor to 5500
          if (i == 800)
         {
            pulse_delay = 6000;

            // set direction for PB dispenser
            digitalWrite(DJELLY, LOW);

            for(int i = 0; i < jelly_motor; i++)
            {
            // control speed of motor by changing value of microseconds
            // Lower = faster
            digitalWrite(STJELLY, HIGH);
            delayMicroseconds(pulse_delay);
            digitalWrite(STJELLY, LOW);
            delayMicroseconds(pulse_delay);

            }
            delay(1000);

            // clockwise direction = HIGH
            digitalWrite(DJELLY, HIGH);
            
            for(int i = 0; i < jelly_motor; i++)
            {  
               // control speed of motor by changing value of microseconds
               // Lower = faster
               digitalWrite(STJELLY, HIGH);
               delayMicroseconds(pulse_delay);
               digitalWrite(STJELLY, LOW);
               delayMicroseconds(pulse_delay);
            }

            delay(1000);

         } 

         // if revolutions == 1100, set speed of motor to 2000
         if(i == 1100)
         {
            pulse_delay = 2000;
         }
      }

      // delay before spinning in the opposite direction
     delay(1500);

     // counter clockwise direction = LOW
      digitalWrite(DIR, LOW);

      for(int i = 0; i<steps_per_rev; i++)
      {  
         // control speed of motor by changing value of microseconds
         // Lower = faster
         digitalWrite(cow, HIGH);
         delayMicroseconds(2000);
         digitalWrite(cow, LOW);
         delayMicroseconds(2000);

      }

      // set direction of bread dispenser HIGH = Clockwise
      digitalWrite(DEEBREAD, HIGH);

      for(int i = 0; i<bread_motor; i++)
      {
         // control speed of motor by changing value of microseconds
         // Lower = faster
         digitalWrite(SBREAD, HIGH);
         delayMicroseconds(pulse_delay);
         digitalWrite(SBREAD, LOW);
         delayMicroseconds(pulse_delay);
         
      }

      delay(3000);

      // change direction of bread motor to CClockwise to bring back
      digitalWrite(DEEBREAD, LOW);

       for(int i = 0; i<bread_motor; i++)
      {
         // control speed of motor by changing value of microseconds
         // Lower = faster
         digitalWrite(SBREAD, HIGH);
         delayMicroseconds(pulse_delay);
         digitalWrite(SBREAD, LOW);
         delayMicroseconds(pulse_delay);
         
      } 
   */
      digitalWrite(ledRED, LOW);
      digitalWrite(ledGREEN, HIGH);
      delay(10000);
      digitalWrite(ledGREEN, LOW);

   }
    

   // motor 2 code (peanut butter dispenser)/ PB only sandwich
 if(request.indexOf("STEB") != -1)
   {
        int pulse_delay = 2000;

        // turn ledRED on when conveyor starts
        digitalWrite(ledRED, HIGH);

      // set direction of bread dispenser HIGH = Clockwise
      digitalWrite(DEEBREAD, HIGH);

      for(int i = 0; i < bread_motor; i++)
      {
         // control speed of motor by changing value of microseconds
         // Lower = faster
         digitalWrite(SBREAD, HIGH);
         delayMicroseconds(pulse_delay);
         digitalWrite(SBREAD, LOW);
         delayMicroseconds(pulse_delay);
         
      }

      delay(3000);

      // change direction of bread motor to CClockwise to bring back
      digitalWrite(DEEBREAD, LOW);

       for(int i = 0; i<bread_motor; i++)
      {
         // control speed of motor by changing value of microseconds
         // Lower = faster
         digitalWrite(SBREAD, HIGH);
         delayMicroseconds(pulse_delay);
         digitalWrite(SBREAD, LOW);
         delayMicroseconds(pulse_delay);
         
      }

      delay(2000);
         
        // start the conveyor belt motor after bread is dropped
        // clockwise direction = HIGH
        digitalWrite(DIR, HIGH);

       for(int i = 0; i<steps_per_rev; i++)
      {
         // control speed of motor by changing value of microseconds
         // Lower = faster
         digitalWrite(cow, HIGH);
         delayMicroseconds(pulse_delay);
         digitalWrite(cow, LOW);
         delayMicroseconds(pulse_delay);

         // if i = 300 revolutions, set speed of motor to 6000
          if (i == 300)
         {
            pulse_delay = 6000;

            // set direction for PB dispenser
            digitalWrite(DIPB, LOW);

            for(int i = 0; i < pb_motor; i++)
            {
            // control speed of motor by changing value of microseconds
            // Lower = faster
            digitalWrite(STEB, HIGH);
            delayMicroseconds(pulse_delay);
            digitalWrite(STEB, LOW);
            delayMicroseconds(pulse_delay);

            }

            delay(1000);

            // clockwise direction = HIGH
            digitalWrite(DIPB, HIGH);

            for(int i = 0; i < pb_motor; i++)
            {  
               // control speed of motor by changing value of microseconds
               // Lower = faster
               digitalWrite(STEB, HIGH);
               delayMicroseconds(pulse_delay);
               digitalWrite(STEB, LOW);
               delayMicroseconds(pulse_delay);
            }
         }
      }

      // delay before spinning in the opposite direction
     delay(1500);

     // counter clockwise direction = LOW
      digitalWrite(DIR, LOW);

      for(int i = 0; i<steps_per_rev; i++)
      {  
         // control speed of motor by changing value of microseconds
         // Lower = faster
         digitalWrite(cow, HIGH);
         delayMicroseconds(2000);
         digitalWrite(cow, LOW);
         delayMicroseconds(2000);

      }

      // set direction of bread dispenser HIGH = Clockwise
      digitalWrite(DEEBREAD, HIGH);

      for(int i = 0; i < bread_motor; i++)
      {
         // control speed of motor by changing value of microseconds
         // Lower = faster
         digitalWrite(SBREAD, HIGH);
         delayMicroseconds(2000);
         digitalWrite(SBREAD, LOW);
         delayMicroseconds(2000);
         
      }

      delay(3000);

      // change direction of bread motor to CClockwise to bring back
      digitalWrite(DEEBREAD, LOW);

       for(int i = 0; i<bread_motor; i++)
      {
         // control speed of motor by changing value of microseconds
         // Lower = faster
         digitalWrite(SBREAD, HIGH);
         delayMicroseconds(2000);
         digitalWrite(SBREAD, LOW);
         delayMicroseconds(2000);
         
      }

      digitalWrite(ledRED, LOW);
      digitalWrite(ledGREEN, HIGH);
      delay(10000);
      digitalWrite(ledGREEN, LOW);

         } 
    

   // motor 3 code (jelly dispenser)// Jelly only sandwich
    if(request.indexOf("STJELLY") != -1)
   {
       int pulse_delay = 2000;

        // turn ledRED on when conveyor starts
        digitalWrite(ledRED, HIGH);

      // set direction of bread dispenser HIGH = Clockwise
      digitalWrite(DEEBREAD, HIGH);

      for(int i = 0; i < bread_motor; i++)
      {
         // control speed of motor by changing value of microseconds
         // Lower = faster
         digitalWrite(SBREAD, HIGH);
         delayMicroseconds(pulse_delay);
         digitalWrite(SBREAD, LOW);
         delayMicroseconds(pulse_delay);
         
      }

      delay(3000);

      // change direction of bread motor to CClockwise to bring back
      digitalWrite(DEEBREAD, LOW);

       for(int i = 0; i<bread_motor; i++)
      {
         // control speed of motor by changing value of microseconds
         // Lower = faster
         digitalWrite(SBREAD, HIGH);
         delayMicroseconds(pulse_delay);
         digitalWrite(SBREAD, LOW);
         delayMicroseconds(pulse_delay);
         
      }

      delay(2000);
         
        // start the conveyor belt motor after bread is dropped
        // clockwise direction = HIGH
        digitalWrite(DIR, HIGH);

       for(int i = 0; i<steps_per_rev; i++)
      {
         // control speed of motor by changing value of microseconds
         // Lower = faster
         digitalWrite(cow, HIGH);
         delayMicroseconds(pulse_delay);
         digitalWrite(cow, LOW);
         delayMicroseconds(pulse_delay);

         // of revolutions == 800, set speed of motor to 5500
          if (i == 800)
         {
            pulse_delay = 6000;

            // set direction for PB dispenser
            digitalWrite(DJELLY, LOW);

             for(int i = 0; i < jelly_motor; i++)
            {
            // control speed of motor by changing value of microseconds
            // Lower = faster
            digitalWrite(STJELLY, HIGH);
            delayMicroseconds(pulse_delay);
            digitalWrite(STJELLY, LOW);
            delayMicroseconds(pulse_delay);

            }

            delay(1000);

            // clockwise direction = HIGH
            digitalWrite(DJELLY, HIGH);

            for(int i = 0; i < jelly_motor; i++)
            {  
               // control speed of motor by changing value of microseconds
               // Lower = faster
               digitalWrite(STJELLY, HIGH);
               delayMicroseconds(pulse_delay);
               digitalWrite(STJELLY, LOW);
               delayMicroseconds(pulse_delay);
            }

         }

      }

      // delay before spinning in the opposite direction
     delay(1500);

     // counter clockwise direction = LOW
      digitalWrite(DIR, LOW);

      for(int i = 0; i<steps_per_rev; i++)
      {  
         // control speed of motor by changing value of microseconds
         // Lower = faster
         digitalWrite(cow, HIGH);
         delayMicroseconds(2000);
         digitalWrite(cow, LOW);
         delayMicroseconds(2000);

      }

      // set direction of bread dispenser HIGH = Clockwise
      digitalWrite(DEEBREAD, HIGH);

      for(int i = 0; i<bread_motor; i++)
      {
         // control speed of motor by changing value of microseconds
         // Lower = faster
         digitalWrite(SBREAD, HIGH);
         delayMicroseconds(pulse_delay);
         digitalWrite(SBREAD, LOW);
         delayMicroseconds(pulse_delay);
         
      }

      delay(3000);

      // change direction of bread motor to CClockwise to bring back
      digitalWrite(DEEBREAD, LOW);

       for(int i = 0; i<bread_motor; i++)
      {
         // control speed of motor by changing value of microseconds
         // Lower = faster
         digitalWrite(SBREAD, HIGH);
         delayMicroseconds(pulse_delay);
         digitalWrite(SBREAD, LOW);
         delayMicroseconds(pulse_delay);
         
      }

      digitalWrite(ledRED, LOW);
      digitalWrite(ledGREEN, HIGH);
      delay(10000);
      digitalWrite(ledGREEN, LOW);
   }
    
   
   // print every time action is done by android app
   client.println("HTTP/1.1 200 OK");
   client.println("Content-type:text/html");
   client.println("");
   delay(1);

   }