#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

#define LED D0

bool b=false;

int port = 8888;
WiFiServer server(port);

const char *ssid = "myPc";
const char *password = "duV5X0eE";



void setup() {
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  Serial.println("teste\n");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  // put your setup code here, to run once:
  Serial.println("Connecting to Wifi");
  while (WiFi.status() != WL_CONNECTED) {   
    delay(500);
    Serial.print(".");
    delay(500);
  }
 
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
 
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  
  server.begin();
  Serial.print("Open Telnet and connect to IP:");
  Serial.print(WiFi.localIP());
  Serial.print(" on port ");
  Serial.println(port);
}

void loop() {
  //b=!b;
  //digitalWrite(LED, b);
  //Serial.println("teste\n");
  //delay(1000);
  WiFiClient client = server.available();
  
  if (client) {
    if(client.connected())
    {
      Serial.println("Client Connected");
    }
    
    while(client.connected()){      
      while(client.available()>0){
        // read data from the connected client
        Serial.write(client.read()); 
      }
      //Send Data to connected client
      while(Serial.available()>0)
      {
        client.write(Serial.read());
      }
    }
    client.stop();
    Serial.println("Client disconnected");    
  }
  // put your main code here, to run repeatedly:
}