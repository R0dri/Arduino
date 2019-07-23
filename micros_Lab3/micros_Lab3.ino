short counter = 0;
bool plus, minus, mot, light;
bool once = true;
int del = 10;

void setup() {
  Serial.begin(9600);

  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  //Stepper
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  
  //Switchs Proto
  pinMode(7, OUTPUT);
  digitalWrite(7,LOW);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
}


void loop() {
  plus  = !digitalRead(11);
  minus = !digitalRead(10);
  mot   = !digitalRead(8);
  light = !digitalRead(9);
  
  if ((plus != minus) and (once)) { //Count Up or Down
    paso(plus);
   // once = false;
  }
 // if ((once == false) and (plus == minus) and (plus == 0)) { //One Time press Selection
   // once = true;
   // delay(100);
 // }
  if (light != mot) {    //Sequence Selector
    activate(light);
  }
}

int i=2;
void paso (bool frwrd){
  for(int j=2;j<6;j++){
     digitalWrite(j,LOW);
     Serial.println(j);
  }
  if(i>5){i=2;}//Serial.println("HEY");}
  if(i<2){i=5;}//Serial.println("HO");}
  if(frwrd){
     Serial.print("Paso ++ ");
     Serial.println(i);
     digitalWrite(i,HIGH);
     i++;
     delay(del);
  }else{
     Serial.print("Paso--");
     Serial.println(i);
     digitalWrite(i,HIGH);
     i--;
     delay(10);
  }
}
void activate (bool onoff){
  if(onoff){
 //   digitalWrite(13,HIGH);
    //if(flag){
      del = 2;
      //flag = false;
    //}
  }else{
   // digitalWrite(13,LOW);
    del = 10;
    //flag = true;
  }
}

