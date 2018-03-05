#include <ESP8266WiFi.h>
#include "DHT.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define MAX_ADC_READING           1023
#define ADC_REF_VOLTAGE           3.3
#define REF_RESISTANCE            4700 // measure this for best results
#define LUX_CALC_SCALAR           12518931
#define LUX_CALC_EXPONENT         -1.405

#define DHTPIN 12
#define DHTTYPE DHT11
#define pinLight A0
#define red_led 13
#define blue_led 14

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "paulo"
#define WLAN_PASS       "nairobi@1234"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "wechuli"
#define AIO_KEY         "c916326bb27c4529bf877c35935c5e2a"


DHT dht(DHTPIN, DHTTYPE,12);

float humidity;
float temperature;

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish temp = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temp");
Adafruit_MQTT_Publish humid = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");
Adafruit_MQTT_Publish luminosity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/lumens");



/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

void setup() {
  red_on();  
  Serial.begin(115200);
  delay(10);
  pinMode(red_led,OUTPUT);
  pinMode(blue_led,OUTPUT);

  Serial.println(F("Initializing Strath Project Demo....Loading"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  blue_on();
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

 
}
void loop(){
red_on();
int   ldrRawData;
  float resistorVoltage, ldrVoltage;
  float ldrResistance;
  float ldrLux;

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

   if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(1000);
    return;
  }

  MQTT_connect();

  // Now we can publish stuff!
  Serial.print(F("\nSending Temprature Values "));
  Serial.print(temperature);
  Serial.print("...");
  if (! temp.publish(temperature)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }

  Serial.print(F("\nSending Humidity Values "));
  Serial.print(humidity);
  Serial.print("...");
  if (! humid.publish(humidity)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }

  Serial.print(F("\nSending Light Intesnity Values "));
  Serial.print(ldrLux);
  Serial.print("...");
  if (! luminosity.publish(ldrLux)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
blue_off();
  blue_on();
  blue_off();
  blue_on();
  blue_off();
  blue_on();

  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  /*
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
  */

  delay(5000);
  red_off();
  blue_off();
  //ESP.deepSleep(5e6); //20e6 is 2000s
}


// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
void red_on(){
    digitalWrite(red_led,HIGH);
    delay(2000);

}
void red_off(){
   digitalWrite(red_led,LOW);
    delay(1000); 
}
void blue_on(){
    digitalWrite(blue_led,HIGH);
    delay(2000);

}
void blue_off(){
   digitalWrite(blue_led,LOW);
    delay(1000); 
}
