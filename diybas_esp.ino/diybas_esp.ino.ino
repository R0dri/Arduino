/*
 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//String string;

// Update these with values suitable for your network.
const char* ssid = "Tejada";
const char* password = "06055819";
const char* mqtt_server = "192.168.0.25";

//Topics
String electrodes = "diybas/electrodes/";
String bufer;
const char* pub_topic = "diybas/electrodes";
const char* sub_topic = "diybas/esp";

//SPI
#define SELPIN   16//Selection Pin 
#define DATAOUT  13//MOSI 
#define DATAIN   12//MISO 
#define SPICLOCK 14//Clock 
int readvalue; 


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
char top[50];
int value = 0;

int pinled = 13;

void setup() {
  //Set MQTT Connection with server
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  Serial.setTimeout(10);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  //set SPI pin modes 
  pinMode(SELPIN, OUTPUT); 
  pinMode(DATAOUT, OUTPUT); 
  pinMode(DATAIN, INPUT); 
  pinMode(SPICLOCK, OUTPUT); 
  //disable device to start with 
  digitalWrite(SELPIN,HIGH); 
  digitalWrite(DATAOUT,LOW); 
  digitalWrite(SPICLOCK,LOW); 
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  pinMode(pinled,OUTPUT);
  digitalWrite(pinled,HIGH);
  delay(100);
  digitalWrite(pinled,LOW);
  delay(100);
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP DIYBAS Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(pub_topic, "Connected!");
      // ... and resubscribe
      client.subscribe(sub_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

int read_adc(int chan){
  int adcvalue = 0;
  byte commandbits = B11000000; //command bits - start, mode, chn (3), dont care (3)

  //allow channel selection
  commandbits|=((chan-1)<<3);

  digitalWrite(SELPIN,LOW); //Select adc
  // setup bits to be written
  for (int i=7; i>=3; i--){
    digitalWrite(DATAOUT,commandbits&1<<i);
    //cycle clock
    digitalWrite(SPICLOCK,HIGH);
    digitalWrite(SPICLOCK,LOW);    
  }

  digitalWrite(SPICLOCK,HIGH);    //ignores 2 null bits
  digitalWrite(SPICLOCK,LOW);
  digitalWrite(SPICLOCK,HIGH);  
  digitalWrite(SPICLOCK,LOW);

  //read bits from adc
  for (int i=11; i>=0; i--){
    adcvalue+=digitalRead(DATAIN)<<i;
    //cycle clock
    digitalWrite(SPICLOCK,HIGH);
    digitalWrite(SPICLOCK,LOW);
  }
  digitalWrite(SELPIN, HIGH); //turn off device
  return adcvalue;
}
int test = 0;

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  while(Serial.available()>0){
    //snprintf (msg, 75,"%s", Serial.read());
    Serial.readString().toCharArray(msg,50);
    client.publish(pub_topic, msg);
    //Serial.println(msg);
  }
  for(int i=1; i<9; i++){
      bufer=electrodes+i;
      bufer.toCharArray(top,50);
      bufer=read_adc(i);
      bufer.toCharArray(msg,50);
      client.publish(top, msg);
      delay(1);
  }
}
