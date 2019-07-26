


// the timer object


unsigned long sinceOn = millis();
unsigned long sinceOff = millis();
bool isOn = false;
const int motorPin=9;
const int switchPin=2;
const int WATERING_TIME=8;
const unsigned long INTEVAL_TIME=259200;


//motor
void WaterOn(){
  sinceOn=millis();
  motorOn();
}

void WaterOff(){
  sinceOff=millis();
  motorOff();
}
void motorOff(){;
  isOn=false;
  digitalWrite(motorPin,LOW);
}
void motorOn(){;
  isOn=true;
  digitalWrite(motorPin,HIGH);
}
//end motor

int timeSince(unsigned long time){ 
  return (millis()-time)/1000;
}


void handleWatering(){
   
Serial.print(millis());
    Serial.print(" ");
    Serial.print(sinceOff);
    Serial.print(" ");
    Serial.print(timeSince(sinceOff));
    Serial.print(" ");
    Serial.print(isOn);
    Serial.println();

  if (timeSince(sinceOff)>=INTEVAL_TIME && !isOn) {
  WaterOn();
  Serial.println(isOn);
  }

  if (timeSince(sinceOn)>=WATERING_TIME && isOn){
  WaterOff();
Serial.println(isOn);
  }
}
int switchState=0;
 
void handlePressBtn(){
  switchState = digitalRead(switchPin);
  Serial.println(switchState);
  if(switchState==HIGH){
      motorOn();
  }else{
      motorOff();
  }
}

String display = String(0 + ":"+0);
void handleDisplay(){
  unsigned long timeUntilNextRun =  INTEVAL_TIME -  timeSince(sinceOff);
  int days = timeUntilNextRun/3600;
  int hours = timeUntilNextRun/3600%60;
  int minutes = ((timeUntilNextRun/60)%60);
  int seconds = (timeUntilNextRun%60);
  display = String( hours);
   display = display.concat("e");
  Serial.println("timeUntilNextRun");
  Serial.print(hours);
  Serial.print(":");
  Serial.print(minutes);
   Serial.print(":");
  Serial.print(seconds);
  Serial.println();
  

  
}

void setup() {
    Serial.begin(9600);
    Serial.println("setup");
    pinMode(motorPin,OUTPUT);
}

void loop() {
    handlePressBtn();
    handleWatering();
    handleDisplay();
    delay(1000);
}
