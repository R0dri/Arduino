int input;
 
void setup(){
 
  pinMode(10, OUTPUT); // Declaramos que utilizaremos el pin 13 como salida
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
 
  Serial.begin(9600);
}
 
void loop()
{
  if (Serial.available()>0){
 
    input=Serial.read();
 
    if (input=='1')
    {
 
      digitalWrite(10, LOW);
      delay(20);//ARRIBA
      Serial.println("ARRIBA");
 
    }
    if (input=='2')
    {
 
      digitalWrite(11, LOW);
      delay(20);//ABAJO
      Serial.println("ABAJO");
 
    }
    if (input=='3')
    {
 
      digitalWrite(12, LOW); //IZQk
      digitalWrite(10, LOW);
      delay(20);
      Serial.println("IZQ");
 
    }
    if (input=='4')
    {
 
      digitalWrite(13, LOW); //DER
      digitalWrite(10, LOW);
      delay(20);
      Serial.println("DER");
 
    }
    
    else
 
    {

      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH); //Si el valor de input es diferente de 1, se apaga el LED
 
    }
 
  }
}
