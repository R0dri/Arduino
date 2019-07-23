int ref = 0;
int sensibility = 1;
int lecture = 0;

int const debounce = 400;
int const encoder_pin = 2;
int const out_pin = 6;
int const analog_pin = 3;
unsigned int const encoder_factor = 15000; //60*1000/4;

unsigned int volatile out = 255;
unsigned int volatile rpm = 0;
int volatile err = 0;
unsigned int volatile timeOld = 0;
unsigned int volatile timeNow = 0;
unsigned int volatile tiempoPasado = 0;
unsigned volatile long bounceTimeEnco = 0;

void setup() {
  analogWrite(out_pin,out);
  pinMode(encoder_pin,INPUT);
  pinMode(4,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(analog_pin,INPUT);
  digitalWrite(4,HIGH);

  attachInterrupt(digitalPinToInterrupt(encoder_pin),encoder,FALLING);

  Serial.begin(9600);
  Serial.println("Program Started");
}

void loop() {
  //Set Reference
  lecture = analogRead(analog_pin);
  ref = map(lecture,0,1000,3,0);
  if(ref<0) ref = 0;
  if(ref>3) ref = 3;
  ref*=200;
  ref+=200;
  if(ref==200) ref = 0;

  if(ref==600) digitalWrite(13,HIGH);
  else         digitalWrite(13,LOW);
  //Calculo del Error y Output
  err = rpm-ref;
  //if(err>50) err = 50;
  //if(err<-50) err = -50;
  if(err!=0){
    if(err>0) out+=5;//err/sensibility;
    else out-=5;//err/sensibility;  
  }
  
  //Set Output Limit
  if(out>255) out=255;

  //Rpm Dampner
  if(timeNow+100<millis()){
    if(rpm>100) rpm-=100;
    else rpm = 0;
  }

  //Set Output
  analogWrite(out_pin,out);

  debug(0);
}

void encoder(){
  noInterrupts();
  timeNow = millis();
  if(!digitalRead(encoder_pin)&&timeNow>bounceTimeEnco){
      tiempoPasado = timeNow-timeOld;
      timeOld = timeNow;
      rpm = encoder_factor/tiempoPasado;
      //Serial.println(rpm);
      bounceTimeEnco = timeNow+10;
  }
  interrupts();
}

void debug(bool analog){
  Serial.print("Ref:\t");
  Serial.print(ref);
  Serial.print("\tRPM:\t");
  Serial.print(rpm);
  Serial.print("\tErr:\t");
  Serial.print(err);
  Serial.print("\tOut:\t");
  if(analog){
    Serial.print(out);
    Serial.print("\tPot:\t");
    Serial.println(lecture);  
  }else Serial.println(out);
}

