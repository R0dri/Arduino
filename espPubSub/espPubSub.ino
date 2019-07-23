/*
 * rosserial PubSub Example
 * Prints "hello world!" and toggles led
 */
#include <ESP8266WiFi.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>

ros::NodeHandle  nh;

// WiFi configuration. Replace '***' with your data
const char* ssid = "Tejada";
const char* password = "06055819";
IPAddress server(192,168,0,32);      // Set the rosserial socket ROSCORE SERVER IP address
const uint16_t serverPort = 11411;    // Set the rosserial socket server port

void setupWiFi() {                    // connect to ROS server as as a client
  Serial.print("Connecting to ");
  Serial.println(ssid);
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


void messageCb( const std_msgs::Empty& toggle_msg){
  //digitalWrite(LED_BUILTIN, HIGH-digitalRead(13));   // blink the led
  Serial.println("Got Data!");
}

ros::Subscriber<std_msgs::Empty> sub("toggle_led", messageCb );



std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char hello[13] = "hello world!";

void setup(){
  Serial.begin(115200);
  //Setup Wifi Connection
  setupWiFi();
  //ROS
  //pinMode(LED_BUILTIN, OUTPUT);
  nh.getHardware()->setConnection(server, serverPort);
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);
}

void loop(){
  str_msg.data = hello;
  chatter.publish( &str_msg );
  nh.spinOnce();
  delay(500);
}
