#define pot A0

void setup() {
    pinMode(pot, INPUT);
    Serial.begin(9600);
}

void loop() {
//  Serial.println(analogRead(pot));
  Serial.println(map(analogRead(pot),0,1023,0,40)*250);
}
