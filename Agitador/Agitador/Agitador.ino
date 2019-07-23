int value = 1000;
void setup() {
  //Number
  pinMode(12,OUTPUT);
  pinMode( 9,OUTPUT);
  pinMode( 8,OUTPUT);
  pinMode(13,OUTPUT);

  //Digits
  pinMode(10,OUTPUT);
  pinMode( 7,OUTPUT);
  pinMode( 6,OUTPUT);
  pinMode( 4,OUTPUT);

  pinMode(A4,INPUT_PULLUP);
  pinMode(A5,INPUT_PULLUP);


  digitalWrite(10,0); //1
  digitalWrite( 7,1); //2
  digitalWrite( 6,1); //3
  digitalWrite( 4,1); //4

  Serial.begin(115200);
}

void loop() {
  print_number(value);
  if(!digitalRead(A4)){
     value++;
   Serial.println(value);
  }
  if(!digitalRead(A5)){
    value--;
    Serial.println(value);
  }
}

void print_number (int number){
  int A = number/10;
  int B = number/100;
  int C = number/1000;

  digitalWrite( 4,1);
  digitalWrite(10,0);
  print_digit(C%10);
  delay(8);

  digitalWrite(10,1);
  digitalWrite( 7,0);
  print_digit(B%10);
  delay(5);

  digitalWrite( 7,1);
  digitalWrite( 6,0);
  print_digit(A%10);
  delay(5);

  digitalWrite( 6,1);
  digitalWrite( 4,0);
  print_digit(number%10);
  delay(5);
}

void print_digit (int digit){
  int A, B, C, D, a, b, c;
  A=digit%2;

  a=digit/2;
  B=a%2;

  b=a/2;
  C=b%2;

  c=b/2;
  D=c%2;

  digitalWrite(12,D);//4
  digitalWrite( 9,C);//3
  digitalWrite( 8,B);//2
  digitalWrite(13,A);//1
}

