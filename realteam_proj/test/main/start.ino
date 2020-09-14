
void setup()
{
  Serial.begin(9600);
  // se la connessione attraverso DHCP fallisce
  if (Ethernet.begin(mac) == 0)
  {
    Serial.println("DHCP fallito");
    Ethernet.begin(mac, ip);
  }
  
  Config conf(7);
  
  conf.updateConfiguration();
  lastConnectionTime = millis();
}

void loop()
{
  //post(server,8080, path, data);
  if (millis() - lastConnectionTime > postingInterval)
  {
    
    Config conf(7);
    conf.updateConfiguration();
    lastConnectionTime = millis();

    JsonObject& jsonNode = conf.getJsonObject(_configuration);
    
    Serial.println("\n\nNUOVI PARAMETRI:");
    Serial.print("userId: "); Serial.println(jsonNode["userId"].asString());
    Serial.print("alertUrl: "); Serial.println(jsonNode["alertUrl"].asString());
  }
}
