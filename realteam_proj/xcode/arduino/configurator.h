//
// Copyright (c) 2017 RealTeam. All rights reserved.
//
// Definizione della configurazione di arduino e metodi di gestione
//

#ifndef __arduino__configurator__
#define __arduino__configurator__

#include <stdio.h>
#include <string>

using namespace std;

// definizione della configurazione
struct Configuration
{
    // id di arduino nel registro RealTeam
    string registryId = "vdftreviglio_vigili";

    // timeout per le richieste HTTP
    long httpTimeout = 5000;
};

// prototipi
Configuration *getConfiguration();
void          setConfiguration(string json);

#endif /* defined(__arduino__configurator__) */
