//Definicion de pines de control
#define motor   5
#define foco    6
//Definicion de pines de entrada
#define pot    A0
#define puls   A1
#define LDR    A2`

#define ldrSensibilidad 175

void setup() {
  //Configurar pines de salida
  pinMode(motor, OUTPUT);
//  pinMode(5,OUTPUT);
  pinMode(foco, OUTPUT);
  //Conigurar pines de entrada
  pinMode(pot, INPUT);
  pinMode(puls, INPUT_PULLUP);
  pinMode(LDR, INPUT_PULLUP);


  Serial.begin(9600);
}

void loop() {
  if(puls){
    activarTiempo(tiempo(),selector());
  }
}

bool selector(){
  if(analogRead(LDR>ldrSensibilidad)){
    return true;
  }else{
    return false;
  }
}

int tiempo(){
//  return map(analogRead(pot),0,200,0,32);
  return map(analogRead(pot),0,1023,0,40)*250; 
}

void activarTiempo (int temp,bool dispositivo){
  if(dispositivo){
    Serial.println("motor");
//    digitalWrite(5,HIGH);
    digitalWrite(motor,HIGH);
  }else{
    digitalWrite(foco,HIGH);
  }
  delay(1000);
  delay(temp);
  digitalWrite(foco,LOW);
  digitalWrite(motor,LOW);
}

