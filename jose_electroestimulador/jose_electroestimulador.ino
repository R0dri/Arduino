#include <SPI.h>
  
#define salida 13
#define CS 10

byte address = 0x00;


String tot,fr,durp,amp;
int tiempo_onda,tiempo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  pinMode (salida, OUTPUT);
  pinMode (CS, OUTPUT);  
  
  Serial.println("probando led, parpadeo 2 veces");
  digitalWrite(salida,HIGH);
  delay(200);
  digitalWrite(salida,LOW);
  delay(200);
  digitalWrite(salida,HIGH);
  delay(200);
  digitalWrite(salida,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()){
    tot=Serial.readStringUntil(';');
    durp=Serial.readStringUntil(';');
    fr=Serial.readStringUntil(';');
    amp=Serial.readStringUntil(';');
    Serial.flush();

    Serial.print("duracion sesion (s): ");
    Serial.println(tot);
    Serial.print("duracion pulso(s): ");
    Serial.println(durp);
    Serial.print("frequencia(hz): ");
    Serial.println(fr);
    Serial.print("amplitud(0-128): ");
    Serial.println(amp);
    Serial.println();

    
    digitalPotWrite(amp.toInt());
    Serial.println("digital pot");
    onda(tot.toInt(),durp.toInt(),fr.toInt());
    Serial.println("onda");
  }
}

void blt(int duracion){
  Serial.println("Haciendo la rutina de blt");
  duracion=1000/duracion;
  int tiempo_blt = millis();
  duracion += tiempo_blt;
  
  while(tiempo_blt<duracion){
    while(Serial.available()){
     amp = Serial.readStringUntil(';');
     Serial.flush();
     Serial.print("Cambiando amplitud a: ");
     Serial.println(amp);
     digitalPotWrite(amp.toInt());
   }
   tiempo_blt = millis();
  }
}

void digitalPotWrite(int value) {
  digitalWrite(CS, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(CS, HIGH);
}

void onda (int duracion,int dpulso, int freq){
  duracion*=1000;
  tiempo_onda = millis();
  duracion += tiempo_onda;
  while(tiempo_onda<duracion){
    pulso(dpulso,freq);
    blt(dpulso);
      
    tiempo_onda = millis();
  }
}
  

void pulso (int duracion, int freq){
  duracion=1000/duracion;
  tiempo = millis();
  duracion += tiempo;
  
  Serial.println("PULSO");
  while(tiempo<duracion){
    digitalWrite(salida,HIGH);
    delay(500/freq);
    digitalWrite(salida,LOW);
    delay(500/freq);
    tiempo = millis();
  }
}
