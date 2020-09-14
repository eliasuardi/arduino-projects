
class Config
{
  public:
  Config(int i)
  {
    Serial.println(i);
  }
  boolean updateConfiguration()
  {
    boolean correct = false;
    
    Comunication com(3);
    if(com.connectionServer("GET", REGISTRY_SERVER, REGISTRY_PORT, REGISTRY_PATH, 2000))
    { 
      int contentLength = com.getContentLength();
      
      if(contentLength > 0)
      {
        Serial.println("inizio a leggere!");
        free(_configuration);
        _configuration = new char[contentLength + 1];
        
        com.readResponseContent(_configuration, contentLength);
        
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
      com.disconnetti();
    }
    else
    {
      Serial.println("EXCEPTION-updateParameters: connessione fallita");
    }
  
    return correct;
  }
  
  JsonObject& getJsonObject(char data[])
  {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(data);
    if (!root.success())
    {
      Serial.println("parseObject() failed");
      return;
    }
    return root;
  }

};

