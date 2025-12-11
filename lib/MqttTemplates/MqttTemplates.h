#pragma once
#include <stdint.h>

// Publie température sur les topics capteurs
void mqttPublishSht(float temperature);

// Publie la discovery Home Assistant
void mqttPublishDiscovery();
