#include "Arduino.h"

void setup() {
  Serial.begin(115200);  // Start Serial
  Serial.println("Starting up...");
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("LED pin configured");
}

void loop() {
  Serial.println("LED HIGH");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  Serial.println("LED LOW");
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}

