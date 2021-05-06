//CONTROLLING LED DEPENDING UPON THE INTENSITY OF LIGHT

void setup() {
pinMode(4,INPUT);//ldr p4 
pinMode(5,OUTPUT);//led p5
Serial.begin(9600);
}

void loop() 
{
  int a=analogRead(4);
  Serial.print("ldr value is");
    Serial.println(a); 
    delay(1000);
    if(a<1000){
    digitalWrite(5,HIGH);  
  }
  else{
  digitalWrite(5,LOW);
  Serial.println("led is off");
  }
}
