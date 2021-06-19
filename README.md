# 12x8x8 LED matrix news ticker

12 8x32 LED matrix components, linked sequentially and with integrated driver boards, create a long, horizontal scrolling message display.
A NodeMCU ESP8266 12-F board drives the display, and loads the texts periodically from internet via WiFi.
An AWS Elastic Beanstalk Spring Boot application provides the input texts to be displayed. (see the 'scrapert' project on https://github.com/oudesnepelaar).

Parts:
 - NodeMCU ESP8266 12-F
 - .ino Sketch file to program the ESP8266
 - 3x MAX7219 8x32 LED-matrix with on-board driver from AZDelivery
 - power switch
 - micro USB connection board for power delivery
 - micro USB power supply (Power Delivery enabled, 3A)

Even though the ESP8266 uses 3.3V logic level, the MAX device is still able to see the 3.3V as logical '1'.
So there is no logc level converter necessary to make the connection between ESP8266 and the MAX.

To use the MD Parola / MD MAX72XX Arduino IDE libraries, please be aware that these use the SPI pins of
the dev board (SS, SCLK, MISO, MOSI) and can only be connected using these very specific pins(!).
It can appear as if things are working correctly while they late ron stop functioning, when you use the wrong
(arbitrary) GPIO pins. Refer to the pin-out diagram of the dev board to see which pins are SPI capable.


Ferrie J Bank,
Amsterdam 25 October 2020

https://github.com/oudesnepelaar
