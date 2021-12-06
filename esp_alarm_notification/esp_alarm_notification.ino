#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <SPI.h>

const char* ssid = "";
const char* password = "";
const int buttonPin = 2;    // the number of the pushbutton pin

/** HTTP REQUEST VARIABLES **/

const char REGISTRY_ID [] = "demo_alert";
// const char* REGISTRY_SERVER = "www.realteam.it";
const char* REGISTRY_SERVER = "192.168.1.7";
const int REGISTRY_PORT = 8080;
const char* REGISTRY_PATH = "/server1/api/configuration/arduino/demo_alert";

WiFiClient client;
HTTPClient httpClient;

unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 2L * 1000L;

/** END HTTP REQUEST VARIABLES **/

/** CONFIGURATION **/

JsonObject *param();

struct AlertStateConfiguration
{
  String value;
  String url;
};

struct Configuration
{
  String id;
  String tenant;
  String userId;
  String alertId;
  AlertStateConfiguration alertStateList[2];
};

/** END CONFIGURATION **/


int buttonPressed;
int buttonState;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup()
{
  pinMode(buttonPin, INPUT);
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(ssid, password);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  httpGetConfiguration(REGISTRY_SERVER, REGISTRY_PORT, REGISTRY_PATH, 5000);
}

void loop() 
{
  // if (client.available())
  // {
  //   char c = client.read();
  //   Serial.write(c);
  // }

  // if (millis() - lastConnectionTime > postingInterval)
  // {
  //   lastConnectionTime = millis();
  // }


  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonPressed) {
      buttonPressed = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonPressed == HIGH) {
        buttonState = !buttonState;
        httpSendObjectEvent(buttonState);
        Serial.println((buttonState == HIGH) ? "HIGH" : "LOW");
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
