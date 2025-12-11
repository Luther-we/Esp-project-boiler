#pragma once
#include <Arduino.h>


namespace ProjectProfile {
  inline constexpr char DEVICE_NAME[]   = "deviceName";
  inline constexpr char FRIENDLY_NAME[] = "Device Name";
  
  inline constexpr uint8_t STATIC_IP_LAST_OCTET = 50;

  inline constexpr char MQTT_BASE_PREFIX[] = "deviceName/";
}

