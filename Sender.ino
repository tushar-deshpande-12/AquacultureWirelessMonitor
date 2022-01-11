#include <LoRa.h>
#define SS 15
#define RST 16
#define DIO0 2
#define S0 0
#define S1 2
#define S2 3

void setup()
{
    // Selection Pins MUX
  pinMode (S0, OUTPUT);
  pinMode (S1, OUTPUT);
  pinMode (S2, OUTPUT);
  
  // Selection input Pin
  pinMode (A0, INPUT);

  Serial.begin(9600);

  //Protocols to start Communication with LORA
  while (!Serial);
  Serial.println("Sender Host");
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa Error");
    delay(100);
    while (1);
  }
}

void loop()
{
  int delayTime = 100;
  int div = 1;
  
  //DO Sensor - PORT 1

  //Serial.println("-----------------------------------------------------------------------------------------------");    

  setMux(HIGH,LOW ,LOW);
  delay(delayTime);
  //int DO = rand()/div;
  int DO = analogRead(A0); 
  //Serial.print("DO value is: ");
  //Serial.print(analogRead(A0));
  //Serial.print(" DO voltage(mV) is: ");
  float voltage = analogRead(A0)*3.3*1000/1024;
  //Serial.println(voltage);

  //Serial.println("-----------------------------------------------------------------------------------------------");    

// TEMPRATURE SENSOR - PORT 0
  setMux(LOW,HIGH,LOW);
  delay( delayTime);
  //float temprature = tempratureRead(rand()/div);
  float temprature = analogRead(A0);
  //Serial.print("Temprature is: ");
  //Serial.print(temprature);
  //Serial.print("   Temprature value is: ");
  //Serial.print(analogRead(A0));
  //Serial.print("   Temprature voltage is: ");
  float voltageT = analogRead(A0)*3.3/1024;
  //Serial.println(voltageT);
  
  //Serial.println("-----------------------------------------------------------------------------------------------");    

  //pH Sensor - PORT 3  
  setMux(HIGH,HIGH,LOW);
  delay( delayTime);
  //float pH = tempratureRead(rand()/div);
  float pH = analogRead(A0);   
  //Serial.print("pH is: ");
  //Serial.print(pH);
  //Serial.print("     pH value is: ");
  //Serial.print(analogRead(A0));
  //Serial.print("     pH voltage is: ");
  //Serial.println(analogRead(A0)*5/1024);
 
  //Serial.println("-----------------------------------------------------------------------------------------------");    

  setMux(HIGH,HIGH,LOW);
  delay(delayTime);
  //int sensorData4 = rand()/div;
  int sensorData4 = analogRead(A0); 
  //Serial.print("Sensor 4 value is: ");
  //Serial.println(sensorData4);
  //Serial.print("Sensor 4 voltage is: ");
  //Serial.println(analogRead(A0)*5/1024);
  
  //Serial.println("-----------------------------------------------------------------------------------------------");    

  setMux(LOW,LOW,HIGH);
  delay( delayTime);
  //int sensorData5 = rand()/div;
  int sensorData5 = analogRead(A0); 
  //Serial.print("Sensor 5 value is: ");
  //Serial.println(sensorData5);
  //Serial.print("Sensor 5 voltage is: ");
  //Serial.println(analogRead(A0)*5/1024);
  
  //Serial.println("-----------------------------------------------------------------------------------------------");    

   setMux(HIGH,LOW,HIGH);
   delay( delayTime);
   //int sensorData6 = rand()/div;
   int sensorData6 = analogRead(A0); 
   //Serial.print("Sensor 6 value is: ");
   //Serial.println(sensorData6);
   //Serial.print("Sensor 6 voltage is: ");
   //Serial.println(analogRead(A0)*5/1024);
  
   //Serial.println("-----------------------------------------------------------------------------------------------");    

// Setting the float values to the fire base cloud server
// callibrate the sensor data before uploading
// As of now it is not callibrated

   

  String data = "Temprature: ";
  data += convertStr(temprature); 
  data += " Dissolved Oxygen: ";
  data += convertStr(DO);
  data += " pH: ";
  data += convertStr(pH);
  data += " Sensor Value4: ";
  data += convertStr(sensorData4);
  data += " Sensor Value5: " ;
  data += convertStr(sensorData5);
  data += " Sensor Value6: ";
  data += convertStr(sensorData6);
  
  // Lora Communication Protocol
  // 1) Begining the Packet
  // 2) Sending the Data 
  // 3) Ending the Packet

  Serial.print("Sending Data: ");
  Serial.println(data);

  LoRa.beginPacket();
  
  LoRa.print(data);
  LoRa.endPacket();
//  delay(200);
}    
  

void setMux(int a,int b ,int c)
{
  digitalWrite(S0,a);
  digitalWrite(S1,b);
  digitalWrite(S2,c);
}  

String convertStr(int input)
{

  String op;
  
  if(input<10000 && input >= 1000)
  {
    op = String(input); 
    }
  if(input<1000 && input >= 100)
  {
    op = "0" + String(input);
    }
   
  if(input<100 && input >= 10)
  {
    op = "00" + String(input);
    }
    if(input<10)
  {
    op = "000" + String(input);
    }

    
    return op;
  }
  
