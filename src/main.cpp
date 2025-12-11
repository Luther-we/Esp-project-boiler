#include <Arduino.h>

#include "WifiConnect.h"
#include "OTA.h"
#include "MqttClient.h"
#include "MqttTemplates.h"
#include "sht31.h"

#include "ProjectProfile.h"
#include "ProjectConfig.h"
#include "SensorProfile.h"
#include "Topics.h"




void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String t(topic);
  String msg;
  msg.reserve(length + 1);
  for (unsigned int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }


  Serial.printf("[MQTT] Message recu sur le topic %s: ", topic);
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void onConnectPublish() {
  mqttPublishDiscovery();
}

void onSht31Measurement(float temperature) {
  mqttPublishSht(temperature);
}

void setup() {
  Serial.begin(115200);
  uint32_t t0 = millis();
  while (!Serial && millis() - t0 < 3000) { delay(10); }
  Serial.printf("\n[BOOT] %s starting...\n", ProjectConfig::deviceName());

  // TODO : placer dans config
  WifiConfig wifiCfg {
    .ssid     = ProjectConfig::wifiSsid(),
    .password = ProjectConfig::wifiPass(),
    .localIP  = ProjectConfig::wifiLocalIP(),
    .gateway  = ProjectConfig::wifiGateway(),
    .subnet   = ProjectConfig::wifiSubnet(),
    .dns1     = ProjectConfig::wifiDns1(),
    .dns2     = ProjectConfig::wifiDns2(),
    .hostname = ProjectConfig::wifiHostname()
  };

  wifiSetup(wifiCfg);

  mqttSetup();
  mqttClient().setCallback(mqttCallback);

    Sht31Config cfg {
    .sdaPin     = SensorProfile::I2C_SDA,
    .sclPin     = SensorProfile::I2C_SCL,
    .intervalMs = SensorProfile::SHT31_INTERVAL_MS
  };
  sht31Setup(cfg, onSht31Measurement);

  setupOTA();
}

void loop() {
  wifiLoop();

  if (wifiIsConnected()) {
    bool justConnected = mqttEnsureConnected();
    if (justConnected) {
      onConnectPublish();
  } }

  sht31Loop();
  mqttLoop();
  loopOTA();
}