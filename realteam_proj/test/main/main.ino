#include <ArduinoJson.h>
#include <Ethernet.h>
#include <SPI.h>

const char REGISTRY_ID [] = "vdftreviglio_vigili";
const char REGISTRY_SERVER [] = "192.168.0.102";
const int REGISTRY_PORT = 8080;
const char REGISTRY_PATH [] = "/server1/api/configuration/arduino/";

IPAddress ip(192, 168, 0, 250);
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 10L * 1000L;

char* _configuration;

