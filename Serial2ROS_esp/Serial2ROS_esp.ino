#include <ESP8266WiFi.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Empty.h>

const char* hello = "Protesis";
ros::NodeHandle  nh;

// WiFi configuration. Replace '***' with your data
const char* ssid = "Rodri's iPhone";
const char* password = "robotica";
IPAddress server(172,20,10,9);      // Set the rosserial socket ROSCORE SERVER IP address
const uint16_t serverPort = 11411;    // Set the rosserial socket server port

//Subscribers
void messageSerial( const std_msgs::String& received_msg){
  Serial.print(received_msg.data);
}


ros::Subscriber<std_msgs::String> sub("teensy", messageSerial);

std_msgs::UInt16 str_msg;
ros::Publisher chatter("chatter/teensy", &str_msg);


int readvalue; 

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
void setupRos()  {
  nh.getHardware()->setConnection(server, serverPort);
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);
}


void setup(){ 
  Serial.begin(9600); 
  Serial.setTimeout(100);
  //Setup Wifi Connection
  setupWiFi();
  //Setup Ros Clients
  setupRos();
} 


void loop() { 
  while(Serial.available()>0){
    str_msg.data = Serial.read();
    chatter.publish( &str_msg );
    nh.spinOnce();
  }
} 
