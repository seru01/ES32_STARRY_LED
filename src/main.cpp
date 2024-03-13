#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

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

//WIFI ACCESS POINT PROVISIONING
const String ssid = "STARY_LED";
const String password = "@STARY_LED098";
IPAddress staticIP(192, 168, 4, 2);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);


//PINS DECLARATION
const int Pins = 15;
int PinCounts[Pins];
int brightness[Pins] = {0};
const int fadeDelay = 25; // Delay between brightness increments

// Variable to keep track of OTA availability time
unsigned long otaStartTime;

// Function declarations
void updateBrightness(int pinIndex, int targetBrightness);
int getPin(int pinIndex);

AsyncWebServer server(80);

void setup() {
  Serial.begin(9600); 
  WiFi.mode(WIFI_AP);

  // Start the access point
  String macAddress = WiFi.softAPmacAddress();
  WiFi.softAP(ssid + "_" + macAddress, password);

  // Get the IP address of the hotspot
  WiFi.softAPConfig(staticIP, gateway, subnet);

  // Print the SSID and IP address of the hotspot to the serial monitor
  Serial.println("Access Point started");
  Serial.print("SSID: ");
  Serial.println(ssid + "_" + macAddress);
  Serial.print("IP address (Access Point Mode) : ");
  Serial.println(WiFi.softAPIP());
  // Initialize AsyncElegantOTA
  AsyncElegantOTA.begin(&server);  
  // Add handlers for OTA
  server.begin();

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

// Initialize Pin Output Limit Current
  int LED_PINS[] = {
    LED_PIN_1, LED_PIN_2, LED_PIN_3, LED_PIN_4, LED_PIN_5, 
    LED_PIN_6, LED_PIN_7, LED_PIN_8, LED_PIN_9, LED_PIN_10, 
    LED_PIN_11, LED_PIN_12, LED_PIN_13, LED_PIN_14, LED_PIN_15
  };

  // Set the initial brightness of all LED pins
  for(int i = 0; i < 15; i++) {
    Serial.println("Initializing LED");
    Serial.print("LED Pin: ");
    Serial.println(LED_PINS[i]);
    digitalWrite(LED_PINS[i], LOW);
    delay(100);
  }
  // Record the start time of OTA availability
  otaStartTime = millis();
  
}

void loop() {
  // Check if OTA time has elapsed
  if (millis() - otaStartTime >= 30 * 60 * 1000) { // 30 minutes in milliseconds
    // Stop the server and disable OTA
    server.end();
    WiFi.mode(WIFI_OFF);
  }

  // GENERATE BRIGHTNESS AND STORE IN PinCounts ARRAY
  for (int i = 0; i < Pins; ++i) {
    PinCounts[i] = random(0, 180);
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
      delay(fadeDelay);
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
  switch (pinIndex) {
    case 0: return LED_PIN_1;
    case 1: return LED_PIN_2;
    case 2: return LED_PIN_3;
    case 3: return LED_PIN_4;
    case 4: return LED_PIN_5;
    case 5: return LED_PIN_6;
    case 6: return LED_PIN_7;
    case 7: return LED_PIN_8;
    case 8: return LED_PIN_9;
    case 9: return LED_PIN_10;
    case 10: return LED_PIN_11;
    case 11: return LED_PIN_12;
    case 12: return LED_PIN_13;
    case 13: return LED_PIN_14;
    case 14: return LED_PIN_15;
    default: return -1;
  }
}
