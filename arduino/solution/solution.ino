
#include "DHT.h"

#define DHTPIN 11  
#define DHTTYPE DHT11
#define mq2 A5
#define red_led 9
#define white_led 10 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing Fake Fire Detector, wait for it");

  dht.begin();
}

void loop() {

  //delay(2000);

  float sensor_volt;
  
  float sensorValue;

  sensorValue = analogRead(A5);
  sensor_volt = sensorValue/1024*5.0;
  
  float h = dht.readHumidity();
  
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  

  Serial.print("Humidity: ");
  Serial.println(h);
  Serial.print("Temperature: ");
  Serial.println(t);
  Serial.print("Voltage= ");
  Serial.print(sensor_volt);
  Serial.println("V");

  if(t>26 && sensor_volt>0.5){
      white_off();
      red_on();
      red_off();

  }
  else{
      red_off();
      white_on();
  }
  
}

void red_on(){
    digitalWrite(red_led,HIGH);
    delay(1000);

}
void red_off(){
   digitalWrite(red_led,LOW);
    delay(1000); 
}
void white_on(){
    digitalWrite(white_led,HIGH);
    delay(2000);

}
void white_off(){
   digitalWrite(white_led,LOW);
    delay(1000); 
}
