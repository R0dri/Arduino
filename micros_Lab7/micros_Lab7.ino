#include <LiquidCrystal.h>
LiquidCrystal lcd(8,9,4,5,6,7);
#define btnRIGHT 0
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5

int lcd_key = 0;
int adc_key_in=0;

int medida = 0;
int pot = 0;
int potnow;
int pos = 0;

int t =0;
int times = 10;

int maxim = 20;
int minim = 0;
int med;

void setup() {
  lcd.begin(16,2);
}

void loop() {

  //med = medidor();
  med = analogRead(A8);
  
  lcd.setCursor(pos,0); //posicion del cursor
  lcd.print("TEMP");
  lcd.setCursor(posicion(),1);
  lcd.print(med);

  if(lcd_key==btnSELECT) {
    delay(100);
  }
  delay(100);  
  lcd.clear();

  if(blinking()){
    delay(500);
  }

}

bool set=false;

bool blinking(){
  lcd_key=readLCD_buttons();
  if(lcd_key==btnUP) {
    set = !set;
  }
  return set;
}

int medidor(){
  posicion();
  
  potnow = analogRead(A8);  
  if(potnow>pot){
    medida++;
    pot = potnow;
  }
  if(potnow<pot){
    medida--;
    pot = potnow;
  }
  if(medida>maxim){
    medida = maxim;
  }
  if(medida<minim){
    medida = minim;
  }
  
  return medida;
}

int posicion(){
  lcd_key=readLCD_buttons();
  if(lcd_key==btnRIGHT) {
    pos++;
  }
  if(lcd_key==btnLEFT) {
    pos--;
  }
  if(pos>maxim){
    pos = maxim;
  }
  if(pos<minim){
    pos = minim;
  }

  return pos;
}

int readLCD_buttons() {
  adc_key_in = analogRead(0);
  if (adc_key_in>1000) return btnNONE;
  if (adc_key_in<50) return btnRIGHT;
  if (adc_key_in<250) return btnUP;
  if (adc_key_in<450) return btnDOWN;
  if (adc_key_in<650) return btnLEFT;
  if (adc_key_in<850) return btnSELECT;

  return btnNONE;
}
