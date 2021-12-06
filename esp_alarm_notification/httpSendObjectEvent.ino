void httpSendObjectEvent(int objectState)
{
  Configuration* config = getConfiguration();
  String eventPath = "";
  const int alertStateCount = sizeof(config->alertStateList) / sizeof(config->alertStateList[0]);

  for (int i=0; i < alertStateCount; i++)
  {
    AlertStateConfiguration alertState = config->alertStateList[i];
    if (alertState.value == String(objectState))
    {
      eventPath = alertState.url;
      break;
    }
  }

  if (eventPath != "")
  {
    eventPath.replace("host", String(REGISTRY_SERVER));
    eventPath.replace("port", String(REGISTRY_PORT));
    eventPath.replace("server", "server1");
    
    Serial.println("\nConnessione in corso...");
    Serial.print("type: "); Serial.println("GET");
    Serial.print("host: "); Serial.println(REGISTRY_SERVER);
    Serial.print("port: "); Serial.println(REGISTRY_PORT);
    Serial.print("path: "); Serial.println(eventPath);
    Serial.println();
  
//    String address = String("http://") + REGISTRY_SERVER + String(":") + String(REGISTRY_PORT) + eventPath; 
    if (httpClient.begin(client, eventPath))
    {
      auto httpCode = httpClient.GET(); 
      Serial.println(httpCode); //Print HTTP return code 
      httpClient.end(); //Close connection
      Serial.println("closing connection");
    }
    else
    {
      Serial.println("httpPostObjectEvent connection failed.");
    }
  }
  else
  {
    Serial.println("empty event path");
  }
}
