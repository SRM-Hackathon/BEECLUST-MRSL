#include "MQ135.h"
#include<ThingSpeak.h>
#include "Wire.h"
#include <ESP8266WiFi.h>
MQ135 gasSensor = MQ135(A0);
MQ135 gasSensor1 = MQ135(A0);
String apiKey="Z59FB6YV9ZLZOBJC";
const int sensorPin = A0;


const char* ssid     = "Pole Star";
const char* password = "atix7014";
const char* server = "api.thingspeak.com";

WiFiClient client;

void setup()
{
     Serial.begin(9600); /* begin serial for debug */
   pinMode(sensorPin, INPUT);                 
   pinMode(A0, INPUT); 
   pinMode(5,OUTPUT);
   pinMode(4,OUTPUT);      
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

WiFi.begin(ssid, password);


while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address of NODEMCU= ");
  Serial.println(WiFi.localIP()); // idi NodeMCU IP address.
  ThingSpeak.begin(client);
}
void loop()
{
  {
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  
  float ppm = gasSensor.getPPM();
  
  Serial.print("Quality : ");
  Serial.println(ppm);
  ThingSpeak.writeField(848759,2,ppm,"Z59FB6YV9ZLZOBJC"); //Write data to channel
   delay(1000);
  }
  {
   digitalWrite(5,HIGH);
   digitalWrite(4,LOW); 
   
   float ppm1 = gasSensor1.getPPM();
   
   //Serial.println(mq135.getPPM());
   Serial.println("CO2:");
   Serial.println(ppm1);
   ThingSpeak.writeField(848759,1,ppm1,"Z59FB6YV9ZLZOBJC"); //Write data to channel
   delay(1000);
    
  }
   

          client.stop();
 
    
  Serial.println();
  delay(1000);
}       
