int lecture;

void setup() {
  pinMode(INPUT,A0);
  pinMode(OUTPUT,11);
  Serial.begin(9600);
  Serial.println("Arduino started!");
}

void loop() {
  //lecture = analogRead(A0);
  lecture = map(analogRead(A0),0,1000,255,0);
  analogWrite(6,lecture);
  Serial.print("Pot value:\t");
  Serial.print(analogRead(A0));
  Serial.print("\tmapped value:\t");
  Serial.println(lecture);
  delay(100);
}
