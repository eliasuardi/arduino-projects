#include <ArduinoJson.h>
#include <Ethernet.h>
#include <SPI.h>

const char REGISTRY_ID [] = "vdftreviglio_vigili";
const char REGISTRY_SERVER [] = "192.168.0.102";
const int REGISTRY_PORT = 8080;
const char REGISTRY_PATH [] = "/server1/api/configuration/arduino/";
const int INTERRUPT_PIN = 2;

EthernetClient client;
IPAddress ip(192, 168, 0, 250);
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 10L * 1000L;

char* _configuration;
boolean _alert = false;

void setup()
{
  Serial.begin(9600);
  // se la connessione attraverso DHCP fallisce
  if (Ethernet.begin(mac) == 0)
  {
    Serial.println("DHCP fallito");
    Ethernet.begin(mac, ip);
  }
  
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), controlSignal, CHANGE);

  updateConfiguration();
  lastConnectionTime = millis();
}


void loop()
{
  if(_alert)
  {
    postAlert();
    _alert = false;
  }
  
  if (millis() - lastConnectionTime > postingInterval)
  {
    updateConfiguration();
    lastConnectionTime = millis();

    /*JsonObject& jsonNode = getJsonObject(_configuration);
    
    Serial.println("\n\nNUOVI PARAMETRI:");
    Serial.print("userId: "); Serial.println(jsonNode["userId"].asString());
    Serial.print("alertUrl: "); Serial.println(jsonNode["alertUrl"].asString());*/
  }
}


