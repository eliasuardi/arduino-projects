void httpPostObjectEvent(int objectState)
{
  const char* path = (objectState == HIGH) 
                              ? "/server1/api/tenants/demo_alert/objects/arduino/events/OpenDoor"
                              : "/server1/api/tenants/demo_alert/objects/arduino/events/CloseDoor";
  const char* server = "192.168.1.7";
  const char* userInfo = "{\"id\":39,\"userId\":\"Arduino\",\"password\":null,\"email\":\"\",\"phone\":null,\"telegramId\":null,\"objectId\":\"arduino\",\"roles\":[\"Admin\"],\"notifyMethods\":[\"\"],\"status\":null,\"maxDashboardConnections\":0,\"userIdSet\":null}";
  const int port = 8080;

  Serial.println("\nConnessione in corso...");
  Serial.print("type: "); Serial.println("POST");
  Serial.print("host: "); Serial.println(server);
  Serial.print("port: "); Serial.println(port);
  Serial.print("path: "); Serial.println(path);
  Serial.println(userInfo);
  Serial.println();

  if (client.connect(server, port))
  {
    client.print("POST "); client.print(String(path)); client.println(" HTTP/1.1");
    client.print("Host: "); client.println(server);
    client.println("Content-Type: application/json");
    client.println("Connection: close");
    // client.println();
    client.println(userInfo);
    client.println();
    client.stop();
  }
  else
  {
    Serial.println("httpPostObjectEvent connection failed");
  }
}