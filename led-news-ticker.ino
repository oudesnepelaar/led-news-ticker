#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>
 
const char* ssid = "-";
const char* password = "-";

#define HARDWARE_TYPE MD_MAX72XX::ICSTATION_HW
#define MAX_DEVICES 4

#define CLK_PIN   1
#define CS_PIN    2
#define DATA_PIN  3


MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
MD_MAX72XX *MAX = P.getGraphicObject();
 
void setup () {

  displayInit();
  showText("Connecting..");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
   
    delay(500);
    Serial.print(".");
  }

  showText("OK");
  showText("Connection established!");
  
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
     
    HTTPClient http;
     
    http.begin("http://scrapert-env-1.eba-czz2mtaz.us-east-2.elasticbeanstalk.com/mix");
    int httpCode = http.GET();
     
    if (httpCode > 0) {
       
      String payload = http.getString();
      showText(payload);
    }
     
    http.end();
  }
}

void displayInit() {

  P.begin();
  P.setSpeed(100);
  P.setPause(2000);
  P.setIntensity(0);
  P.setTextEffect(PA_SCROLL_LEFT, PA_SCROLL_LEFT);

  MAX->clear();
}

void showText(String input) {

  char text[2048];
  input.toCharArray(text, 2048);

  MAX->clear();

  P.setTextBuffer(text);
  P.displayReset();

  while (!P.displayAnimate()){;};
}


void loop() {
  
}
