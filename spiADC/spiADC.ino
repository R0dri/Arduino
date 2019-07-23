#include <ESP8266WiFi.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Empty.h>
#include <Servo.h>

#define indice  16 
#define pulgar   0
#define medio    2 
#define anular   4
#define pequen   5

Servo servoi;
Servo servoa;
Servo servom;
Servo servop;
Servo servoq;

const char* hello = "Protesis";
ros::NodeHandle  nh;

// WiFi configuration. Replace '***' with your data
const char* ssid = "Rodri's iPhone";
const char* password = "robotica";
IPAddress server(172,20,10,9);      // Set the rosserial socket ROSCORE SERVER IP address
const uint16_t serverPort = 11411;    // Set the rosserial socket server port

//Subscribers
void messageIndice( const std_msgs::UInt16& received_msg){
  Serial.println("Indice");
  hello = "indice";
  servoi.write(received_msg.data);
}
void messageAnular( const std_msgs::UInt16& received_msg){
  Serial.println("Anular");
  hello = "anular";
  servoa.write(received_msg.data);
}
void messageMedio( const  std_msgs::UInt16& received_msg){
  Serial.println("Medio");
  hello = "medio ";
  servom.write(received_msg.data);
}
void messagePulgar( const std_msgs::UInt16& received_msg){
  Serial.println("Pulgar");
  hello = "pulgar";
  servop.write(received_msg.data);
}
void messagePequen( const std_msgs::UInt16& received_msg){
  Serial.println("Pequen");
  hello = "pequen";
  servoq.write(received_msg.data);
}
void messageSerial( const std_msgs::Empty& received_msg){
  hello = "Serial";
  Serial.print(read_adc(1),DEC);
  Serial.print(",");
  Serial.print(read_adc(2),DEC);
  Serial.print(",");
  Serial.print(read_adc(3),DEC);
  Serial.print(",");
  Serial.print(read_adc(4),DEC);
  Serial.print(",");
  Serial.print(read_adc(5),DEC);
  Serial.print(",");
  Serial.print(read_adc(6),DEC);
  Serial.print(",");
  Serial.print(read_adc(7),DEC);
  Serial.print(",");
  Serial.println(read_adc(8),DEC);
}


ros::Subscriber<std_msgs::UInt16> subI("pos/indice", messageIndice);
ros::Subscriber<std_msgs::UInt16> subA("pos/anular", messageAnular);
ros::Subscriber<std_msgs::UInt16> subM("pos/medio",  messageMedio);
ros::Subscriber<std_msgs::UInt16> subP("pos/pulgar", messagePulgar);
ros::Subscriber<std_msgs::UInt16> subE("pos/pequen", messagePequen);
ros::Subscriber<std_msgs::Empty> sub("adc", messageSerial);

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);



#define SELPIN   15 //Selection Pin 
#define DATAOUT  13//MOSI 
#define DATAIN   12//MISO 
#define SPICLOCK 14//Clock 
int readvalue; 


void setupServo(){
  servoi.attach(indice);
  servop.attach(pulgar);
  servom.attach(medio);
  servoa.attach(anular);
  servoq.attach(pequen);
}
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
  nh.subscribe(subI);
  nh.subscribe(subA);
  nh.subscribe(subM);
  nh.subscribe(subP);
  nh.subscribe(subE);
  nh.subscribe(sub);
}
void setupSPI()  {
  //set pin modes 
  pinMode(SELPIN, OUTPUT); 
  pinMode(DATAOUT, OUTPUT); 
  pinMode(DATAIN, INPUT); 
  pinMode(SPICLOCK, OUTPUT); 
  //disable device to start with 
  digitalWrite(SELPIN,HIGH); 
  digitalWrite(DATAOUT,LOW); 
  digitalWrite(SPICLOCK,LOW); 
}


void setup(){ 
  Serial.begin(9600); 
  //Setup Wifi Connection
  setupWiFi();
  //Setup Servo outputs
  setupServo();
  //Setup Ros Clients
  setupRos();
  //Setup SPI interface
} 


void loop() {
 //readvalue = read_adc(2); 
 //Serial.println(readvalue,DEC); 
 //Serial.println(" "); 
 //delay(250); 
  str_msg.data = hello;
  chatter.publish( &str_msg );
  nh.spinOnce();
  delay(500);
} 


//ADC read thru SPI
int read_adc(int channel){
  int adcvalue = 0;
  byte commandbits = B11000000; //command bits - start, mode, chn (3), dont care (3)

  //allow channel selection
  commandbits|=((channel-1)<<3);

  digitalWrite(SELPIN,LOW); //Select adc
  // setup bits to be written
  for (int i=7; i>=3; i--){
    digitalWrite(DATAOUT,commandbits&1<<i);
    //cycle clock
    digitalWrite(SPICLOCK,HIGH);
    digitalWrite(SPICLOCK,LOW);    
  }

  digitalWrite(SPICLOCK,HIGH);    //ignores 2 null bitsesp
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


