//
// Copyright (c) 2017 RealTeam. All rights reserved.
//
// Programma principale
//

#include <iostream>
#include "configurator.h"

int main(int argc, const char * argv[])
{
    // accedi a configurazione globale
    Configuration *config = getConfiguration();
    std::cout << "default: " << config->registryId << " " << config->httpTimeout << endl;

    // aggiorna la configurazione globale
    string json = "{\"httpTimeout\":8888[}";
    setConfiguration(json);
    std::cout << "aggiornata: " << config->registryId << " " << config->httpTimeout << endl;

    std::cout << "Bye, World!" << endl;
    return 0;
}
