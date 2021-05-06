//ultrasonic sensor and servomotor

#include<Servo.h>
Servo mt;
void setup()
{
 mt.attach(5);
  pinMode(7,OUTPUT);
  pinMode(12,INPUT);
 Serial.begin(9600);
}

void loop()
{
  digitalWrite(7,HIGH);
  delay(1000);
  digitalWrite(7,LOW);
  int duration=pulseIn(12,HIGH);
  int distance=(duration*0.034)/2;
  Serial.println("the distance is ");
  Serial.println(distance);
 // delay(1000);
    if(distance<100)
  {
  mt.write(180);
  Serial.println("door opened");
  delay(1000);
  }
  else
  {
  mt.write(0);
  Serial.println("door closed");
  delay(1000);
  }
}
