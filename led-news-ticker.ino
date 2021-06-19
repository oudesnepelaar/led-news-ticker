#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include <SPI.h>
 
const char* ssid = "ZiggoA72811A";
const char* password = "E3asv6vauwdk";

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 8

#define CLK_PIN   D5
#define CS_PIN    D8
#define DATA_PIN  D7

MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
MD_MAX72XX *MAX = P.getGraphicObject();

uint8_t scrollSpeed = 35;
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;

int const bufferSize = 8192;
char myBuffer[bufferSize] = {"Welcome to the News Ticker :-) by Ferrie J Bank (c) 2020"};
String payload;
boolean bufferDirty = false;

unsigned long lastReadTime = 0;
unsigned long readTimeDelay = 600000; // refresh news every 10 minutes
 
void setup () {

  displayInit();
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
   
    delay(500);
  }
}

void displayInit() {

  P.begin();
  P.displayClear();
  P.displaySuspend(false);
  P.setIntensity(0);

  P.displayScroll(myBuffer, scrollAlign, scrollEffect, scrollSpeed);
  
  while (!P.displayAnimate()) {yield();}
}


void loop() {
  
  readNews();
  
  if (bufferDirty) {

    bufferDirty = false;

    MAX->clear();
    payload.toCharArray(myBuffer, bufferSize);
    P.displayReset();
  }

  if (P.displayAnimate()) {
    P.displayReset();
  }
}

void readNews() {

  unsigned long diff = millis() - lastReadTime;
  if ((lastReadTime > 0) && diff < readTimeDelay) return;
  
  lastReadTime = millis();

  if (WiFi.status() == WL_CONNECTED) {
     
    HTTPClient http;
     
    http.begin("http://scrapert-env-1.eba-czz2mtaz.us-east-2.elasticbeanstalk.com/mix");
    int httpCode = http.GET();
     
    if (httpCode > 0) {
       
      payload = http.getString();
      bufferDirty = true;
    }
     
    http.end();
  }
}
