#include <Arduino.h>
#include "parser.h"
#include "Adafruit_NeoPixel.h"

#define NUMPIXELS 8
#define PIN 5
#define TOUCH 2

Parser parser = Parser(0x7e);
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

long health_timer = millis();

void setup() {
  Serial.begin(115200);
  pixels.begin();
  pinMode(TOUCH, INPUT);
}

void loop() {
  parser.listen(Serial);
  if (parser.isReady()){
    uint32_t color;
    uint8_t effect;
    uint8_t time; 
    parser.getPayload(color, effect, time);
    Serial.println(color);
    pixels.fill(color);
    pixels.show();
  }
  if (digitalRead(TOUCH)) {
    uint32_t color = pixels.getPixelColor(0);
    color += 100;
    pixels.fill(color);
    pixels.show();
  }

  if (millis() - health_timer > 10000) {
    // Serial.println("Health Check!");
    health_timer = millis();
  }

}