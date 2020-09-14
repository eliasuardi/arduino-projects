
Configuration configuration;

Configuration *getConfiguration()
{
  return &configuration;
}

void setConfiguration(char* json)
{
  StaticJsonDocument<200> jsonDocument;

  DeserializationError err = deserializeJson(jsonDocument, json);
    
  if (err != DeserializationError::Ok)
  {
    Serial.println("parseObject() failed");
    return;
  }

  JsonObject root = jsonDocument.as<JsonObject>();
  
  configuration.id = root["id"].as<String>();
  configuration.tenant = root["tenant"].as<String>();
  configuration.userId = root["userId"].as<String>();
  configuration.alertId = root["alertId"].as<String>();
  configuration.alertUrl = root["alertUrl"].as<String>();
}
