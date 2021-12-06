
void httpGetConfiguration (const char* server,const int port,const char* path,const int timeout)
{
  Serial.println("\nConnessione in corso...");
  Serial.print("type: "); Serial.println("GET");
  Serial.print("host: "); Serial.println(server);
  Serial.print("port: "); Serial.println(port);
  Serial.print("path: "); Serial.println(path);
  Serial.println();

  String address = String("http://") + server + String(":") + String(port) + path; 
  if (httpClient.begin(client, address))
  {
    auto httpCode = httpClient.GET(); 
    Serial.println(httpCode); //Print HTTP return code 
    String httpResponse = httpClient.getString(); 
    Serial.println(httpResponse); //Print request response payload 
    httpClient.end(); //Close connection
    Serial.println("Response:");
    Serial.println(httpResponse);
    Serial.println("closing connection");

    setConfiguration(httpResponse);
  }
  else
  {
    Serial.println("httpGetConfiguration connection failed.");
  }
}
