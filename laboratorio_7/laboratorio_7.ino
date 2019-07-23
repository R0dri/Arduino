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

int readLCD_buttons()
{
adc_key_in = analogRead(0);
if (adc_key_in>1000) return btnNONE;
if (adc_key_in<50) return btnRIGHT;
if (adc_key_in<250) return btnUP;
if (adc_key_in<450) return btnDOWN;
if (adc_key_in<650) return btnLEFT;
if (adc_key_in<850) return btnSELECT;

return btnNONE;
}
void setup() {
  lcd.begin(16,2);

}

void loop() {
  lcd.setCursor(0,0); //posicion del cursor
  lcd.print("TEMP:");

  lcd.setCursor(0,1);
  lcd.print("abajo");
 /* lcd_key=readLCD_buttons();
  if(lcd_key==btnRIGHT)
  {
  lcd.setCursor(0,0); //posicion del cursor
  lcd.print("RIGHT:");
  lcd.print(20);*/
  
  }
  
  

//}
