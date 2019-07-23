//Declara puertos de entradas y salidas
int sensor1=1;
int sensor2=3;
int sensor3=4;
int led1=11;
int led2=12;
int led3=10;
//Pin donde se encuentra el pulsador, entrada
//Pin donde se encuentra el LED, salida
//Funcionprincipal
void setup() // Se ejecuta cada vez que el Arduino se inicia
{
  Serial.begin(9600);
pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
pinMode(led3,OUTPUT);

//Configurar el LED como una salida
//PROGRAMACIÓN
}
//Funcionciclicla
void loop(){
  Serial.print(analogRead(sensor1));
    Serial.print("  ");
      Serial.print(analogRead(sensor2));
        Serial.print("  ");
          Serial.println(analogRead(sensor1));
  if(analogRead(sensor1<300)>500){
    digitalWrite(led1,HIGH);
  }else{
    digitalWrite(led1,LOW);
    
  }
   if(analogRead(sensor2<300)>600){
    digitalWrite(led2,HIGH);
  }else{
    digitalWrite(led2,LOW);
    
  }
   if(analogRead(sensor3<300)>500){
    digitalWrite(led3,HIGH);
  }else{
    digitalWrite(led3,LOW);
    
  }
}
