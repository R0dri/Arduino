int encoder_pin = 2;
int ref = 800; //rpm
int rpm, pulses = 0;
float rpmModd;
int out = 0;
int Ts = 0.3;
unsigned int timeold, timenow;
float tiempo = 0;
static volatile unsigned long debounce = 0; // Tiempo del rebote.
static volatile unsigned long debounced = 0; // Tiempo del rebote.

void setup(){
   Serial.begin(9600);
   pinMode(encoder_pin, INPUT);
   attachInterrupt(0, counter, RISING);
   ref+=200;
}
void loop(){}

void counter(){
    if(digitalRead(encoder_pin) && (micros()-debounce > 100)) {
      noInterrupts();
        tiempo = tiempoPasao();
        salidaMot(ref-rpmMod(tiempo/1000));
      interrupts();
    }
} 

int tiempoPasao(){
   timenow = millis();
   pulses = timenow-timeold;
   timeold = timenow;
   return pulses;
}

int rpmMod(float tiemp){
  rpm = 60/tiemp;
  rpmModd = ((1/Ts)*exp(-(1/Ts)*tiemp))*rpm;
  return rpmModd;
}

void salidaMot(int rpmObj){
  out = map(rpmObj,1400,1700,0,255);
  Serial.print(rpmObj);
  Serial.print(",");
  Serial.print(rpm);
  Serial.print(",");
  Serial.print(rpmModd);
  Serial.print(",");
  Serial.println(out);
  analogWrite(10,out);
}
