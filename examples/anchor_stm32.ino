#include <SPI.h>
#include "DW1000Ranging.h"
#include "DW1000Device.h"


// connection pins
const uint8_t PIN_RST = PA0; // reset pin
const uint8_t PIN_IRQ = PA1; // irq pin
const uint8_t PIN_SS  = PA4; // spi select pin
const uint8_t LED1  = PB0; // led1
const uint8_t LED2  = PB1; // led2


// active statement
unsigned long previousMillis = 0; // last time update
long interval = 10000; // interval at which to do something (milliseconds)


  

void setup() {
  

  Serial2.begin(115200);  
  
  delay(1000);
  
  //init the configuration
  DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
 
  //define the sketch as anchor. It will be great to dynamically change the type of module
  DW1000Ranging.attachNewRange(newRange);
  DW1000Ranging.attachBlinkDevice(newBlink);
  DW1000Ranging.attachInactiveDevice(inactiveDevice);
  
  //we start the module as an anchor
  DW1000Ranging.startAsAnchor("BA:02:AA:AA:AA:AA:AA:AA", DW1000.MODE_LONGDATA_RANGE_ACCURACY);

  // indicate if we are an anchor
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  
  delay(2000);
  
  long int bootime = millis();

 digitalWrite(LED1, HIGH);
}

void loop() {
  DW1000Ranging.loop();
}

void newRange() {
  // indicate TX
  digitalWrite(LED2, HIGH);

  // make UDP package
  unsigned long timestamp = millis();
  String tagID = DW1000Ranging.getDistantDevice()->getAddress();
  float tagRange = DW1000Ranging.getDistantDevice()->getRange();
  float tagPower = DW1000Ranging.getDistantDevice()->getRXPower();
    
 
  String msg =  timestamp + "," + String(anchorid) + "," + String(tagID) + "," + tagRange + "," + tagPower;

 
  Serial2.println(msg);  
  
  // indicate TX off
  digitalWrite(LED2, LOW);
 }


void newBlink(DW1000Device* device) {
}

void inactiveDevice(DW1000Device* device) {
}

