//
// Copyright (c) 2017 RealTeam. All rights reserved.
//
// Implementazione della configurazione di arduino e metodi di gestione
//

#include <iostream>
#include "ArduinoJson-v5.10.0.h"
#include "configurator.h"

// ogni arduino ha una singola configurazione
Configuration configuration;

Configuration *getConfiguration()
{
    return &configuration;
}

void setConfiguration(string json)
{
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);
    if (root == JsonObject::invalid())
    {
        std::cout << "JSON non valido ! " << json << endl;
    }
    configuration.httpTimeout = root["httpTimeout"];
}