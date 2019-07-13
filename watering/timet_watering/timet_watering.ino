


// the timer object


unsigned long sinceOn = millis();
unsigned long sinceOff = millis();
bool isOn = false;
const int motorPin=9;
const int switchPin=2;
#define WATERING_TIME 3
#define INTEVAL_TIME 259200


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

void setup() {
    Serial.begin(9600);
    Serial.println("setup");
    pinMode(motorPin,OUTPUT);
}

void loop() {
    handlePressBtn();
    handleWatering();
//    delay(1000);
}
