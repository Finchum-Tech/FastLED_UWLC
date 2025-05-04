/// @file    PCA9634.ino
/// @brief   PCA9634 wrapper layer example for adapting fast LED to the PCA9634 I2C PWM Driver
/// @example PCA9634.ino

#include <Arduino.h> //needed for conversion to cpp file
#include <FastLED.h> 
#include <PCA9634.h>

#define LED_PIN NULL
#define OUTPUT_PIN 16

// How many leds in your strip?
#define NUM_LEDS 1

// Define the array of leds
CRGB ledArray[NUM_LEDS];

// Define PCA9634 device --> Constuctor takes in I2C address of d115
PCA9634 ledDriver(115); 

//function prototype
void updateLEDs();

void setup() { 
      //enable led
      pinMode(2, OUTPUT);
      digitalWrite(2, HIGH);

    // Initialize serial communication at esp8266 native baud rate of 74880
    Serial.begin(74880);
    while (!Serial) {
      ; // Wait for serial port to connect
    }
    // Print a message to the Serial Monitor
    Serial.println("Serial communication initialized.");

    // Uncomment/edit one of the following lines for your leds arrangement.
    // ## Clockless types ##
    FastLED.addLeds<WS2812, LED_PIN, GRB>(ledArray, NUM_LEDS); // dummy setup

    //Start 2wire comm with the following pins 
    Wire.begin(4, 5);

    //enable output pin
    pinMode(OUTPUT_PIN, OUTPUT);
    digitalWrite(OUTPUT_PIN, LOW);

    ledDriver.begin(0x01,0x14); //start pca control with register mode values

    Serial.println("setup loop initialized.");
    
    digitalWrite(2, LOW);
}

void loop() { 
  digitalWrite(2, !(digitalRead(2)));
  // Turn the LED on, then pause
  ledArray[0] = CRGB::Red;
  updateLEDs();
  delay(1000);
  // Now turn the LED off, then pause
  ledArray[0] = CRGB::Black;
  updateLEDs();
  delay(1000);
  Serial.println(millis());
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
