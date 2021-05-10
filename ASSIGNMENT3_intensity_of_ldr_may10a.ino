void setup(){
pinMode(4,INPUT);
Serial.begin(9600);
}
void loop(){
int a=analogRead(4);
Serial.println("ldr value is");
Serial.print(a);
delay(1000);
}
