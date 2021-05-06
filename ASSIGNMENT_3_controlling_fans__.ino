
#include "DHT.h"

#define DHTPIN 4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
//CONTROLLING FANS BASED UPON TEMPERATURE 

void setup() {
  pinMode(5,OUTPUT);//led p5
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
}

void loop() 
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  if(t<35){
  digitalWrite(5,HIGH);
  }
  else{
    digitalWrite(6,LOW);
  }
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  delay(1000);
  
  }
