short counter = 0;
bool plus, minus, mot, light;
bool once = true;

void setup() {
  Serial.begin(9600);

  //LEDs
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  
  //Switchs Proto
  pinMode(7, OUTPUT);
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
    count(plus);
    once = false;
  }
  if ((once == false) and (plus == minus) and (plus == 0)) { //One Time press Selection
    once = true;
    delay(100);
  }
  if (light != mot) {    //Sequence Selector
    sequence(light);
  }
}

void count(bool posi){
  if (posi) {
    counter++;
  } else {
    counter--;
  }
  if (counter < 0) {
    counter = 16;
  }
  if (counter > 16){
    counter = 0;
  }
  Serial.println(counter);
  leds(counter);
}

void sequence (bool prim){
  // Timing Sequence Selector
  int del = 0; //Setting delay
  if(prim){
    del = 500;
  }else{
    del = 250;
  }
  //Sequence Builder
  for(int i=0;i<5;i++){
    for(int i=2;i<6;i++){
      digitalWrite(i,HIGH);
      delay(del);
      digitalWrite(i,LOW);
    }  
  }
}


void leds (int cont){
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
  if(cont>=8){
    digitalWrite(2,HIGH);
    cont-=8;
  }
  if(cont>=4){
    digitalWrite(3,HIGH);
    cont-=4;
  }
  if(cont>=2){
    digitalWrite(4,HIGH);
    cont-=2;
  }
  if(cont>0){
    digitalWrite(5,HIGH);
  }
}

