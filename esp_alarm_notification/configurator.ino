
Configuration configuration;

Configuration *getConfiguration()
{
  return &configuration;
}

void setConfiguration(char* json)
{
  StaticJsonDocument<600> jsonDocument;

  DeserializationError err = deserializeJson(jsonDocument, json);
    
  if (err != DeserializationError::Ok)
  {
    Serial.println("parseObject() failed");
    return;
  }
  // serializeJson(jsonDocument, Serial);
  Serial.println();

  // JsonObject root = jsonDocument.as<JsonObject>();
  // JsonArray alertStateArray = jsonDocument["alertStateList"].to<JsonArray>();

  serializeJson(jsonDocument["alertStateList"], Serial);
  Serial.println();

  configuration.id = jsonDocument["id"].as<String>();
  configuration.tenant = jsonDocument["tenant"].as<String>();
  configuration.userId = jsonDocument["userId"].as<String>();
  configuration.alertId = jsonDocument["alertId"].as<String>();
  //configuration.alertUrl = root["alertUrl"].as<String>();
  // configuration.alertStateList = new AlertStateConfiguration[jsonDocument["alertStateList"].size()];
  Serial.print("alert state list size: "); Serial.println(jsonDocument["alertStateList"].size());
  for (int i=0; i<jsonDocument["alertStateList"].size(); i++)
  {
    JsonObject alertState = jsonDocument["alertStateList"][i].as<JsonObject>();
    configuration.alertStateList[i].value = alertState["value"].as<String>();
    configuration.alertStateList[i].url = alertState["url"].as<String>();
  }
}
