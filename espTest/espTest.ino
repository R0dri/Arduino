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

String string;

// Update these with values suitable for your network.
const char* ssid = "rodri";
const char* password = "rodrimen";
const char* mqtt_server = "192.168.43.246";

//Topics
const char* pub_topic = "agitadora/out";
const char* sub_topic = "agitadora/in";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

int pinled = 13;

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  Serial.setTimeout(10);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
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
  // Serial.print("Message arrived [");
  // Serial.print(topic);
  // Serial.print("] ");
  //for (int i = 0; i < length; i++) {
  //  Serial.print((char)payload[i]);
  //}
  //Serial.println();

  // Switch on the LED if an 1 was received as first character
   if ((char)payload[1] == 'F') {
     digitalWrite(pinled, LOW);   // it is acive low on the ESP-01
   } else if((char)payload[1] == 'N') {
     digitalWrite(pinled, HIGH);  // Turn the LED off by making the voltage HIG   
   }else {
     switch((int)payload[0]-48){
      case 1:
        Serial.print(500);
        break;
      case 2:
        Serial.print(800);
        break;
      case 3:
        Serial.print(1000);
        break;
      case 4:
        Serial.print(0);
        break;
      default:
        Serial.print((int)payload[0]-48);
        break;
     }
   }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP12Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(pub_topic, "Connected!");
      // ... and resubscribe
      client.subscribe(sub_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 s```econds before retrying
      delay(5000);
    }
  }
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  while(Serial.available()>0){
//    snprintf (msg, 75,"%s", Serial.read());
  Serial.readString().toCharArray(msg,50);
    client.publish(pub_topic, msg);
    //Serial.println(msg);
  }
  

//   long now = millis();
//   if (now - lastMsg > 2000) {
//     lastMsg = now;
//     ++value;
//     snprintf (msg, 75, "hello world #%ld", value);
//     Serial.print("Publish message: ");
//     Serial.println(msg);
//     client.publish(pub_topic, msg);
//   }
}

