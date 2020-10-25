#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>
 
const char* ssid = "ZiggoA72811A";
const char* password = "E3asv6vauwdk";

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CLK_PIN   1
#define CS_PIN    2
#define DATA_PIN  3


MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
MD_MAX72XX *MAX = P.getGraphicObject();

uint8_t scrollSpeed = 60;
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;
uint16_t scrollPause = 0;

int const bufferSize = 8192;
char myBuffer[bufferSize] = {"Initialization imminent!"};
String payload;
boolean bufferDirty = false;

int newsRefreshDelaySecs = 30;
int newsRefreshCounter = -1;
 
void setup () {

  displayInit();

  Serial.begin(115200);
  while (!Serial) delay(200);
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
   
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connection established!");
}

void displayInit() {

  P.begin();
  P.displayClear();
  P.displaySuspend(false);
  P.setIntensity(0);

 // P.displayScroll(myBuffer, scrollAlign, scrollEffect, scrollSpeed);
  
 // while (!P.displayAnimate()) {yield();}
}


void loop() {
  
  newsRefreshCounter++;
  evaluateCounter();
  readNews();
  
  if (bufferDirty) {

    bufferDirty = false;
    
    payload.toCharArray(myBuffer, bufferSize);
  //  P.displayReset();
    P.displayScroll(myBuffer, scrollAlign, scrollEffect, scrollSpeed);
    
  }

  while (!P.displayAnimate()) {yield();}
}

void evaluateCounter() {

  if (newsRefreshCounter >= newsRefreshDelaySecs) newsRefreshCounter = 0;  
}

void readNews() {

  Serial.print("counter ");
  Serial.println(newsRefreshCounter);
  
  if (newsRefreshCounter > 0) return;

  if (WiFi.status() == WL_CONNECTED) {
     
    HTTPClient http;
     
    http.begin("http://scrapert-env-1.eba-czz2mtaz.us-east-2.elasticbeanstalk.com/mix");
    int httpCode = http.GET();
     
    if (httpCode > 0) {
       
      payload = http.getString();
      bufferDirty = true;
      
      Serial.println(httpCode);
      Serial.println(payload);
    }
     
    http.end();
  }
}
