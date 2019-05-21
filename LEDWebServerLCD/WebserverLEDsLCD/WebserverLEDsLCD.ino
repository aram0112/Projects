#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <Fonts/FreeMonoBoldOblique12pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>
#include "rmbs.h"
#include <Wire.h>

char yLED;
char bLED;
char wLED;
char rLED;
char gLED;

// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     10
#define TFT_RST    8  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     9

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);


void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.fillScreen(ST7735_WHITE);

    } // end pixel

void loop() {
  Wire.requestFrom(8, 1);    // request 6 bytes from slave device #8

    char leds = Wire.read();// receive a byte as character         // print the character

    Serial.print(leds);
           // join i2c bus (address optional for master)
    // start serial for output

//LED 1 Label  
    tft.setCursor(20, 10);
    tft.setTextColor(ST7735_BLACK);
    tft.setTextSize(2);
    tft.print("Yellow");
//LED 2 Label
    tft.setCursor(20, 35);
    tft.setTextColor(ST7735_BLACK);
    tft.setTextSize(2);
    tft.print("Blue");
//LED 3 Label
    tft.setCursor(20, 60);
    tft.setTextColor(ST7735_BLACK);
    tft.setTextSize(2);
    tft.print("White");
//LED 4 Label
    tft.setCursor(20, 85);
    tft.setTextColor(ST7735_BLACK);
    tft.setTextSize(2);
    tft.print("Red");
//LED 5 Label
    tft.setCursor(20, 110);
    tft.setTextColor(ST7735_BLACK);
    tft.setTextSize(2);
    tft.print("Green");
  
//LED 1 On/Off Button  
    tft.setCursor(100, 10);
    tft.setTextColor(ST7735_BLACK);
    tft.setTextSize(2);
if (leds == '2') {
    tft.fillRect(100,10,40,20, ST7735_WHITE);
    tft.print("On"); 
}
else if (leds == '3'){
  tft.fillRect(100,10,40,20, ST7735_WHITE);
  tft.print("Off");
}
//LED 2 On/Off Button
    tft.setCursor(100, 35);
tft.setTextColor(ST7735_BLACK);
    tft.setTextSize(2);
if (leds == '6'){
    tft.fillRect(100,35,40,20, ST7735_WHITE);
    tft.print("On");
}
else if (leds == '7') {
  tft.fillRect(100,35,40,20, ST7735_WHITE);
  tft.print("Off");
}
//LED 3 On/Off Button
    tft.setCursor(100, 60);
tft.setTextColor(ST7735_BLACK);
    tft.setTextSize(2);
if (leds == '8'){
    tft.fillRect(100,60,40,20, ST7735_WHITE);
    tft.print("On");
}
else if (leds == '9') {
  tft.fillRect(100,60,40,20, ST7735_WHITE);
  tft.print("Off");
}
//LED 4 On/Off Button
    tft.setCursor(100, 85);
tft.setTextColor(ST7735_BLACK);
    tft.setTextSize(2);
if (leds == '0'){
    tft.fillRect(100,85,40,20, ST7735_WHITE);
    tft.print("On");
}
else if(leds == '1') {
  tft.fillRect(100,85,40,20, ST7735_WHITE);
  tft.print("Off");
}

//LED 5 On/Off Button
    tft.setCursor(100, 110);
tft.setTextColor(ST7735_BLACK);
    tft.setTextSize(2);
if (leds == '4'){
    tft.fillRect(100,110,40,20, ST7735_WHITE);
    tft.print("On");
}
else if (leds == '5'){
  tft.fillRect(100,110,40,20, ST7735_WHITE);
  tft.print("Off");
}



}
