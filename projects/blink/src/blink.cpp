#include "Arduino.h"

void setup() {
  Serial.begin(115200);  // Start Serial
  Serial.println("Starting up...");
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.println("LED pin configured");
}

void loop() {
  Serial.println("LED HIGH");
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(9, HIGH);
  delay(500);
  Serial.println("LED LOW");
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(9, LOW);
  delay(500);
}

