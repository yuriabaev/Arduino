


// the timer object


unsigned long sinceOn = millis();
unsigned long sinceOff = millis();
bool isOn = false;
const int motorPin=9;
#define WATERING_TIME 2
#define INTEVAL_TIME 259200

void WaterOn(){
  sinceOn=millis();
  isOn=true;
  digitalWrite(motorPin,HIGH);
}

void WaterOff(){
  sinceOff=millis();
  isOn=false;
  digitalWrite(motorPin,LOW);
}

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

void setup() {
    Serial.begin(9600);
    Serial.println("setup");
    pinMode(motorPin,OUTPUT);
}

void loop() {
    handleWatering();
}
