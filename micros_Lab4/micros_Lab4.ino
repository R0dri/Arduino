short counter = 0;
bool plus, minus, mot, light;
bool once = true;
int del = 10;
int anal = 0;

void setup() {
  Serial.begin(9600);

// LEDS
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  
  //Switchs Proto
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
    secuencia(plus);
    once = false;
  }
  if ((once == false) and (plus == minus) and (plus == 0)) { //One Time press Selection
    once = true;
    delay(100);
  }
  if (light != mot) {    //Sequence Selector
    activate(light);
  }
}

void secuencia (bool sel){
  if(sel){  //EJERCICIO 1
    anal = analogRead(A0);
    Serial.println(anal);
    binPrint(potParce(analogRead(anal)));
  }else{    //EJERCICIO 2
    for(int j=0;j<4;j++){
      for(int h=0;h<16;h++){
        binPrint(h);
        anal = analogRead(A0);
        anal+=100;
        delay(anal); 
        Serial.println(anal);
      }
    }
    binPrint(0);
    delay(100);
    binPrint(16);
    delay(100);
    binPrint(0);
    delay(100);
    binPrint(16);
    delay(100);
    binPrint(0);
  }
}

void activate (bool onoff){   //EJERCICIO 3
  for(int j=0;j<4;j++){
    int h = 0;
      while(h<17){
        anal = analogRead(A0);
        if(anal>512){
          h++;
        }else{
          h--;
        }
        if(h<0){h=16;}
        Serial.println(anal);
        binPrint(h);
        delay(150); 
      }
    }
    binPrint(0);
    delay(100);
    binPrint(16);
    delay(100);
    binPrint(0);
    delay(100);
    binPrint(16);
    delay(100);
    binPrint(0);
}

void binPrint (int cont){
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  Serial.println(cont);
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

int potParce (int analog){
  return map(analog,0,1022,0,16);
}

