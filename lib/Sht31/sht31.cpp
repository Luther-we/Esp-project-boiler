#include <Wire.h>
#include <Adafruit_SHT31.h>
#include "sht31.h"

static Adafruit_SHT31 g_sht31;
static Sht31Config    g_cfg;
static Sht31Callback  g_cb = nullptr;
static unsigned long  g_lastRead = 0;

void sht31Setup(const Sht31Config& cfg, Sht31Callback cb) {
  g_cfg = cfg;
  g_cb  = cb;

  Wire.begin(g_cfg.sdaPin, g_cfg.sclPin);

  if (!g_sht31.begin(0x44)) {
    Serial.println("[SHT31] Erreur : capteur non detecte a 0x44");
  } else {
    Serial.println("[SHT31] OK");
  }
}

void sht31Loop() {
  unsigned long now = millis();
  if (now - g_lastRead < g_cfg.intervalMs) return;
  g_lastRead = now;

  float temperature = g_sht31.readTemperature();


  // TODO ce check est présent dans MqttTemplates, affiner la logic pour éviter double check

  if (isnan(temperature)) {
    Serial.println("[SHT31] Lecture invalide");
    return;
  }

  Serial.print("[SHT31] Temp: ");
  Serial.print(temperature);;
  Serial.println(" °C");

  if (g_cb) {
    g_cb(temperature);
  }
}
