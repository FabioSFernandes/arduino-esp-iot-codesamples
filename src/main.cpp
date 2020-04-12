#include <Arduino.h>
#include "wifi/WifiManager.h"


WifiManager *wifi;

void setup() {
  Serial.begin(115200);
  Serial.println("Setup - Starting main appication path");
  // put your setup code here, to run once:
  wifi = new WifiManager();
  wifi->start();
  Serial.println("Setup - Finishing main appication path");
}

void loop() {
  // Serial.println("Loop - Starting main appication path");
  // put your main code here, to run repeatedly:
  if (wifi->getStatus()==WL_CONNECTED) { 
    
  }
  // Serial.println("Loop - Stop main appication path");
}