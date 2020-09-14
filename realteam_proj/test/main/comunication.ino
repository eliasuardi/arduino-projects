
class Comunication
{
  EthernetClient client;

  public:
  Comunication (int i)
  {
    Serial.println(i);
  }
  boolean connectionServer(char* tipe, char* host, int port, char* path, int waitResponse)
  {
    char httpBuffer[200];
    
    client.stop();
    
    Serial.println("\nConnessione in corso...");
    Serial.print("tipe: ");Serial.println(tipe);
    Serial.print("host: ");Serial.println(host);
    Serial.print("port: ");Serial.println(port);
    Serial.print("path: ");Serial.print(path);Serial.println(REGISTRY_ID);
    Serial.println();
     
    if (client.connect(host, port))
    {
      sprintf(httpBuffer, "%s %s%s HTTP/1.1", tipe, path, REGISTRY_ID);
      Serial.println(httpBuffer);
      client.println(httpBuffer);
       
      sprintf(httpBuffer, "Host: %s:%d", host, port);
      Serial.println(httpBuffer);
      client.println(httpBuffer);
  
      Serial.println("User-Agent: arduino-ethernet");
      client.println("User-Agent: arduino-ethernet");
      
      Serial.println("Connection: close");
      client.println("Connection: close");
      
      if(tipe == "GET")
      {
        // linea vuota tra headers HTTP e Body
        Serial.println();
        client.println();
    
        Serial.println("wait response...");
        delay(waitResponse);
      }
      
      return true;
    }
    else
    {
      return false;
    }
  }

  void readResponseContent(char*response, int contentLength)
  {
    char c;
    int index =0;
    if(!client.available())
    {
      Serial.println("EXCEPITON-readResponseContent: client not available");
      exit;
    }
    
    while(client.available())
    {
      c = client.read();
      Serial.print(c);
      if( c == '{' || index > 0 )
      {
        if(index < contentLength)
        {
          response[index] = c;
          index++;
        }
        else
        {
          Serial.println("EXCEPITON-readResponseContent: dimensione contenuto superiore a contentLength");
          exit;
        }
      }
    }
    
    response[index] = '\0';
  }
  
  void writeContent(char*data, int waitResponse)
  {
    char httpBuffer[100];
    
    Serial.println("Content-Type: application/json; charset=utf-8");
    client.println("Content-Type: application/json; charset=utf-8");
     
    sprintf(httpBuffer, "Content-Length: %u", strlen(data));
    Serial.println(httpBuffer);
    client.println(httpBuffer);
     
    // linea vuota tra headers HTTP e Body
    Serial.println();
    client.println();
     
    sprintf(httpBuffer, "%s", data);
    Serial.println(httpBuffer);
    client.print(httpBuffer); 
  
    delay(waitResponse);
  }

  int getContentLength()
  { 
    char c;
    char httpBuffer[100];
    int index = 0;
  
    if(!client.available())
    {
      Serial.println("EXCEPITON-getContentLength: client not available");
      exit;
    }
    
    while(client.available() && index < 100)
    {
      c = client.read();
      Serial.print(c);
      httpBuffer[index] = c;
      if(c == '\n')
      {
        httpBuffer[index+1] = '\0';
        if(isContain(httpBuffer, "Content-Length:"))
        {
           return getValueLength(httpBuffer);
        }
        index = 0;
      }
      index++;
    }
    return -1;
  }

  void disconnetti()
  {
    // se il server ha chiusto la connessione
    if (!client.connected())
    {
      // stop del client
      client.stop();
      Serial.println("\nINFO-updateParameters: client stop");
    }
  }
};

