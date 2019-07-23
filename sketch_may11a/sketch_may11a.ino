/*
this program taken from arduino Example .
  modified by By Mohannad Rawashdeh
  http://www.genotronex.com
https://www.instructables.com/

  This code used to control the digital potentiometer
  MCP41100 connected to  arduino Board
  CS >>> D10
  SCLK >> D13
  DI  >>> D11
  PA0 TO VCC
  PBO TO GND
  PW0 TO led with resistor 100ohm .
*/
#include <SPI.h>

byte address = 0x00;
int CS= 10;

void setup(){
  Serial.begin(9600);
  pinMode (CS, OUTPUT);
  SPI.begin();
}
String amp;
void loop(){
  while(Serial.available()){
    amp = Serial.readStringUntil(';');
    Serial.flush();
    Serial.print("Cambiando amplitud a: ");
    Serial.println(amp);
    digitalPotWrite(amp.toInt());
  }
}

int digitalPotWrite(int value)
{
digitalWrite(CS, LOW);
SPI.transfer(address);
SPI.transfer(value);
digitalWrite(CS, HIGH);
}
