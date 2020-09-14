
void controlSignal()
{
  _alert = true;
}

void postAlert()
{
  Serial.println("  ALLERTA  ");
  
  JsonObject& jsonNode = getJsonObject(_configuration);
  
  Serial.println("\n\nNUOVI PARAMETRI:");
  Serial.print("userId: "); Serial.println(jsonNode["userId"].asString());
  Serial.print("alertUrl: "); Serial.println(jsonNode["alertUrl"].asString());
}


