//Checked with evive / Arduino Mega
//Compatible with SPI based TFT (user can modify TFT codes and library)
//Date: 20160623
//Developer: Dhrupal R Shah

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <Fonts/FreeMonoBoldOblique12pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>
#include "rmbs.h"
#include <Wire.h>
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
  tft.setRotation(3);
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
    tft.print("LED 1");
//LED 2 Label
    tft.setCursor(20, 35);
    tft.setTextColor(ST7735_BLACK);
    tft.setTextSize(2);
    tft.print("LED 2");
//LED 3 Label
    tft.setCursor(20, 60);
    tft.setTextColor(ST7735_BLACK);
    tft.setTextSize(2);
    tft.print("LED 3");
//LED 4 Label
    tft.setCursor(20, 85);
    tft.setTextColor(ST7735_BLACK);
    tft.setTextSize(2);
    tft.print("LED 4");
//LED 5 Label
    tft.setCursor(20, 110);
    tft.setTextColor(ST7735_BLACK);
    tft.setTextSize(2);
    tft.print("LED 5");
  
//LED 1 On/Off Button  
    tft.setCursor(100, 10);
    tft.setTextColor(ST7735_BLACK);
    tft.setTextSize(2);
if (leds == '1'){
    tft.print("On");
}
else {tft.print("Off");
}
//LED 2 On/Off Button
    tft.setCursor(100, 35);
tft.setTextColor(ST7735_BLACK);
    tft.setTextSize(2);
if (leds == '1'){
    tft.print("On");
}
else {tft.print("Off");
}
//LED 3 On/Off Button
    tft.setCursor(100, 60);
tft.setTextColor(ST7735_BLACK);
    tft.setTextSize(2);
if (leds == '1'){
    tft.print("On");
}
else {
  tft.print("Off");
}
//LED 4 On/Off Button
    tft.setCursor(100, 85);
tft.setTextColor(ST7735_BLACK);
    tft.setTextSize(2);
if (leds == '1'){
    tft.print("On");
}
else {
  tft.print("Off");
}

//LED 5 On/Off Button
    tft.setCursor(100, 110);
tft.setTextColor(ST7735_BLACK);
    tft.setTextSize(2);
if (leds == '1'){
    tft.print("On");
}
else {
  tft.print("Off");
}


}
