#include <WiFi.h>
#include <PubSubClient.h>

int distance;
int a;
String command;
String data="";

void callback(char* topic, byte* payload, unsigned int payloadLength);

// CHANGE TO YOUR WIFI CREDENTIALS
const char* ssid = "mangaapathi Rao";//your wifi ssid
const char* password = "9394891584";//your password

// CHANGE TO YOUR DEVICE CREDENTIALS AS PER IN IBM BLUMIX
#define ORG "uqeb4i"
#define DEVICE_TYPE "ULTRASONIC"
#define DEVICE_ID "67890"
#define TOKEN "7702502769" //  Authentication Token OF THE DEVICE
//  PIN DECLARATIONS 

#define led1 2
#define led2 0

int echopin=4;
int trigpin=16;
const int ldrin = 34;
int light = 0;

//-------- Customise the above values --------
const char publishTopic[] = "iot-2/evt/Data/fmt/json";
char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[] = "iot-2/cmd/home/fmt/String";// cmd  REPRESENT command type AND COMMAND IS TEST OF FORMAT STRING
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;


WiFiClient wifiClient;
PubSubClient client(server, 1883, callback, wifiClient);

int publishInterval = 5000; // 30 seconds
long lastPublishMillis;
void publishData();

void setup() {
  pinMode(echopin,INPUT);
  pinMode(trigpin,OUTPUT);
  Serial.begin(115200);
  Serial.println();
  
   
  wifiConnect();
  mqttConnect();
}

void loop() {
  digitalWrite(trigpin,HIGH);
  delay(1000);
  digitalWrite(trigpin,LOW);
  int duration=pulseIn(echopin,HIGH);
  distance=(duration*0.034)/2;
  delay(1000);

  light = analogRead(ldrin);
  delay(1000);

 if (millis() - lastPublishMillis > publishInterval)
  {
    publishData();
    lastPublishMillis = millis();
  }
  
  if (!client.loop()) {
    mqttConnect();
  }
}

void wifiConnect() {
  Serial.print("Connecting to "); Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("WiFi connected, IP address: "); 
  Serial.println(WiFi.localIP());
}

void mqttConnect() {
  if (!client.connected())  
  {
    Serial.print("Reconnecting MQTT client to "); Serial.println(server);
    while (!client.connect(clientId, authMethod, token)) {
      Serial.print(".");
      delay(500);
    }
    
    initManagedDevice();
    Serial.println();
  }
}

void initManagedDevice() {
  if (client.subscribe(topic)) {
   
    Serial.println("subscribe to cmd OK");
  } else {
    Serial.println("subscribe to cmd FAILED");
  }
}

void callback(char* topic, byte* payload, unsigned int payloadLength) {
  
  Serial.print("callback invoked for topic: ");
  Serial.println(topic);

  for (int i = 0; i < payloadLength; i++) {
    
    command+= (char)payload[i];
  }
  
  Serial.print("data: "+ command);
  control_func();
  command= "";
}

void control_func()
{
  
   
  if(command== "lightoff")
 {

 digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
     Serial.println(".......lights are off..........");
    
  }
  else if(command== "lighton")
  {
     digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
     Serial.println(".......lights are on..........");

  }

   
  else
  {
    Serial.println("......no commands have been subscribed..........");
   
    }
}

void publishData() 
{
  

  
  

  String payload = "{\"d\":{\"distance\":";
  payload += distance;
  payload += ",""\"light\":";
  payload += light;
  payload += "}}";


  Serial.print("\n");
  Serial.print("Sending payload: "); Serial.println(payload);

  if (client.publish(publishTopic, (char*) payload.c_str())) {
    Serial.println("Publish OK");
  } else {
    Serial.println("Publish FAILED");
  }
}
