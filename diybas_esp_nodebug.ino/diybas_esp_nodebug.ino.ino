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

#include <WiFi.h>
#include <PubSubClient.h>

//String string;
bool debug = true;

// Update these with values suitable for your network.
const char* ssid = "Mita";
const char* password = "123queseyo";
const char* mqtt_server = "192.168.1.2";

//Topics
String electrodes = "e/";
String bufer;
const char* pub_topic = "diybas/electrodes";
const char* sub_topic = "diybas/esp";

//SPI
#define SELPIN   22//Selection Pin 
#define DATAOUT  23//MOSrodste
#define DATAIN   19//MISO 
#define SPICLOCK 18//Clock 
int readvalue;


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[5];
char top[4];
int value = 0;

int pinled = 2;

void setup() {
  //Set led as indicator and turnoff during operation
  pinMode(pinled, OUTPUT);
  
  if(debug){
    Serial.begin(115200);
    //Connecting to wifi
    Serial.println("Connecting");
    setup_wifi();
    Serial.println("Connected!");
  }else{
    setup_wifi();
  }

  //Set MQTT Connection with server
  client.setServer(mqtt_server, 1883);
  //set SPI pin modes
  pinMode(SELPIN, OUTPUT);
  pinMode(DATAOUT, OUTPUT);
  pinMode(DATAIN, INPUT);
  pinMode(SPICLOCK, OUTPUT);
  //disable device to start with
  digitalWrite(SELPIN, HIGH);
  digitalWrite(DATAOUT, LOW);
  digitalWrite(SPICLOCK, LOW);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  pinMode(pinled, OUTPUT);
  digitalWrite(pinled, HIGH);
  delay(100);
  digitalWrite(pinled, LOW);
  delay(100);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    if(debug){
      Serial.print(".");
    }
    delay(450);
    digitalWrite(pinled, HIGH);
    delay(150);
    digitalWrite(pinled, LOW);
  }
}

void reconnect() {
  if(debug) Serial.println("Lost connection with server");
  // Loop until we're reconnected
  while (!client.connected()) {
    // Attempt to connect
    if (client.connect("ESP DIYBAS Client")) {
      // Once connected, publish an announcement...
      client.publish(pub_topic, "Connected!");
      if(debug) Serial.println("Reconnected to MQTT Server!");
    } else {
      // Wait 5 seconds before retrying
      delay(5000);
      if(debug) Serial.println("Retrying...");
    }
  }
}

int read_adc(int chan) {
  int adcvalue = 0;
  byte commandbits = B11000000; //command bits - start, mode, chn (3), dont care (3)

  //allow channel selection
  commandbits |= ((chan - 1) << 3);

  digitalWrite(SELPIN, LOW); //Select adc
  // setup bits to be written
  for (int i = 7; i >= 3; i--) {
    digitalWrite(DATAOUT, commandbits & 1 << i);
    //cycle clock
    digitalWrite(SPICLOCK, HIGH);
    digitalWrite(SPICLOCK, LOW);
  }

  digitalWrite(SPICLOCK, HIGH);   //ignores 2 null bits
  digitalWrite(SPICLOCK, LOW);
  digitalWrite(SPICLOCK, HIGH);
  digitalWrite(SPICLOCK, LOW);

  //read bits from adc
  for (int i = 11; i >= 0; i--) {
    adcvalue += digitalRead(DATAIN) << i;
    //cycle clock
    digitalWrite(SPICLOCK, HIGH);
    digitalWrite(SPICLOCK, LOW);
  }
  digitalWrite(SELPIN, HIGH); //turn off device
  return adcvalue;
}


int test = 0;
int spacer = 0;

void loop() {
//  if(debug){
//    Serial.println("We are in the loop");
//    client.publish(pub_topic,"hello");
//  }

  if (spacer > 50) {
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
    spacer = 0;
  }
  spacer++;
  
  for (int i = 1; i < 9; i++) {
    bufer = electrodes + i;
    bufer.toCharArray(top, 4);
    bufer = read_adc(i);
    bufer.toCharArray(msg, 5);
    client.publish(top, msg);
    delay(1);
  }
}
