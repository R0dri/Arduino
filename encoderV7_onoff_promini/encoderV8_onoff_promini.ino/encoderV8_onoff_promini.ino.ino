int ref = 0;
int sensibility = 1;

int const debounce = 400;
int const encoder_pin = 2;
int const out_pin = 6;
unsigned int const encoder_factor = 15000; //60*1000/4;

int volatile out = 0;
unsigned int volatile rpm = 0;
int volatile err = 0;
unsigned int volatile timeOld = 0;
unsigned int volatile timeNow = 0;
unsigned int volatile tiempoPasado = 0;
unsigned volatile long bounceTimeEnco = 0;

void setup() {
  pinMode(encoder_pin,INPUT);  

  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);
  analogWrite(out_pin,150);
  
  Serial.begin(9600);
  Serial.print("Velocidad actual: ");
  Serial.println(rpm);
  
  attachInterrupt(digitalPinToInterrupt(encoder_pin),encoder,FALLING);
}

void loop() {
  err = rpm-ref;
  if(err>=0){
     //out+=err*sensibility;
     out++;
   }else{
     //out-=err*sensibility
     out--;
   }
   
   if(out<0) out=0;
   if(out>255) out=255;
   if(timeNow+100<millis()){
     if(rpm>100) rpm-=100;
     else rpm = 0;
   }

  
   analogWrite(out_pin,out);
   Serial.print("rpm:\t");
   Serial.print(rpm);
   Serial.print("\terror:\t");
   Serial.print(err);
   Serial.print("\tOutput:\t");
   Serial.println(out);

   
}

void encoder(){
  noInterrupts();
  timeNow = millis();
  if(!digitalRead(encoder_pin)&&timeNow>bounceTimeEnco){
      tiempoPasado = timeNow-timeOld;
      timeOld = timeNow;
      rpm = encoder_factor/tiempoPasado;
      //Serial.println("--------------------------------------------");
      //Serial.println(rpm);
      bounceTimeEnco = timeNow+50;
  }
  interrupts();
}
