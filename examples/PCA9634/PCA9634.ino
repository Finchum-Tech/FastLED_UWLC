/// @file    PCA9634.ino
/// @brief   PCA9634 wrapper layer example for adapting fast LED to the PCA9634 I2C PWM Driver
/// @example PCA9634.ino

#include <Arduino.h> //needed for conversion to cpp file
#include <PCA9634FakePin.h>
#include <FastLED.h> 
#include <PCA9634.h>

#define LED_PIN NULL

// How many leds in your strip?
#define NUM_LEDS 1

// Define the array of leds
CRGB ledArray[NUM_LEDS];

// Define PCA9634 device --> Constuctor takes in I2C address TODO: Confirm this with Avery again but I think 0x00
PCA9634 ledDriver(0x00); 

//function prototype
void updateLEDs();

void setup() { 
    // Uncomment/edit one of the following lines for your leds arrangement.
    // ## Clockless types ##
    FastLED.addLeds<WS2812, LED_PIN, GRB>(ledArray, NUM_LEDS); // dummy setup


    ledDriver.begin();
}

void loop() { 
  // Turn the LED on, then pause
  ledArray[0] = CRGB::Red;
  updateLEDs();
  delay(500);
  // Now turn the LED off, then pause
  ledArray[0] = CRGB::Black;
  updateLEDs();
  delay(500);
}



void updateLEDs()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    // Assume 3 channels per LED: R, G, B
    int baseChannel = i * 3;

    uint8_t r = ledArray[i].r;
    uint8_t g = ledArray[i].g;
    uint8_t b = ledArray[i].b;
    
    ledDriver.write3(baseChannel, r, g, b);
  }
}
