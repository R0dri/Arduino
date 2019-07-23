int ref = 0;
int sensibility = 1;

int const debounce = 500;
int const encoder_pin = 2;
int const buttons_pin = 3;
int const b_up = 10;
int const b_down = 9;
int const out_pin = 5;
unsigned int const encoder_factor = 15000; //60*1000/4;

int volatile out = 0;
bool volatile up = false;
bool volatile down = false;
bool volatile flag = false;
unsigned int volatile rpm = 0;
unsigned int volatile err = 0;
unsigned int volatile timeOld = 0;
unsigned int volatile timeNow = 0;
unsigned volatile long bounceTime = 0;

void setup() {
  pinMode(encoder_pin,INPUT);
  pinMode(buttons_pin,INPUT_PULLUP);
  pinMode(b_up,INPUT_PULLUP);
  pinMode(b_down,INPUT_PULLUP);

  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);
  analogWrite(out_pin,255);
  
  Serial.begin(9600);
  //Serial.setTimeout(1);
  Serial.print("Velocidad actual: ");
  Serial.println(rpm);
  
  attachInterrupt(digitalPinToInterrupt(buttons_pin),buttons,FALLING);
  attachInterrupt(digitalPinToInterrupt(encoder_pin),encoder,FALLING);
}

void loop() {
  if(up){
    if(out>250){
      out = 255;
    }else{
      out+=5;
    }
    up = false;
    analogWrite(5,out);
    Serial.print("Voltaje: ");
    Serial.print(out*3.3/255);
    Serial.print("\tPWM: ");
    Serial.println(out);
  }
  if(down){
    if(out<5){
      out = 0;
    }else{
      out-=5;   
    }
    down = false;
    analogWrite(5,out);
    Serial.print("Voltaje: ");
    Serial.print(out*3.3/255);
    Serial.print("\tPWM: ");
    Serial.println(out);
  }
}

void buttons(){
  noInterrupts();
  if(!digitalRead(buttons_pin)&&millis()>bounceTime){
    up = !digitalRead(b_up);
    down = !digitalRead(b_down);
    Serial.println("Button Presed!");
    Serial.println(digitalRead(b_up));
    Serial.println(digitalRead(b_down));
    bounceTime = millis()+debounce;
  }
  interrupts();
}
void encoder(){
  noInterrupts();
  if(digitalRead(encoder_pin)){
      timeNow = millis();
      interrupts();
      rpm = encoder_factor/tiempoPasado();
      err = rpm-ref;
      if(err>0){
        out+=err*sensibility;
      }else{
        out-=err*sensibility;
      }
      analogWrite(out_pin,out);
      Serial.print("Speed: ");
      Serial.println(out);
  }else{
    interrupts();
  }
}

int tiempoPasado(){
  //timeNow = millis();
  rpm = timeNow - timeOld;
  timeOld = timeNow;
  return rpm;
}
