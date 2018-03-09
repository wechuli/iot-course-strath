#include <TheThingsNetwork.h>

#include "DHT.h"

// Set your DevAddr, NwkSKey, AppSKey and the frequency plan
const char *devAddr = "2601140C";
const char *nwkSKey = "780593843792C5D0588E762741387ABC";
const char *appSKey = "149DA9C63CCCFF42C5D8B571554B37A1";

#define loraSerial Serial1
#define debugSerial Serial
#define DHTPIN 8 
#define DHTTYPE DHT11 
// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan TTN_FP_EU868

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  loraSerial.begin(57600);
  debugSerial.begin(9600);
  dht.begin();

  // Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000)
    ;

  debugSerial.println("-- PERSONALIZE");
  ttn.personalize(devAddr, nwkSKey, appSKey);

  debugSerial.println("-- STATUS");
  ttn.showStatus();
}

void loop()
{
  debugSerial.println("-- LOOP");

    // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  uint16_t humidity = h*100;
  uint16_t temperature = t*100;

byte payload[4];

  payload[0] = highByte(temperature);
  payload[1] = lowByte(temperature);
  payload[2] = highByte(humidity);
  payload[3] = lowByte(humidity);
  
  

  // Send it off
  ttn.sendBytes(payload, sizeof(payload));

  debugSerial.print("Temperature: ");
  debugSerial.println(temperature);
  debugSerial.print("Humidity: ");
  debugSerial.println(humidity);

  delay(10000);
}