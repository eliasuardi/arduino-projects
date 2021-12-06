
Configuration configuration;

Configuration *getConfiguration()
{
  return &configuration;
}

void setConfiguration(String json)
{
  StaticJsonDocument<600> jsonDocument;

  DeserializationError err = deserializeJson(jsonDocument, json);
    
  if (err != DeserializationError::Ok)
  {
    Serial.println("parseObject() failed");
    return;
  }
  
  configuration.id = jsonDocument["id"].as<String>();
  configuration.tenant = jsonDocument["tenant"].as<String>();
  configuration.userId = jsonDocument["userId"].as<String>();
  configuration.alertId = jsonDocument["alertId"].as<String>();
  for (int i=0; i<jsonDocument["alertStateList"].size(); i++)
  {
    JsonObject alertState = jsonDocument["alertStateList"][i].as<JsonObject>();
    configuration.alertStateList[i].value = alertState["value"].as<String>();
    configuration.alertStateList[i].url = alertState["url"].as<String>();
  }
}
