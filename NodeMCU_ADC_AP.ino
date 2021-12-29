#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// SSID Name
const char* ssid = "nodemcu";

ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
int adc_data;
float volt;

void setup() {
  delay(100);
  Serial.begin(115200);
  
  pinMode(A0, INPUT);

  Serial.println("Configuring access point... ");
  Serial.println(ssid);
  WiFi.softAP(ssid);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handle_adc);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  adc_data = analogRead(A0);
  volt = ((adc_data/1024.0)*3.3);
  delay(1000);
  server.handleClient();
  }

void handle_adc() 
{
  server.send(200, "text/html", SendHTML()); 
}

void handle_NotFound()
{
  server.send(404, "text/plain", "Not found");
}

String SendHTML(){
  String ptr = "<!DOCTYPE html>\n";
  ptr +="<html>\n";
  ptr +="<head>\n";
  ptr +="<title>ADC Display</title>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Displaying ADC Value in Web Browser [AP Mode]</h1>\n";
  ptr +="<h2>Digital Data: ";
  ptr += String(adc_data);
  ptr +="</h2>";
  ptr +="<h2>Voltage (V): ";
  ptr += String(volt);
  ptr +="</h2>";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
