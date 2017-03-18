#include "ESP8266WiFi.h"

WiFiClient client;
IPAddress hub(192, 168, 11, 34);  //IP Address of Lightify Gateway

byte ONOFF[] = {0x0f, 0x00, 0x00, 0x32, 0x01, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x02};
byte BRIGHTNESS_ALL[] = {0x11, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x03, 0x00};

int rotaryLastVal, rotaryVal;
bool switchState;

void setup() {
  Serial.begin(115200);

  //Wifi Settings
  const char* ssid     = "";
  const char* password = "";
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    delay(10);
  }
  client.setNoDelay(true);

  //Debug Serial
  Serial.println("Connected");
  Serial.println(WiFi.localIP());

  //Input Setup
  pinMode(A0, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  switchState = digitalRead(4);
  rotaryLastVal = analogRead(A0);

}

void loop() {
  //On-Off function
  if (digitalRead(4) != switchState) {
    onOff();
    delay(100);
  }

  //Dimmer function
  rotaryVal = analogRead(A0);

  if ((rotaryVal < (rotaryLastVal - 8) || rotaryVal > (rotaryLastVal + 8)) && switchState == 1 ) {
    delay(150);
    rotaryVal = analogRead(A0);

    brightness(rotaryVal);
    rotaryLastVal = rotaryVal;
  }
  delay(50);
}

void onOff() {
  Serial.println("ONOFF Called");
  ONOFF[16] = ((ONOFF[16] == 0x00) ? 0x01 : 0x00);
  client.connect(hub, 4000);
  client.write((uint8_t*)ONOFF, sizeof(ONOFF));
  client.stop();
  switchState = !switchState;
}

void brightness(int level) {
  level = map(level, 0, 1007, 0, 100);
  client.connect(hub, 4000);
  Serial.print("Brightness called");
  Serial.println(level);
  BRIGHTNESS_ALL[16] = level;
  client.write((const uint8_t*)BRIGHTNESS_ALL, sizeof(BRIGHTNESS_ALL));
  delay(100);
  client.stop();
}

void reboot() {
  if (millis() > 86400000) {
    ESP.reset();
  }
}

void webinterface() {
}

