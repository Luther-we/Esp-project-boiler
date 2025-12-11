#pragma once
#include <Arduino.h>

struct Sht31Config {
  int sdaPin;
  int sclPin;
  unsigned long intervalMs;
};

using Sht31Callback = void(*)(float temperature);

void sht31Setup(const Sht31Config& cfg, Sht31Callback cb);
void sht31Loop();
