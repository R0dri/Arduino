int encoder_pin = 2;
int ref = 800; //rpm
int pulses = 0;
float rpm;
float tiempo = 0;
unsigned int timeold, timenow;
static volatile unsigned long debounce = 0; // Tiempo del rebote.
static volatile unsigned long debounced = 0; // Tiempo del rebote.

void setup(){
   Serial.begin(9600);
   pinMode(encoder_pin, INPUT);
   attachInterrupt(0, counter, RISING);
}

void loop(){ 
}

void counter(){
  noInterrupts();
  if(digitalRead(encoder_pin) && (micros()-debounce > 100)) {
    debounce = micros();
    tiempo = tiempoPasao();
    rpm = 60000/tiempo;
    Serial.println(rpm);
  }
  interrupts();
}

int tiempoPasao(){
   timenow = millis();
   pulses = timenow-timeold;
   timeold = timenow;
   return pulses;
}

