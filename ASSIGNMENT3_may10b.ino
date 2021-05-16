#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
#include "DHT.h"
#define DHTPIN 4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
 float h = dht.readHumidity();
  float t = dht.readTemperature();
void setup() {
  pinMode(5,OUTPUT);//led
  pinMode(4,INPUT);//ldr
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
  delay(2000);
Serial.println("oled test");
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println(h);
  display.println(t);
  display.display(); 
}

void loop() 
{
  int a=analogRead(4);
  Serial.println("ldr value is");
  Serial.print(a);
  delay(1000);
  if(a<1000){
    digitalWrite(5,HIGH);  
  }
  else{
  digitalWrite(5,LOW);
  Serial.println("led is off");
  }
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("% Temperature: "));
  Serial.print(t);
  if(t<35){
  digitalWrite(5,HIGH);
  }
  else{
  digitalWrite(5,LOW);
  }
  Serial.print(F("°C "));
  Serial.print(f);
  delay(1000);
  }
