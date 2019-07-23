int num [][7] = {
  { 4, 7,11,1,2,10, 0},//.
  { 7, 4, 0,0,0, 0, 0}, //1
  {11, 7, 5,1,2, 0, 0}, //2
  {11, 7, 5,4,2, 0, 0}, //3
  {10, 5, 7,4,0, 0, 0}, //4
  {11,10, 5,4,2, 0, 0},//5
  {11,10, 5,4,2, 1, 0},//6
  {11, 7, 4,0,0, 0, 0}, //7
  {11, 7, 5,1,2, 4,10},//8
  { 5,10,11,7,4, 0, 0},//9
  { 1, 2, 3,4,5, 6, 7}  //Numeracion
};

              //{ 0,1,2,3,4,5, 6,7, 8, 9,10,11,12}    Display Pins
int pinMap [] = {13,2,3,4,5,6,13,9,13,11, 8, 7,10}; //Arduino Pins

int readed = 0;
int aux,one,two;
int del = 10;
bool flag = true;

void setup() {
//  Serial.begin(9600);
//  Serial.setTimeout(10);
//  Serial.println("Serial Connection Initizalized!!!");
  for(int i=2;i<12;i++){
    pinMode(i,OUTPUT);
  }
}

void loop() {
//  if (Serial.available() > 0) {
//    readed = Serial.parseInt();
    readed = analogRead(A0);
//    Serial.println(readed);
    readed = map(readed,30,200,0,99);
    one = readed/10;
    two = readed - one*10;
//    Serial.flush();
//    Serial.print("Set num to: ");
//    Serial.println(readed);
/*    if(flag){
      one = readed;
      flag = false;
    }else{
      two = readed;
      flag = true;
    }*/
    
    show(one,two);
    //delay(50);
 // }
}

void show (int one, int two){
  for(int i=0;i<10;i++){
    digitalWrite(10,HIGH);
    displayNum(one);
    delay(del);
    digitalWrite(10,LOW);

    digitalWrite(11,HIGH);
    displayNum(two);
    delay(del);
    digitalWrite(11,LOW);
  }
}

void displayNum (int numer){
  for(int i=2;i<10;i++){
    digitalWrite(i,LOW);
  }
  for(int i=0; i<7; i++){
    aux = num[numer][i];
    Serial.println(pinMap[aux]);
    digitalWrite(pinMap[aux],HIGH);
  }
}
