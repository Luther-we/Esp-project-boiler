#include <Arduino.h>
#include "WifiConnect.h"
#include "WifiConfig.h"
#include "OTA.h"


void setup() {
  Serial.begin(115200);
  
  uint32_t t0 = millis();
  while (!Serial && millis() - t0 < 3000) { delay(10); }
  Serial.println("\n[BOOT] Desk #3");

  wifiSetup(WIFI_CONFIG);
  setupOTA();
}

void loop() {
  wifiLoop();

  if (wifiIsConnected()) {
    
  } 
  loopOTA();
}