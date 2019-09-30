
/*Program to control LED (ON/OFF) from ESP32 using Serial Bluetooth
 * Thanks to Neil Kolbans for his efoorts in adding the support to Arduino IDE
 * Turotial on: www.circuitdigest.com 
 */

#include "BluetoothSerial.h" //Header File for Serial Bluetooth, will be added by default into Arduino
#include <Morse.h>

Morse morse(2);

BluetoothSerial ESP_BT; //Object for Bluetooth

int incoming;
String command;
int LED_BUILTIN = 2;


String getCommand() {
  String command="";
  while(ESP_BT.available()) //Check if we receive anything from Bluetooth
  {
    char  c=ESP_BT.read();
    command+=String(c);
   
  };
  return command;
}


void doLedOn() {
    //digitalWrite(LED_BUILTIN, HIGH);
    morse.dot();
    ESP_BT.println("LED turned ON");
}

void doLedOff() {
   //digitalWrite(LED_BUILTIN, LOW);
   morse.dash();
   ESP_BT.println("LED turned OFF");
}

void setup() {
  Serial.begin(9600); //Start Serial monitor in 9600
  ESP_BT.begin("ESP32_LED_Control"); //Name of your Bluetooth Signal
  Serial.println("Bluetooth Device is Ready to Pair");

  pinMode (LED_BUILTIN, OUTPUT);//Specify that LED pin is output
}

void loop() {
  command=getCommand();
  morse.dash();
   morse.dot();

//  if(command.length() !=0){
//    
//    Serial.print("Received:");Serial.println(command );
//    if (command== "on") {
//        doLedOn();
//    }else if (command== "off") {
//        doLedOff();
//    }else{
//        ESP_BT.println("no such command");
//    }    
 // }
  //delay(20);
  delay(2000);
}
