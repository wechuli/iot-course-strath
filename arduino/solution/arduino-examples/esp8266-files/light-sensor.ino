#include <ESP8266WiFi.h>
#include "DHT.h"
const int pinLight = A0; 
    
#define MAX_ADC_READING           1023
#define ADC_REF_VOLTAGE           3.3
#define REF_RESISTANCE            4700 // measure this for best results
#define LUX_CALC_SCALAR           12518931
#define LUX_CALC_EXPONENT         -1.405


#define DHTPIN 14
#define DHTTYPE DHT11
//int sensor=12;
//int gas_value;


// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE,6);

const char* ssid     = "Incubator";
const char* password = "Incubator#2013";

const char* host = "172.16.40.46";
const char* id   = "mmQo1NHP72dGjryYt1usIG3zWyt1";
float humidity;
float temperature;


void setup() {

  Serial.begin(115200);
  delay(10);


  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
 //WiFi.mode(WIFI_STA);
 
 WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  int   ldrRawData;
  float resistorVoltage, ldrVoltage;
  float ldrResistance;
  float ldrLux;

  here:
  ldrRawData = analogRead(pinLight);
  // RESISTOR VOLTAGE_CONVERSION
  // Convert the raw digital data back to the voltage that was measured on the analog pin
  resistorVoltage = (float)ldrRawData / MAX_ADC_READING * ADC_REF_VOLTAGE;

  // voltage across the LDR is the 5V supply minus the 5k resistor voltage
  ldrVoltage = ADC_REF_VOLTAGE - resistorVoltage;
  
  // LDR_RESISTANCE_CONVERSION
  // resistance that the LDR would have for that voltage  
  ldrResistance = ldrVoltage/resistorVoltage * REF_RESISTANCE;
  
  // LDR_LUX
  // Change the code below to the proper conversion from ldrResistance to
  // ldrLux
  ldrLux = 2*LUX_CALC_SCALAR * pow(ldrResistance, LUX_CALC_EXPONENT);



 
 humidity = dht.readHumidity();
  temperature = dht.readTemperature();
 
/*  

Serial.println(temperature);
delay(1000);
Serial.println(ldrRawData);
delay(1000);
Serial.println(humidity);
delay(1000);

*/

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 7773;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    delay(1000);
    goto here;
  }

  else if (isnan(temperature)||isnan(humidity)){
    Serial.println("Seems there is a problem with the senser");
    goto here;
  }
  
  // We now create a URI for the request
  String url = "/fire/home";
  url += "?id=";
  url += id;
  url += "&T01=";
  url += temperature;
  url += "&L01=";
  url += ldrLux;
  url += "&H01=";
  url += humidity;
 
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
               delay(10000);
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
 /* // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");*/
   ESP.deepSleep(500e6); // 20e6 is 2000s 
}



void loop() {
  
  
}
