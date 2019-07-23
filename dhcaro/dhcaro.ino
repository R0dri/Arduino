int sensor;

void setup() {
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}

void lowop() {
  sensor = analogRead(A0);
  Serial.println(sensor);
  if(sensor>450){
    digitalWrite(13,HIGH);
  }else{
    digitalWrite(13,LOW);
  }
}
