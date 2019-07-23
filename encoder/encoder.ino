int encoder_pin = 2;            //Pin 2, donde se conecta el encoder       
int rpm = 0;           // Revoluciones por minuto calculadas.
unsigned int pulses = 0;       // Número de pulsos leidos por el Arduino en un segundo
unsigned int timeold, timenow;
int ppt = 2 ; // Número de muescas que tiene el disco del encoder.
static volatile unsigned long debounce = 0; // Tiempo del rebote.

void setup(){
   Serial.begin(9600);
   pinMode(encoder_pin, INPUT);
   attachInterrupt(0, counter, RISING);
   pulses = 0;
   rpm = 0;
   timeold = 0;
   timenow = 0;
  Serial.print("Seconds ");
  Serial.print("RPM ");
  Serial.println("Pulses ");
}

void loop(){ 
   timenow = millis();
   if (timenow - timeold >= 1000){  // Se actualiza cada segundo
      noInterrupts();
      rpm = 30*pulses; 
      Serial.print(timenow/1000);Serial.print("    ");
      timeold = timenow;
      Serial.print(rpm);
      Serial.print("     ");Serial.println(pulses);
      pulses = 0;
      interrupts(); 
   }
}

void counter(){
   if(digitalRead(encoder_pin) && (micros()-debounce > 10)) { 
      debounce = micros();
      pulses++;
   }
} 

