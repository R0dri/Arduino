int ref = 0;
int sensibility = 1;

int const debounce = 400;
int const encoder_pin = 2; 
int const buttons_pin = 3;
int const b_up = 10;
int const b_down = 9;
int const out_pin = 6;
unsigned int const encoder_factor = 15000; //60*1000/4;

int volatile out = 0;
bool volatile up = false;
bool volatile down = false;
bool volatile flag = false;
unsigned int volatile rpm = 0;
int volatile err = 0;
unsigned int volatile timeOld = 0;
unsigned int volatile timeNow = 0;
unsigned int volatile tiempoPasado = 0;
unsigned volatile long bounceTimeButt = 0;
unsigned volatile long bounceTimeEnco = 0;

void setup() {
  pinMode(encoder_pin,INPUT);
  pinMode(buttons_pin,INPUT_PULLUP);
  pinMode(b_up,INPUT_PULLUP);
  pinMode(b_down,INPUT_PULLUP);
  

  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);
  analogWrite(out_pin,150);
  
  Serial.begin(9600);
  Serial.print("Velocidad actual: ");
  Serial.println(rpm);
  
  attachInterrupt(digitalPinToInterrupt(buttons_pin),buttons,FALLING);
  attachInterrupt(digitalPinToInterrupt(encoder_pin),encoder,FALLING);
}

void loop() {
  if(up){
    if(ref>1300){
      ref = 1400;
    }else{
      ref+=100;
    }
    up = false;
    Serial.print("Velocidad de Referencia actual: =+++++++++++++++++=");
    Serial.println(ref);
  }
  if(down){
    if(ref<100){
      ref = 0;
    }else{
      ref-=100;   
    }
    down = false;
    Serial.print("Velocidad de Referencia actual: ");
    Serial.println(ref);
  }
  
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

  //Serial.print("\t");
  //Serial.println(out);
}

void buttons(){
  noInterrupts();
  if(!digitalRead(buttons_pin)&&millis()>bounceTimeButt){
    up = !digitalRead(b_up);
    down = !digitalRead(b_down);
    Serial.println("Button Presed!");
    //Serial.println(up);
    //Serial.println(down);
    bounceTimeButt = millis()+debounce;
  }
  interrupts();
}
void encoder(){
  noInterrupts();
  //Serial.println("INTERRUPTED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
  timeNow = millis();
  if(!digitalRead(encoder_pin)&&timeNow>bounceTimeEnco){
      tiempoPasado = timeNow-timeOld;
      timeOld = timeNow;
      rpm = encoder_factor/tiempoPasado;
      Serial.print("--------------------------------------------");
      //Serial.println(rpm);
      bounceTimeEnco = timeNow+50;
  }
  interrupts();
}
