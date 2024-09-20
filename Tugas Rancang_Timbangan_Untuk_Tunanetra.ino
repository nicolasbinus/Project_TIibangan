#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "HX711.h"

// Pin definitions
static const uint8_t PIN_MP3_TX = 2;
static const uint8_t PIN_MP3_RX = 3;
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

DFRobotDFPlayerMini player;

#define I2C_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLS, LCD_ROWS);

#define DOUT 4
#define CLK 5
HX711 scale;

// Variables for calibration
float calibration_factor = -7050; // You might need to adjust this
float known_weight = 1.0; // known weight in kilograms
float weight = 0.0;

void setup() {
  Serial.begin(9600);
  softwareSerial.begin(9600);

  if (player.begin(softwareSerial)) {
    player.volume(30);
  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }

  lcd.init();
  lcd.backlight();

  scale.begin(DOUT, CLK);
  lcd.setCursor(0, 0);
  lcd.print("Taring scale...");
  scale.tare();
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Place weight:");
  lcd.setCursor(0, 1);
  lcd.print(known_weight, 1);
  lcd.print(" kg");
  delay(5000); // Wait for the user to place the known weight

  float raw_value = scale.get_units(10);
  calibration_factor = raw_value / known_weight;
  scale.set_scale(calibration_factor);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Calibration done");
  delay(2000);

  Serial.println("HX711 calibration complete");
}

void loop() {
  if (scale.is_ready()) {
    weight = scale.get_units(10); // Average over 10 readings

    if (weight < 0.0) {
      weight = 0.0;
    }

    updateLCD(weight);
    playTrack(weight);
    delay(2000);
  } else {
    Serial.println("HX711 not found.");
  }
}

void playTrack(float weight) {
  int track;


  if (weight >= 0.0 && weight < 0.06) {
    track = 13; //0.0
  } else if (weight >= 0.06 && weight < 0.16) {
    track = 14; //0.1
  } else if (weight >= 0.16 && weight < 0.26) {
    track = 15; //0.2
  } else if (weight >= 0.26 && weight < 0.36) {
    track = 16; //0.3
  } else if (weight >= 0.36 && weight < 0.46) {
    track = 17; //0.4
  } else if (weight >= 0.46 && weight < 0.56) {
    track = 18; //0.5
  } else if (weight >= 0.56 && weight < 0.66) {
    track = 19; //0.6
  } else if (weight >= 0.66 && weight < 0.76) {
    track = 20; //0.7
  } else if (weight >= 0.76 && weight < 0.86) {
    track = 21; //0.8
  } else if (weight >= 0.86 && weight < 0.96) {
    track = 22; //0.9
  } else if (weight >= 0.96 && weight < 1.06) {
    track = 23; //1.0
  } else if (weight >= 1.06 && weight < 1.16) {
    track = 24; //1.1
  } else if (weight >= 1.16 && weight < 1.26) {
    track = 25; //1.2
  } else if (weight >= 1.26 && weight < 1.36) {
    track = 26; //1.3
  } else if (weight >= 1.36 && weight < 1.46) {
    track = 27; //1.4
  } else if (weight >= 1.46 && weight < 1.56) {
    track = 28; //1.5
  } else if (weight >= 1.56 && weight < 1.66) {
    track = 29; //1.6
  } else if (weight >= 1.66 && weight < 1.76) {
    track = 30; //1.7
  } else if (weight >= 1.76 && weight < 1.86) {
    track = 31; //1.8
  } else if (weight >= 1.86 && weight < 1.96) {
    track = 32; //1.9
  } else if (weight >= 1.96 && weight < 2.06) {
    track = 33; //2.0
  } else if (weight >= 2.06 && weight < 2.16) {
    track = 34; //2.1
  } else if (weight >= 2.16 && weight < 2.26) {
    track = 35; //2.2
  } else if (weight >= 2.26 && weight < 2.36) {
    track = 36; //2.3
  } else if (weight >= 2.36 && weight < 2.46) {
    track = 37; //2.4
  } else if (weight >= 2.46 && weight < 2.56) {
    track = 38; //2.5
  } else if (weight >= 2.56 && weight < 2.66) {
    track = 39; //2.6
  } else if (weight >= 2.66 && weight < 2.76) {
    track = 40; //2.7
  } else if (weight >= 2.76 && weight < 2.86) {
    track = 41; //2.8
  } else if (weight >= 2.86 && weight < 2.96) {
    track = 42; //2.9
  } else if (weight >= 2.96 && weight < 3.06) {
    track = 43; //3.0
  } else if (weight >= 3.06 && weight < 3.16) {
    track = 44; //3.1
  } else if (weight >= 3.16 && weight < 3.26) {
    track = 45; //3.2
  } else if (weight >= 3.26 && weight < 3.36) {
    track = 46; //3.3
  } else if (weight >= 3.36 && weight < 3.46) {
    track = 47; //3.4
  } else if (weight >= 3.46 && weight < 3.56) {
    track = 48; //3.5
  } else if (weight >= 3.56 && weight < 3.66) {
    track = 49; //3.6
  } else if (weight >= 3.66 && weight < 3.76) {
    track = 50; //3.7
  } else if (weight >= 3.76 && weight < 3.86) {
    track = 51; //3.8
  } else if (weight >= 3.86 && weight < 3.96) {
    track = 1; //3.9
  } else if (weight >= 3.96 && weight < 4.06) {
    track = 2; //4.0
  } else if (weight >= 4.06 && weight < 4.16) {
    track = 3; //4.1
  } else if (weight >= 4.16 && weight < 4.26) {
    track = 4; //4.2
  } else if (weight >= 4.26 && weight < 4.36) {
    track = 5; //4.3
  } else if (weight >= 4.36 && weight < 4.46) {
    track = 6; //4.4
  } else if (weight >= 4.46 && weight < 4.56) {
    track = 7; //4.5
  } else if (weight >= 4.56 && weight < 4.66) {
    track = 8; //4.6
  } else if (weight >= 4.66 && weight < 4.76) {
    track = 9; //4.7
  } else if (weight >= 4.76 && weight < 4.86) {
    track = 10; //4.8
  } else if (weight >= 4.86 && weight < 4.96) {
    track = 11; //4.9
  } else if (weight >= 4.96 && weight < 5.06) {
    track = 12; //5.0
  } else {
    track = 13;
  }


  player.play(track);
  Serial.print("DFPlayer playing track ");
  Serial.print(track);
  Serial.print(" corresponding to weight: ");
  Serial.print(weight * 1000, 1); // Print weight in grams on serial monitor
  Serial.println(" g");
}

void updateLCD(float weight) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Weight: ");
  lcd.print(weight, 1);
  lcd.print("kg");
}
