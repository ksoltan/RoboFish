#include <Arduino.h>
#include "Joint.h"

Joint::Joint(int leftPin, int rightPin, bool isPwmTest = true) {
  pinMode(LED, OUTPUT);
  LeftPin = leftPin;
  RightPin = rightPin;
  lastUpdate = millis();
  isPwm = isPwmTest;
  activeMode = SIMPLE_FLAP; // All parameters are set already to default values. No need to call set.
}

void Joint::SimpleFlapSet(int duty, int deadZone, float frequency, float phase) {
  activeMode = SIMPLE_FLAP;
  currDuty = duty;
  currDeadZone = deadZone;
  phaseOffset = phase;
  lastUpdate = millis() - phase;
//  delay(phase); // Use delay if adding phase to lastUpdate.
  currFlapNum = 1;
  setFrequency(frequency);
//  Serial.println("Set Simple Flap.");
}

void Joint::LeftOnlySet(int duty, int deadZone = 0){
  // Flap once to the left side. Meant to test the pwm signal.
  activeMode = LEFT_ONLY;
  currDuty = duty;
  currDir = LEFT;
  currDeadZone = deadZone;
//  Serial.println("Set Left Only.");
}

void Joint::RightOnlySet(int duty, int deadZone = 0){
  // Flap once to the right side. Meant to test the pwm signal.
  activeMode = RIGHT_ONLY;
  currDuty = duty;
  currDir = RIGHT;
  currDeadZone = deadZone;
//  Serial.println("Set Right Only.");
}

int Joint::Update() {
  switch (activeMode) {
    case LEFT_ONLY:
      LeftOnlyUpdate();
      break;
    case RIGHT_ONLY:
      RightOnlyUpdate();
      break;
    default:
      break;
  }
  return Flap();
}

int Joint::getCurrFlapNum(){
  return currFlapNum;
}

int Joint::getCurrDuty(){
  return currDuty;
}

int Joint::getCurrDeadZone(){
  return currDeadZone;
}

float Joint::getCurrFrequency(){ // CHECK THIS
  return 1.0 / period * 1000;
}

void Joint::setDuty(int duty){
  currDuty = duty;
}

void Joint::setDeadZone(int deadZone){
  currDeadZone = deadZone;
}

void Joint::setFrequency(float frequency = 0.5) {
  period = (int)(1 / frequency * 1000); // convert to ms.
//  Serial.print("Set period to ");
//  Serial.print(period);
//  Serial.println(".\n");
}

void Joint::LeftOnlyUpdate(){
  // Trick the program into thinking it has switched direction already, and keep it going left.
  lastUpdate = millis();
  currDir = LEFT;
}

void Joint::RightOnlyUpdate(){
  // Trick the program into thinking it has switched direction already, and keep it going right.
  lastUpdate = millis();
  currDir = RIGHT;
}

int Joint::Flap() {
  int res = UpdateFlapDir();
  UpdatePins();
  return res;
}

int Joint::UpdateFlapDir() {
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
//    Serial.println("Flap.");
    return currDir == RIGHT ? 1 : -1;
  }
  return 0;
}

void Joint::UpdatePins() {
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
