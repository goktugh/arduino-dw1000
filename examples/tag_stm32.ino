#include <SPI.h>
#include "DW1000Ranging.h"
#include "DW1000Device.h"


// connection pins
const uint8_t PIN_RST = PA0; // reset pin  // war PB0
const uint8_t PIN_IRQ = PA1; // irq pin
const uint8_t PIN_SS = PA4; // spi select pin

const uint8_t LED1  = PB0; // led1
const uint8_t LED2  = PB1; // led2




  
void setup() {
  

  Serial2.begin(115200);
  
  // set led outputs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  
  delay(1000);
  
  //init the configuration
  DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
  //define the sketch as anchor. It will be great to dynamically change the type of module
  DW1000Ranging.attachNewRange(newRange);
  DW1000Ranging.attachNewDevice(newDevice);
  DW1000Ranging.attachInactiveDevice(inactiveDevice);
  //Enable the filter to smooth the distance
  //DW1000Ranging.useRangeFilter(true);
  
  //we start the module as a tag
  DW1000Ranging.startAsTag("AD:14:22:EA:82:60:AF:F9", DW1000.MODE_LONGDATA_RANGE_ACCURACY);

  

 }

void loop() {
  DW1000Ranging.loop();
}

void newRange() {
  // print to serial
  unsigned long timestamp = millis();
  //Serial2.print("t: "); Serial2.print(timestamp);
  //Serial2.print("from: "); Serial2.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
  //Serial2.print("\t Range: "); Serial2.print(DW1000Ranging.getDistantDevice()->getRange()); Serial2.print(" m");
  //Serial2.print("\t RX power: "); Serial2.print(DW1000Ranging.getDistantDevice()->getRXPower()); Serial2.println(" dBm");


   byte anchorID = DW1000Ranging.getDistantDevice()->getShortAddress();
    float tagRange = DW1000Ranging.getDistantDevice()->getRange();
    float tagPower = DW1000Ranging.getDistantDevice()->getRXPower();
    
   
    String msg = timestamp + "," + String(anchorID) +  "," + tagRange + "," + tagPower;
    Serial2.println(msg);
  }


void newDevice(DW1000Device* device) {
//  mySerial.print("ranging init; 1 device added ! -> ");
//  mySerial.print(" short:");
//  mySerial.println(device->getShortAddress(), HEX);
}

void inactiveDevice(DW1000Device* device) {
//  mySerial.print("delete inactive device: ");
//  mySerial.println(device->getShortAddress(), HEX);
}


