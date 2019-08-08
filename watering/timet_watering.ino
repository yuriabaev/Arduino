
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// the timer object
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display


unsigned long sinceOn = millis();
unsigned long sinceOff = millis();
bool isOn = false;
bool isCustom = false;
const int motorPin = 9;
const int switchPin = 2;
const int WATERING_TIME = 8;
const unsigned long INTEVAL_TIME = 259200;


//motor
void WaterOn() {
  sinceOn = millis();
  motorOn();
}

void WaterOff() {
  sinceOff = millis();
  motorOff();
}
void motorOff() {
  ;
  isOn = false;
  digitalWrite(motorPin, LOW);
}
void motorOn() {
  ;
  isOn = true;
  digitalWrite(motorPin, HIGH);
}
//end motor

int timeSince(unsigned long time) {
  return (millis() - time) / 1000;
}


void handleWatering() {
  if (isCustom)return;
  Serial.print(millis());
  if (timeSince(sinceOff) >= INTEVAL_TIME && !isOn) {
    WaterOn();
    Serial.println(isOn);
  }

  if (timeSince(sinceOn) >= WATERING_TIME && isOn) {
    WaterOff();
    Serial.println(isOn);
  }
}
int switchState = 0;

void handlePressBtn() {
  switchState = digitalRead(switchPin);
  Serial.println(switchState);
  if (switchState == HIGH) {
    motorOn();
    isCustom = true;
  } else {
    motorOff();
    isCustom = false;
  }
}

String display = String(0 + ":" + 0);
void handleDisplay() {
  unsigned long timeUntilNextRun =  INTEVAL_TIME -  timeSince(sinceOff);
  int days = timeUntilNextRun / 3600 / 24;
  int hours = timeUntilNextRun / 3600 % 24;
  int minutes = ((timeUntilNextRun / 60) % 60);
  int seconds = (timeUntilNextRun % 60);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(String(days) + ":" + String(hours) + ":" + String(minutes) + ":" + String(seconds));

  if (isCustom) {
    lcd.setCursor(0, 1);
    lcd.print("on");
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("setup");
  pinMode(motorPin, OUTPUT);

  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("ghj");

}

void loop() {
  handlePressBtn();
  handleWatering();
  handleDisplay();
  delay(1000);
}
