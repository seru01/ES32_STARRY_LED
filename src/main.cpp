#include <Arduino.h>

#define LED_PIN_1 21
#define LED_PIN_2 22
#define LED_PIN_3 23
#define LED_PIN_4 18
#define LED_PIN_5 5
#define LED_PIN_6 19
#define LED_PIN_7 17
#define LED_PIN_8 14
#define LED_PIN_9 4
#define LED_PIN_10 2
#define LED_PIN_11 15
#define LED_PIN_12 32
#define LED_PIN_13 33
#define LED_PIN_14 26
#define LED_PIN_15 27

const int Pins = 15;
int PinCounts[Pins];
int brightness[Pins] = {0};
const int fadeDelay = 5; // Delay between brightness increments
const int lowfadeDelay = 2;
// Function declarations
void updateBrightness(int pinIndex, int targetBrightness);
int getPin(int pinIndex);

void setup() {
  Serial.begin(9600); 
  pinMode(LED_PIN_1, OUTPUT); 
  pinMode(LED_PIN_2, OUTPUT); 
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(LED_PIN_4, OUTPUT); 
  pinMode(LED_PIN_5, OUTPUT); 
  pinMode(LED_PIN_6, OUTPUT); 
  pinMode(LED_PIN_7, OUTPUT);
  pinMode(LED_PIN_8, OUTPUT);
  pinMode(LED_PIN_9, OUTPUT); 
  pinMode(LED_PIN_10, OUTPUT); 
  pinMode(LED_PIN_11, OUTPUT);
  pinMode(LED_PIN_12, OUTPUT); 
  pinMode(LED_PIN_13, OUTPUT); 
  pinMode(LED_PIN_14, OUTPUT); 
  pinMode(LED_PIN_15, OUTPUT);
  for(int init = 0; init <256; init++){
    analogWrite(Pins,init);
  }
  delay(fadeDelay);

}

void loop() {
  // GENERATE BRIGHTNESS AND STORE IN PinCounts ARRAY
  for (int i = 0; i < Pins; ++i) {
    PinCounts[i] = random(0, 256);
  }
  // DISPLAY GENERATED BRIGHTNESS 
  Serial.println("Random Brightness values:");
  for (int i = 0; i < Pins; ++i) {
    Serial.print(PinCounts[i]);
    Serial.print(" ");
  }
  Serial.println(); 

  // SMOOTH FADING EFFECT
  for (int i = 0; i < Pins; ++i) {
    int targetBrightness = PinCounts[i];
    updateBrightness(i, targetBrightness);
  }

  delay(1000); 
}

// BRIGHTNESS INTENSITY FUNCTION
void updateBrightness(int pinIndex, int targetBrightness) {
  // Gradually adjust brightness to the target value
  int currentBrightness = brightness[pinIndex];
  // If the targetBrightness lessthan 150 then currentBrightness Goes to 0
  if (targetBrightness < 150) {
    while (currentBrightness > 0) {
      currentBrightness--;
      brightness[pinIndex] = currentBrightness;
      analogWrite(getPin(pinIndex), currentBrightness);
      delay(lowfadeDelay);
    }
  } else {
    // Otherwise, adjust brightness towards the target value
    while (currentBrightness != targetBrightness) {
      if (currentBrightness < targetBrightness) {
        currentBrightness++;
      } else {
        currentBrightness--;
      }
      brightness[pinIndex] = currentBrightness;
      analogWrite(getPin(pinIndex), currentBrightness);
      delay(fadeDelay);
    }
  }
}
// SET PINS INDEX for BRIGHTNESS ARRAY VALUES 
int getPin(int pinIndex) {
  if (pinIndex == 0)
    return LED_PIN_1;
  else if (pinIndex == 1)
    return LED_PIN_2;
  else if (pinIndex == 2)
    return LED_PIN_3;
  else if (pinIndex == 3)
    return LED_PIN_4;
  else if (pinIndex == 4)
    return LED_PIN_5;
  else if (pinIndex == 5)
    return LED_PIN_6;
  else if (pinIndex == 6)
    return LED_PIN_7;
  else if (pinIndex == 7)
    return LED_PIN_8;
  else if (pinIndex == 8)
  return LED_PIN_9;
  else if (pinIndex == 9)
    return LED_PIN_10;
  else if (pinIndex == 10)
    return LED_PIN_11;
  else if (pinIndex == 11)
    return LED_PIN_12;
  else if (pinIndex == 12)
    return LED_PIN_13;
  else if (pinIndex == 13)
    return LED_PIN_14;
  else if (pinIndex == 14)
    return LED_PIN_15;
  else
    return -1;
}
