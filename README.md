# 12x8x8 LED matrix news ticker

12 8x32 LED matrix components, linked sequentially and with integrated driver boards, create a long, horizontal scrolling message display.
A NodeMCU ESP8266 12-F board drives the display, and loads the texts periodically from internet via WiFi.
An AWS Elastic Beanstalk Spring Boot application provides the input texts to be displayed. (see the 'scrapert' project on https://github.com/oudesnepelaar).

Parts:
 - NodeMCU ESP8266 12-F
 - .ino Sketch file to program the ESP8266
 - 3x MAX7219 8x32 LED-matrix with on-board driver from AZDelivery
 - 4-channel bi-directional logic level converter (3.3V to 5V and v.v.)
 - power switch
 - micro USB connection board for power delivery

Ferrie J Bank,
Amsterdam 20 September 2020

https://github.com/oudesnepelaar