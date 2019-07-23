int temp = 250;
bool plus, minus, mot, light;
bool once = true;

void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

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
  if ((plus != minus) and (once)) {
    tempor(plus);
    once = false;
  }
  if ((once == false) and (plus == minus) and (plus == 0)) {
    once = true;
    delay(100);
  }
  if (light != mot) {
    Serial.print("Activating for: ");
    Serial.print(temp / 1000.00);
    Serial.println(" Seconds");
    digitalWrite(12, mot);
    digitalWrite(13, light);
    Serial.println(mot);
    Serial.println(light);
    delay(temp);
    digitalWrite(12, 0);
    digitalWrite(13, 0);
  }
}

void tempor (bool posi) {
  if (posi) {
    temp += 250;
  } else {
    temp -= 250;
  }
  if (temp < 250) {
    temp = 250;
  }
  if (temp > 10000) {
    temp = 10000;
  }
  Serial.println(temp);
}

