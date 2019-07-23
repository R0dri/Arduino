void setup(){
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
 
  Serial.begin(9600);
  Serial.setTimeout(1);
}

void loop() {
  if (Serial.available()>0){
    int in = Serial.readString().toInt();
    switch(in){
      case 1:
          digitalWrite(10, LOW);
          delay(20);//ARRIBA
          Serial.println("ARRIBA");
          break;
      case 2:
          digitalWrite(11, LOW);
          delay(20);//ABAJO
          Serial.println("ABAJO");
          break;
      case 3:
          digitalWrite(12, LOW); //IZQ
          digitalWrite(10, LOW);
          delay(20);
          Serial.println("IZQ");
          break;
      case 4:
          digitalWrite(13, LOW); //DER 9
          digitalWrite(10, LOW);
          delay(20);
          Serial.println("DER");
          break;
     default:
      Serial.print("Defaulted with: ");
      Serial.println(in);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH); //Si el valor de input es diferente de 1, se apaga el LED
    }
  }
}
