#include <SPI.h>
#include <LoRa.h>
void setup() 
{
  Serial.begin(9600);
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(433E6)) 
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}
void loop() 
{
  // To store the received message in a string, uncomment line 16 and 24.
  // String str="";
  int packetSize = LoRa.parsePacket();
  if (packetSize) 
  {
    Serial.print("Received packet '");
    while (LoRa.available()) 
    {
      Serial.print((char)LoRa.read());
      //str=str+((char)LoRa.read());    
    }
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
