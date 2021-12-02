
void httpGetConfiguration (const char* server,const int port,const char* path,const int timeout)
{
  // client.stop();

  Serial.println("\nConnessione in corso...");
  Serial.print("type: "); Serial.println("GET");
  Serial.print("host: "); Serial.println(server);
  Serial.print("port: "); Serial.println(port);
  Serial.print("path: "); Serial.println(path);
  Serial.println();

  if (client.connect(server, port))
  {
    client.print("GET "); client.print(String(path)); client.println(" HTTP/1.1");
    client.print("Host: "); client.println(server);
    client.println("Connection: close");
    client.println();

    // read entire response or timeout if server does not respond
    unsigned long elapsed = 0;
    unsigned long start = millis();
    char httpBuffer[350];
    httpBuffer[0] = NULL;

    while (elapsed < timeout)
    {
      char c;
      int i = 0;

      if (client.available())
      {
        skipResponseHeaders();
        while (client.available())
        {
          c = client.read();
          httpBuffer[i] = c;
          i++;
        }
        httpBuffer[i] = '\0';
      }

      if (httpBuffer[0] != NULL)
      {
        Serial.print("httpGetConfiguration response in: ");
        Serial.print(elapsed); Serial.println(" ms");

        // Serial.println(httpBuffer);
        setConfiguration(httpBuffer);
        
        Serial.println(configuration.id);
        Serial.println(configuration.tenant);
        Serial.println(configuration.userId);
        Serial.println(configuration.alertId);
        // Serial.println(configuration.alertUrl);
        for (int i = 0; i < (sizeof(configuration.alertStateList) / sizeof(configuration.alertStateList[0])); i++) {
          Serial.println("[" + configuration.alertStateList[i].value + "] " + configuration.alertStateList[i].url);
        }

        break;
      }
      else
      {
        elapsed = millis() - start;
      }
    }

    client.stop();

    if (httpBuffer[0] == NULL)
    {
      Serial.println("httpGetConfiguration time out ");
    }
  }
  else
  {
    Serial.println("httpGetConfiguration connection failed");
  }
}

bool skipResponseHeaders() 
{
  char endOfHeaders[] = "\r\n\r\n";

  client.setTimeout(5000);
  bool ok = client.find(endOfHeaders);

  if (!ok) {
    Serial.println("No response or invalid response!");
  }

  return !ok;
}
