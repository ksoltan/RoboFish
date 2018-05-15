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
  setDuty(duty);
  setDeadZone(deadZone);
  setPhase(phase);
  setFrequency(frequency);
  currFlapNum = 1;
//  Serial.println("Set Simple Flap.");
}

void Joint::FlapSet(){
  activeMode = SIMPLE_FLAP;
}

void Joint::LeftOnlySet(){
  // Flap once to the left side. Meant to test the pwm signal.
  activeMode = LEFT_ONLY;
  currDir = LEFT;
//  Serial.println("Set Left Only.");
}

void Joint::RightOnlySet(){
  // Flap once to the right side. Meant to test the pwm signal.
  activeMode = RIGHT_ONLY;
  currDir = RIGHT;
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

void Joint::setPhase(float phase = 0) {
  // Negative phase is equivalent to the period minus this offset.
  if(phase < 0){
    phase += period;
  }

  phaseOffset = phase;
  lastUpdate = millis() - phase;
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
  int res = UpdateFlapDir(); // Returns whether the joint just switched direction (-1 or 1) or is still moving (0). For Serial plotter vis.
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
