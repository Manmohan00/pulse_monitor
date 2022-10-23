#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <WiFiClient.h>

const char* ssid     = "Nam";
const char* password = "Nam12345";
const char pulse = D0;

int count = 0;
long int previousMillis = 0;
long int millisForBeat = 0;
const int period = 15000;
bool beat = false;

WiFiClient client;
unsigned long myChannelNumber = 1679866;
const char* myWriteAPIKey = "XFOVHFXWYHJ0O63D";

void setup() {
  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);

  pinMode(pulse, INPUT);
  
}

void loop() {
  long int millistime = millis();
  int n = digitalRead(pulse);
  
  if (n == 1) {
    if (beat == false) {
      count = count + 1;
      beat = true;
    }
  }
  else {
    beat = false;
  }

  if (millistime - previousMillis >= period) {
    previousMillis = millistime;
    Serial.print("Total Pulse - ");
    Serial.println(count);
     Serial.println("Uploading to Thingspeak server...");
    ThingSpeak.writeField(myChannelNumber, 1,count, myWriteAPIKey);
    count = 0;
  }

}
