int accDelay;
bool plus, minus, mot, light;
bool once = true;
int spid = 0;
int wait;

void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);

  //Switchs Proto
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  Serial.println("SERIAL READY");
}

void loop() {
  plus  = !digitalRead(11);
  minus = !digitalRead(10);
  mot   = !digitalRead(8);
  light = !digitalRead(9);

  if ((plus != minus) and (once)) { //Count Up or Down
    if(plus){
      Serial.println("accelerate in 5 sgs");
      delay(1000);  
      accelerate(5,1);
    }else{
      Serial.println("deaccelerate in 5 sgs");  
      analogWrite(3,255);
      delay(500);
      accelerate(5,-1);
    }
    
    // Run only once
    once = false;
  }
  if ((once == false) and (plus == minus) and (plus == 0)) { //One Time press Selection
    once = true;
    delay(100);
  }
  if (light != mot) {    //Sequence Selector
    wait = millis();
    while((!digitalRead(8))and((millis()-wait) < 3001));
    accelerate(3,0);
    Serial.println("accelerate in 5 sgs");
    delay(100);
    accelerate(10,1);
  }
}

void accelerate (int tiemp, int behave){
  if(behave != 0){
    if(behave>0){
      spid=1;
    }else{
      spid=255;
    }
    while((spid < 256) and (spid > 0)){
      analogWrite(3,spid);
      delay(tiemp*1000/256);
      spid=spid+behave;
      Serial.println(spid);
    }
  }else{
    delay(tiemp*1000);
  }
}



