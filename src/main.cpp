#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

#define LED D0

void serverConection();
void setUpW();

void clientConnection();
void clientMsg();
bool b=false;

int port = 4242;
WiFiServer server(port);
WiFiClient client;
IPAddress ip(10,42,0,1);
const char *ssid = "myPc";
const char *password = "duV5X0eE";



void setup() {
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  //Serial.println("teste\n");
  setUpW();
  clientConnection();
}

void loop() {
  //b=!b;
  //digitalWrite(LED, b);
  //Serial.println("teste\n");
  //delay(1000);
  clientMsg();
  // put your main code here, to run repeatedly:
}

void serverConection(){
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
}
void setUpW(){
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
void clientConnection(){
  client.stop();
  while (!client.connected())
  {
    /* code */
    if(client.connect(ip,port)){
      Serial.println("connected");
    }
    else{
      Serial.println("not connected");
    }
    delay(1000);
  }
  
}
void clientMsg(){
  client.println("connectado");
  delay(1000);
  while(client.available()>0){
        // read data from the connected client
        Serial.write(client.read()); 
      }

}
