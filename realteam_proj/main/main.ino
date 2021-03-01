#include <ArduinoJson.h>
#include <Ethernet.h>
#include <ESP8266WiFi.h>
#include <SPI.h>

const char REGISTRY_ID [] = "vdftreviglio_vigili";
const char REGISTRY_SERVER [] = "192.168.0.102";
const int REGISTRY_PORT = 8080;
const char REGISTRY_PATH [] = " ";

/** specific for ethernet shield **/
EthernetClient client;
IPAddress ip(192, 168, 0, 250);
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

/** specific for esp8266 module **/
char * ssid = "xxxxx";
char * password = "yyyyy";


unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 2L * 1000L;

JsonObject *param();

struct Configuration
{
  String id;
  String tenant;
  String userId;
  String alertId;
  String alertUrl;
};

enum ModeType
{
  ethernet,
  esp
};

const ModeType mode = esp;

void setup()
{
  
  Serial.begin(9600);
  Serial.println();

  switch (mode)
  {
    case eth:
    
      // se la connessione attraverso DHCP fallisce
      if (Ethernet.begin(mac) == 0)
      {
        Serial.println("DHCP fallito");
        Ethernet.begin(mac, ip);
      }
      
      break;
      
    case esp:
    
      WiFi.begin(ssid, password);
      
      Serial.print("Connecting");
      while (WiFi.status() != WL_CONNECTED)
      {
        delay(500);
        Serial.print(".");
      }
      Serial.println();
      
      break;
  }

  delay(2000);
}

void loop()
{

  if (client.available())
  {
    char c = client.read();
    Serial.write(c);
  }

  if (millis() - lastConnectionTime > postingInterval)
  {
    httpGetConfiguration(REGISTRY_SERVER, REGISTRY_PORT, REGISTRY_PATH, 5000);
    lastConnectionTime = millis();
  }

}
