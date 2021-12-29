#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "SSID_Name";   // your network SSID (name) 
const char* password = "Password";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = "Channel ID"; // ThingSpeak Channel 
const char * myWriteAPIKey = "Write API"; // ThingSpeak Write API Key

// Variable to ADC value
int adc_val;

void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(A0, INPUT);
  
  WiFi.mode(WIFI_STA);   
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) 
  {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");

}

void loop() {
  adc_val = analogRead(A0);
  int x = ThingSpeak.writeField(myChannelNumber, 1, adc_val, myWriteAPIKey);
  Serial.print("Value to be updated: ");
  Serial.println(adc_val);
  if(x == 200)
    {
      Serial.println("Channel update successful.");
    }
    else
    {
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    delay(15000);
}
