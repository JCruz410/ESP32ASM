#include <Arduino.h>
#include <WiFi.h>

#define WIFI_NETWORK "Hunter-Joel Wifi"
#define WIFI_PASSWORD "hunterjoel"
#define WIFI_TIMEOUT_MS 20000

void connectToWiFi(){

  Serial.print("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

  unsigned long startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT_MS)
  {
    Serial.print(".");
    delay(100);
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Failed!");
    // take action
  }
  else
  {
    Serial.print("Connected!");
    Serial.println(WiFi.localIP());
  }
}


void setup() 
{
  Serial.begin(9600);  
  connectToWiFi();
}

// test
void loop() {
  // put your main code here, to run repeatedly:
}