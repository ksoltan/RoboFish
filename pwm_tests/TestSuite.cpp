#include <Arduino.h>
#include "TestSuite.h"

TestSuite::TestSuite(int leftPin, int rightPin, bool isPwmTest = false) {
  pinMode(LED, OUTPUT);
  LeftPin = leftPin;
  RightPin = rightPin;
  lastUpdate = millis();
  isPwm = isPwmTest;
  activeTest = SIMPLE_FLAP; // All parameters are set already to default values. No need to call set.
}

void TestSuite::SimpleFlapSet(int duty, int deadZone, float frequency, bool isPwmTest) {
  activeTest = SIMPLE_FLAP;
  currDuty = duty;
  currDeadZone = deadZone;
  isPwm = isPwmTest;
  currFlapNum = 1;
  SetPeriod(frequency);
  Serial.println("Set Simple Flap.");
}

void TestSuite::LeftOnlySet(int duty, bool isPwmTest = true){
  // Flap once to the left side. Meant to test the pwm signal.
  activeTest = LEFT_ONLY;
  currDuty = duty;
  currDir = LEFT;
  currDeadZone = 0;
  isPwm = isPwmTest;
  Serial.println("Set Left Only.");
}

void TestSuite::Update() {
  switch (activeTest) {
    case LEFT_ONLY:
      LeftOnlyUpdate();
      break;
    default:
      break;
  }
  Flap();
}

void TestSuite::LeftOnlyUpdate(){
  // Trick the program into thinking it has switched direction already, and keep it going left.
  lastUpdate = millis();
  currDir = LEFT;
}

void TestSuite::SetPeriod(float frequency = 0.5) {
  period = (int)(1 / frequency * 1000); // convert to ms.
}

void TestSuite::Flap() {
  UpdateFlapDir();
  UpdatePins();
}

void TestSuite::UpdateFlapDir() {
  // Update direction only if half a period has passed.
  if (millis() - lastUpdate >= period / 2) {
    // currDir = 1 - currDir;
    if (currDir == RIGHT) {
      currDir = LEFT;
    } else {
      currDir = RIGHT;
    }
    lastUpdate = millis();
    currFlapNum++;
    Serial.println("Flap.");
  }
}

void TestSuite::UpdatePins() {
  if (millis() - lastUpdate <= period / 2 * (100 - currDeadZone) / 100) {
    int pwm = isPwm ? (int)(255 * currDuty / 100) : 0; // calculate pwm if needed
    if (currDir == RIGHT) {
      isPwm ? analogWrite(RightPin, pwm) : digitalWrite(RightPin, HIGH); // Set right pin high
      isPwm ? analogWrite(LeftPin, 0) : digitalWrite(LeftPin, LOW); // Set left pin low
      digitalWrite(LED, HIGH);
    } else {
      isPwm ? analogWrite(RightPin, 0) : digitalWrite(RightPin, LOW); // Set right pin low
      isPwm ? analogWrite(LeftPin, pwm) : digitalWrite(LeftPin, HIGH); // Set left pin high
      digitalWrite(LED, LOW);
    }
  } else{
    // No actuation at this point. Set both pins to 0.
    digitalWrite(RightPin, LOW);
    digitalWrite(LeftPin, LOW);
  }
}

