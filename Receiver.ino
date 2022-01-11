#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include<stdio.h>
#include <LoRa.h>
#include <stdlib.h>

//Format
//00        10        20        30        40        50        60        70        80        90        100 
//012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567
//Temprature: 0627 Dissolved Oxygen: 0626 pH: 0627 Sensor Value4: 0627 Sensor Value5: 0626 Sensor Value6: 0627


// Define the firebase host id here
#define FIREBASE_HOST "test-14622-default-rtdb.firebaseio.com"

// Wifi Name
#define WIFI_SSID "T"             // Change the name of your WIFI

//Password of the Wifi
#define WIFI_PASSWORD "Room910@"  // Change the password of your WIFI


#define SS 15
#define RST 16
#define DIO0 2

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                  
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); 
  Firebase.begin(FIREBASE_HOST);
  
  while (!Serial);
  Serial.println("Receiver Host");
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa Error");
    while (1);
  }
}
void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print("Receiving Data: ");
    while (LoRa.available()) {
      String data = LoRa.readString();
      int temprature = tempratureRead(createInt(data, 12, 13, 14, 15));
      Firebase.setFloat ("Temprature",temprature);
      int DO = doRead(createInt(data, 35, 36, 37, 38));
      Firebase.setFloat ("Dissolved_Oxygen",DO);
      int pH = pHRead(createInt(data, 44, 45, 46, 47));
      Firebase.setFloat ("sensorData3",pH);
      int sensorData4 = createInt(data, 64, 65, 66, 67);
      Firebase.setFloat ("sensorData4",sensorData4);
      int sensorData5 = createInt(data, 84, 85, 86, 87);
      Firebase.setFloat ("sensorData5",sensorData5);
      int sensorData6 = createInt(data, 104, 105, 106, 107);
      Firebase.setFloat ("sensorData6",sensorData6);                 
    }
  }
}

int createInt(String data, int a, int b, int c, int d)
{
  char data1 = charToInt(data[a]);
  char data2 = charToInt(data[b]);
  char data3 = charToInt(data[c]);
  char data4 = charToInt(data[d]);
   
  int output = (data1*1000) + (data2*100) + (data3*10) + data4;
  return output; 
 }

 
 int charToInt(char c){
 int num = 0;

  //Substract '0' from entered char to get
  //corresponding digit
  num = c - '0';

  return num;
}

float tempratureRead(int input)
{
  float temprature1 = map(input, 0, 1023, -55, 125);
  delay(50);
  float temprature2 = map(input, 0, 1023, -55, 125);
  float temprature = (temprature1 + temprature2)/2 ;
  return temprature;
  }

float pHRead(int input)
{
  
  float pH1 = map(input, 0, 1023, 14, 1);
  delay(50);
  float pH2 = map(input, 0, 1023, 14, 1);
  float pH = (pH1 + pH2)/2 ; 
  
  return pH;
  }

float doRead(int input)
{
  
  float do1 = map(input, 0, 1023, 0, 7.8);
  delay(50);
  float do2 = map(input, 0, 1023, 0, 7.8);
  float DO = (do1 + do2)/2 ; 
  
  return DO;
  }
  
