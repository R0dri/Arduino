// Pinout Connections
int encoder_pin = 2;
int pin_out = 10;

// Speed variables
unsigned int ref = 800; //rpm
int rpm = 0;
int out = 0;//pwm voltage

// Time calculation variables.
unsigned int encoder_factor = 30000;//60*1000/2; //*time[ms]
unsigned int tiempo = 0;
unsigned int timeold = 0; 
unsigned int timenow = 0;

void setup(){
   Serial.begin(115200);
   Serial.setTimeout(100);
   pinMode(encoder_pin, INPUT);
   attachInterrupt(0, counter, RISING);
}

void loop(){
  if(Serial.available()){
    ref = Serial.parseInt();
    if(ref>900){ref=900;}
    while(Serial.available()){Serial.read();}
    //Serial.read();
    //Serial.println(ref);
    //Serial.flush();
  }f
}

void counter(){
    if(digitalRead(encoder_pin)) {
      noInterrupts();
        salidaMot(rpmMod(tiempoPasaoMillis()));
      interrupts();
    }
}

int tiempoPasaoMillis(){
   timenow = millis();
   tiempo = timenow-timeold;
   timeold = timenow;
   return tiempo;
}

int rpmMod(float tiemp){
  rpm = encoder_factor/tiemp;
  return (kp+tiemp*ki)*(-ref+rpm); //Error * Controlador
}

void salidaMot(int rpmAj){
  if(rpmAj>1200){rpmAj=1200;}
  if(rpmAj<0){rpmAj=0;}
  out = map(rpmAj,0,1200,255,0);
  analogWrite(pin_out,out);     //Salida a la Planta

  printVars();
}

void printVars(){
  Serial.print(ref);
  Serial.print(",");
  Serial.print(rpm);
  //Serial.print(",");
// Serial.print(rpmObj);
  Serial.print(",");
  Serial.println(out);
}
