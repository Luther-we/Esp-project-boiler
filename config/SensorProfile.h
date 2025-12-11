#pragma once
#include <Arduino.h>

namespace SensorProfile {
  // SHT31
  inline constexpr int I2C_SDA = 8;
  inline constexpr int I2C_SCL = 9;

  inline constexpr unsigned long SHT31_INTERVAL_MS = 5000;
}