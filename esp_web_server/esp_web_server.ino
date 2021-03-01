#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "wifi name";
const char* password = "wifi password";

const int ledPin = 2;

// Set up the server object
ESP8266WebServer server;

int isOn = 0;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  // connection to wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
  Serial.println();
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
  
  // configure server routes
  server.on("/", handleIndex); // use the top root path to report last sensor value
  server.on("/update", handleUpdate); // use the top root path to report last sensor value
  server.begin();
}

void loop() 
{
  server.handleClient();

  Serial.println(isOn);
  if (isOn == 1)
    digitalWrite(ledPin, HIGH);
  else
    digitalWrite(ledPin, LOW);
}

void handleIndex()
{
  server.send(200, "text/plain", String(isOn));
}

void handleUpdate()
{
  isOn = server.arg("value").toInt();
  Serial.println(isOn);
  server.send(200, "text/plain", "Updated");
}
