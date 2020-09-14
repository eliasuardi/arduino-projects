#include <ESP8266WiFi.h>

const char* ssid = "wifi name";
const char* password = "wifi password";

const char* host = "www.realteam.it";
const char* path = "/server1/api/tenants/demo_vigili2/objects";
int port = 80;

void setup()
{
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
}


void loop()
{
  WiFiClient client;

  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, port))
  {
    Serial.println("connected]");

    Serial.println("[Sending a request]");    

    client.print("GET "); client.print(String(path)); client.println(" HTTP/1.1");
    client.print("Host: "); client.println(host);
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();

    Serial.println("[Response:]");
    while (client.connected() || client.available())
    {
      if (client.available())
      {
        String line = client.readStringUntil('\n');
        Serial.println(line);
      }
    }
    
    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!]");
    client.stop();
  }
  delay(5000);
}
