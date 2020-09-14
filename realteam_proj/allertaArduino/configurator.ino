
boolean updateConfiguration()
{
  boolean correct = false;

  if(connectionServer("GET", REGISTRY_SERVER, REGISTRY_PORT, REGISTRY_PATH, 1000))
  { 
    int contentLength = getContentLength();
    
    if(contentLength > 0)
    {
      free(_configuration);
      _configuration = new char[contentLength + 1];
      readResponseContent(_configuration, contentLength);
      
      if(_configuration != NULL)
      {
        correct = true;
      }
      else
      {
        Serial.println("EXCEPTION-updateParameters: jsonResponse NULL");
      }
    }
    else
    {
      Serial.println("EXCEPTION-updateParameters: contentLength non trovato");
    }

    // se il server ha chiusto la connessione
    if (!client.connected())
    {
      // stop del client
      client.stop();
      Serial.println("\nINFO-updateParameters: client stop");
    }
  }
  else
  {
    Serial.println("EXCEPTION-updateParameters: connessione fallita");
  }

  return correct;
}

void getJsonObject(char data[])
{
  StaticJsonBuffer<200> jsonBuffer;
  
  ROOT = jsonBuffer.parseObject(data);
  
  if (!root.success())
  {
    Serial.println("parseObject() failed");
    return;
  }
  
}

