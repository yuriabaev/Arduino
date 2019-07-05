


// the timer object


unsigned long sinceOn = millis();
unsigned long sinceOff = millis();
bool isOn = false;

void WaterOn(){
  sinceOn=millis();
  isOn=true;
  digitalWrite(13,HIGH);
}

void WaterOff(){
  sinceOff=millis();
  isOn=false;
  digitalWrite(13,LOW);
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

  if (timeSince(sinceOff)>=2 && !isOn) {
  WaterOn();
  Serial.println(isOn);
  }

  if (timeSince(sinceOn)>=1 && isOn){
  WaterOff();
Serial.println(isOn);
  }
}

void setup() {
    Serial.begin(9600);
    Serial.println("setup");
    pinMode(13,OUTPUT);
}

void loop() {
     handleWatering();
}
