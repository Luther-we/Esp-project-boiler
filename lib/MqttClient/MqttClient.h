#pragma once
#include <Arduino.h>
#include <PubSubClient.h>

void mqttSetup();

void mqttLoop();

// Retourne true si une nouvelle connexion vient d'être établie.
bool mqttEnsureConnected();

// Accès au client pour setCallback / subscribe / autres
PubSubClient& mqttClient();
