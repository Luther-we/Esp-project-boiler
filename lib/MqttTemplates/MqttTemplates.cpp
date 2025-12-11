#include "MqttTemplates.h"
#include <ArduinoJson.h>
#include "MqttClient.h"
#include "ProjectConfig.h"
#include "Topics.h"


void mqttPublishSht(float temperature) {
  if (isnan(temperature)) {
    Serial.println("[SHT] Valeurs invalides, publish annule");
    return;
  }

  Serial.print("[SHT] T = ");
  Serial.print(temperature);
  Serial.println(" °C");

  char buf[16];

  dtostrf(temperature, 2, 2, buf);
  mqttClient().publish(Topics::tempState().c_str(), buf, true);

}

void mqttPublishDiscovery() {
  
  // Temp sensor
  {
    JsonDocument doc;

    doc["name"]    = "Température";
    doc["uniq_id"] = String(ProjectConfig::deviceName()) + "_temperature";
    doc["obj_id"]  = String(ProjectConfig::deviceName()) + "_temperature";

    doc["stat_t"]  = Topics::tempState();
    doc["unit_of_measurement"] = "°C";
    doc["device_class"]        = "temperature";
    doc["state_class"]         = "measurement";

    doc["avty_t"]       = Topics::availability();
    doc["pl_avail"]     = "online";
    doc["pl_not_avail"] = "offline";

    JsonObject dev = doc["device"].to<JsonObject>();
    dev["name"] = ProjectConfig::friendlyName();
    dev["mf"]   = "DIY";
    dev["mdl"]  = "ESP32 C3 - Template Device";
    JsonArray ids = dev["identifiers"].to<JsonArray>();
    ids.add(ProjectConfig::deviceName());

    char buf[512];
    size_t n = serializeJson(doc, buf, sizeof(buf));
    mqttClient().publish(Topics::tempDiscovery().c_str(), (const uint8_t*)buf, (unsigned int)n, true);
    Serial.printf("[DISCOVERY] TEMP %s\n", buf);
  }

}
