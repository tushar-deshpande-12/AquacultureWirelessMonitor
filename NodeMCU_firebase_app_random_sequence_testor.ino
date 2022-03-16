#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

 
#define FIREBASE_HOST "test-14622-default-rtdb.firebaseio.com" 
#define WIFI_SSID "T"             // Change the name of your WIFI
#define WIFI_PASSWORD "Room910@"  // Change the password of your WIFI
    
  
void setup() 
{
  // Selection Pins MUX
  pinMode (D0, OUTPUT);
  pinMode (D1, OUTPUT);
  pinMode (D2, OUTPUT);
  
  // Selection input Pin
  pinMode (A0, INPUT);
  
  // Set the baud rate accordigly
  Serial.begin(115200);
               
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
  
}
 
void loop() 
{
 
  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  int temprature = rand();
  delay(200);

  digitalWrite(D0, HIGH);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  int DO = rand(); 
  delay(200);

  digitalWrite(D0, LOW);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
  int sensorData3 = rand(); 
  delay(200);

  digitalWrite(D0, HIGH);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
  int sensorData4 = rand(); 
  delay(200);

  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
  int sensorData5 = rand(); 
  delay(200);

  digitalWrite(D0, HIGH);
  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
  int sensorData6 =rand(); 
  delay(200);

// Setting the float values to the fire base cloud server
// callibrate the sensor data before uploading
// As of now it is not callibrated

  Firebase.setFloat ("Temprature",temprature);
  Firebase.setFloat ("Dissolved_Oxygen",DO);
  Firebase.setFloat ("sensorData3",sensorData3);
  Firebase.setFloat ("sensorData4",sensorData4);
  Firebase.setFloat ("sensorData5",sensorData5);
  Firebase.setFloat ("sensorData6",sensorData6);
  
  delay(3000);
}

  
