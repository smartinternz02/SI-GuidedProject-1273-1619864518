Code:
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
int LED=14;
int trigpin=16;
int echopin=4;
int onn=1;
int off=0;
void setup()
{
 pinMode(echopin,INPUT);
 pinMode(trigpin,OUTPUT);
 pinMode(LED,OUTPUT);
Serial.begin(115200);
 SerialBT.begin("ESP32test"); //Bluetooth device name
 Serial.println("The device has started, now you can pair it with bluetooth!");
}
void loop()
{
 int Data= (SerialBT.read());
 digitalWrite(trigpin,HIGH);
delay(1000);
digitalWrite(trigpin,LOW);
int duration=pulseIn(echopin,HIGH);
int distance=(duration*0.0343)/2;
Serial.print("the distance is");
Serial.println(distance);
delay(1000); 
 if (distance>100)
 {
 SerialBT.print("water level is");
 SerialBT.print(distance);
 SerialBT.println(" :NULL");
 }
 else
 {
 SerialBT.print("Water level is");
 SerialBT.print(distance);
 SerialBT.println(" :FULL");
 }
 if (Data==onn); {
 digitalWrite(LED,HIGH);
 
 }
 if(Data==off)
 {
 digitalWrite(LED,LOW);
 
 } 
 delay(20);
 
}
